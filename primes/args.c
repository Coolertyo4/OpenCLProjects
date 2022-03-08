#include "args.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

int parseArgs(int argc, char *argv[], bool *cpu_flag, bool* timer_flag, bool *return_result_flag, long *number_flag) {
  for (int i = 1; i < argc; ++i) {
    if (strstr(argv[i], "-c") != NULL) {
      *cpu_flag = true;
    }else if (strstr(argv[i], "-t") != NULL) {
      *timer_flag = true;
    }else if (strstr(argv[i], "-r") != NULL) {
      *return_result_flag = true;
    } else if (strstr(argv[i], "-n") != NULL) {
      if (argc - 1 > i) {
        *number_flag = atol(argv[++i]);
      } else {
        Warning("No number provided (Running with default)\n");
      }
    }
  }
  return 0;
}

