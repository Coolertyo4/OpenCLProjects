#ifndef _ARGS_H
#define _ARGS_H
#include <stdbool.h>

int parseArgs(int argc, char *argv[], bool *cpu_flag, bool* timer_flag,bool *return_result_flag, long *number_flag);

#endif
