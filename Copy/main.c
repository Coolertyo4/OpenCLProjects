#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "log.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#define MAX_SOURCE_SIZE (0x100000)
#define SIZE 100000

int sort(int *A,int* R, size_t size);

int main() {
  int* A = (int*)malloc(SIZE * sizeof(int));
  int* R = (int*)malloc(SIZE * sizeof(int));
  sort(A,R, SIZE);
  int i;
  printf("A=[");
  for (i = 0; i < SIZE; ++i) {
    printf(" %d", A[i]);
  }
  printf(" ]\n");
  printf("R=[");
  for (i = 0; i < SIZE; ++i) {
    printf(" %d", R[i]);
  }
  printf(" ]\n");
  free(A);
}

int sort(int *A, int* R, size_t size) {
  
  char *source_str;
  size_t source_len;
  FILE *fp;
  source_str = (char *)malloc(MAX_SOURCE_SIZE * sizeof(char));
  fp = fopen("sort_kernel.cl", "r");
  if (!fp) {
    Error("Could not open Kernel source file\n");
    return -1;
  }
  source_len = fread(&source_str, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);

  cl_platform_id platform_id = NULL;
  cl_device_id device_id = NULL;
  cl_uint ret_num_devices, ret_num_platforms;
  cl_int ret;
  ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id,
                       &ret_num_devices);

  cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

  cl_command_queue queue = 
      clCreateCommandQueue(context, device_id, 0, &ret);

  cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, size * sizeof(int), NULL, &ret);
  cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size * sizeof(int), NULL, &ret);

  ret = clEnqueueWriteBuffer(queue, a_mem_obj, CL_TRUE, 0, sizeof(int) * size, A, 0, NULL, NULL);

  cl_program program = clCreateProgramWithSource(
      context, 1, (const char **)&source_str, &source_len, &ret);

  ret = clBuildProgram(program, ret_num_devices, &device_id, NULL, NULL, NULL);

  cl_kernel kernel = clCreateKernel(program, "copy", &ret);

  cl_device_type type;
  clGetDeviceInfo(device_id, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
  if (type != CL_DEVICE_TYPE_GPU) {
    Error("Not using GPU\n");
  }

  ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
  ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*) &b_mem_obj);

  size_t global = size;
  size_t local = 64;
  ret = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global, &local, 0, NULL, NULL);

  ret = clEnqueueReadBuffer(queue, b_mem_obj, CL_TRUE, 0, sizeof(int), &R, 0, NULL,
                            NULL);
  size_t i;
  for (i = 0; i < size; ++i) {
    Info("%d\n", A[i]);
  }
  ret = clFlush(queue);
  ret = clFinish(queue);
  ret = clReleaseKernel(kernel);
  ret = clReleaseProgram(program);
  ret = clReleaseMemObject(a_mem_obj);
  ret = clReleaseCommandQueue(queue);
  ret = clReleaseContext(context);
  free(source_str);
  return ret;
}
