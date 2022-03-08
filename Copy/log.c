#include "log.h"
#include <stdarg.h>
#include <stdio.h>

#define RESET "\033[0m"
#define RED "\033[31;1m"
#define MAGENTA "\033[35m"
#define BLUE "\033[34;1m"
#define BRIGHT_YELLOW "\033[93;1m"
#define YELLOW "\033[33m"

void logInit() { fprintf(stdout, "\n"); }

void Error(const char *message, ...) {
  va_list args;
  va_start(args, message);
  fprintf(stderr, "%s[ERROR]:%s%s ", RED, RESET, RED);

  vfprintf(stderr, message, args);
  fprintf(stderr, "%s", RESET);
}
void Info(const char *message, ...) {
  va_list args;
  va_start(args, message);
  fprintf(stdout, "%s[INFO]:%s%s ", BLUE, RESET, MAGENTA);
  vfprintf(stdout, message, args);
  fprintf(stdout, "%s", RESET);
}
void Warning(const char *message, ...) {
  va_list args;
  va_start(args, message);
  fprintf(stdout, "%s[Warning]:%s%s ", BRIGHT_YELLOW, RESET, YELLOW);

  vfprintf(stdout, message, args);
  fprintf(stdout, "%s", RESET);
}


