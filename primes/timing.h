#ifndef _TIMING_H
#define _TIMING_H

#include <time.h>

typedef struct 
{
  double delta_s, delta_ns;
}TimerResult;

int startTimer();

int endTimer();

TimerResult getTimerResult();

#endif
