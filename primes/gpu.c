#include "gpu.h"
#include "log.h"

#include <stdio.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#define MAX_SOURCE_SIZE (0x100000)

int run(long number, int *result) {
  long *N = (long *)malloc(sizeof(long));
  int R = 1;

  *N = number;

  char *source_str;
  FILE *fp;
  fp = fopen("prime_kernel.cl", "r");

  source_str = (char *)malloc(MAX_SOURCE_SIZE * sizeof(char));
  size_t source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);

  fclose(fp);
  // Get platform and device information
  cl_platform_id platform_id = NULL;
  cl_device_id device_id = NULL;
  cl_uint ret_num_devices;
  cl_uint ret_num_platforms;
  cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id,
                       &ret_num_devices);

  // Create an OpenCL context
  cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
  // Create a command queue
  cl_command_queue command_queue =
      clCreateCommandQueue(context, device_id, 0, &ret);

  // Create memory buffers on the device for each vector
  cl_mem N_mem_obj =
      clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(long), NULL, &ret);
  cl_mem R_mem_obj =
      clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int), NULL, &ret);

  // Copy the lists A and B to their respective memory buffers
  ret = clEnqueueWriteBuffer(command_queue, N_mem_obj, CL_TRUE, 0, sizeof(long),
                             N, 0, NULL, NULL);

  // Create a program from the kernel source
  cl_program program =
      clCreateProgramWithSource(context, 1, (const char **)&source_str,
                                (const size_t *)&source_size, &ret);

  // Build the program
  ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

  // Create the OpenCL kernel
  cl_kernel kernel = clCreateKernel(program, "Compute", &ret);
  cl_device_type dev_type;

  clGetDeviceInfo(device_id, CL_DEVICE_TYPE, sizeof(dev_type), &dev_type, NULL);
  if (dev_type != CL_DEVICE_TYPE_GPU) {
    Error("GPU not used\n");
  }
  // Set the arguments of the kernel
  ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&N_mem_obj);
  ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&R_mem_obj);

  // Execute the OpenCL kernel on the list
  size_t global_item_size = number / 2; // Process the entire lists
  size_t local_item_size = 1;           // Divide work items into groups of 64
  ret =
      clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size,
                             &local_item_size, 0, NULL, NULL);

  ret = clEnqueueReadBuffer(command_queue, R_mem_obj, CL_TRUE, 0, sizeof(int),
                            &R, 0, NULL, NULL);
  *result = R;
  // Clean up
  ret = clFlush(command_queue);
  ret = clFinish(command_queue);
  ret = clReleaseKernel(kernel);
  ret = clReleaseProgram(program);
  ret = clReleaseMemObject(N_mem_obj);
  ret = clReleaseMemObject(R_mem_obj);
  ret = clReleaseCommandQueue(command_queue);
  ret = clReleaseContext(context);
  free(N);
  free(source_str);

  return ret;
}
