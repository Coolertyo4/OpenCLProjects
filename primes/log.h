#ifndef _LOG_HPP
#define _LOG_HPP

void logInit();

void Error(const char *message, ...);
void Info(const char *message, ...);
void Warning(const char *message, ...);
void LogFps(int frames);

#define ErrorP(message)                                                        \
  Error("File: %s, Line: %d %s", __FILE__, __LINE__, message)

#endif
