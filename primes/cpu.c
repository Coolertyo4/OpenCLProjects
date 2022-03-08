#include "cpu.h"
#include "log.h"
void Compute(long *i, long *number, int *result) {
  if (*number % *i == 0) {
    *result = 0;
  }
}

int runCPU(long number, int *result) {
  Warning("Running on CPU (Much slower)\n");
  *result = 1;
  long i;
  for (i = 2; i <= number / 2; ++i) {
    Compute(&i, &number, result);
  }
  return 0;
}
