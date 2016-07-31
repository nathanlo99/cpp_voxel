#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <iostream>
#include <string>

#ifdef OS_APPLE
#include <sys/time.h>
#endif

// ================================= LOGGING =================================

inline void log(const char *desc, const char *format, va_list args) {
  printf("[%s] ", desc);
  vprintf(format, args);
  printf("\n");
}

inline void debug(const char *format, ...) {
#ifdef DEBUG
  va_list args;
  va_start(args, format);
  log("DEBUG", format, args);
  va_end(args);
#endif
}

inline void error(const char *format, ...) {
  va_list args;
  va_start(args, format);
  log("ERROR", format, args);
  va_end(args);
}

inline void logSDLError(const char *msg) {
  error("%s error: %s", msg, SDL_GetError());
}

// ============================== GETTING TIME ===============================
long getTimeMs() {
#ifdef OS_APPLE
  timeval tp;
  gettimeofday(&tp, nullptr);
  return tp.tv_sec * 1000 + tp.tv_usec / 1000;
#else
  error("Time Fetching for non-Apple operating systems not yet implemented");
  return 0;
#endif
}

#endif
