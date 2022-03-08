#include "timing.h"
#include "log.h"



static struct timespec start_time;
static struct timespec end_time;

int startTimer()
{
  if(clock_gettime(CLOCK_REALTIME, &start_time) == -1)  Warning("Clock failed\n");
  return 0;
}
int endTimer()
{
  if(clock_gettime(CLOCK_REALTIME, &end_time) == -1) Warning("Clock failed\n");
  return 0;
}
TimerResult getTimerResult()
{
  TimerResult r;
  r.delta_ns = end_time.tv_nsec - start_time.tv_nsec;
  r.delta_s = end_time.tv_sec - start_time.tv_sec;


  return r;
}
