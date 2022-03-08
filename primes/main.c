
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "args.h"
#include "cpu.h"
#include "gpu.h"
#include "log.h"
#include "timing.h"

int main(int argc, char *argv[]) {
  int status;
  long number = (long)0xABCDEFCFD31;

  bool cpu = false;
  bool timer = false;
  bool return_result = 0;
  int result;

  parseArgs(argc, argv, &cpu, &timer, &return_result, &number);

  startTimer();
  status = cpu ? runCPU(number, &result) : run(number, &result);
  endTimer();
  Info("Number %ld is %s!\n", number, result ? "prime" : "not prime");

  if (timer) {
    TimerResult r = getTimerResult();
    Info("%fs %fns\n", r.delta_s, r.delta_ns);
  }

  if(return_result) return result;
  else return status;
}
