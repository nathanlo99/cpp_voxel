#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <iostream>
#include <string>

// ================================= LOGGING =================================

void log(const char *desc, const char *format, ...) {
  va_list args;
  va_start(args, format);
  printf("[%s] ", desc);
  vfprintf(stdout, format, args);
  printf("\n");
  va_end(args);
}

void debug(const char *format, ...) {
#ifdef DEBUG
  va_list args;
  va_start(args, format);
  log("INFO", format, args);
  va_end(args);
#endif
}

void error(const char *format, ...) {
  va_list args;
  va_start(args, format);
  log("ERROR", format, args);
  va_end(args);
}

// ============================== ERROR LOGGING ==============================
inline void logSDLError(const char *msg) {
  log("ERROR", "%s error: %s", msg, SDL_GetError());
}

#endif
