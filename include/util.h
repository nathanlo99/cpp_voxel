#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <iostream>
#include <string>

// ================================= VERBOSE =================================

void log(const char *format, ...) {
#ifdef DEBUG
  va_list args;
  va_start(args, format);
  printf("[INFO] ");
  vfprintf(stdout, format, args);
  printf("\n");
  va_end(args);
#endif
}

// ============================== ERROR LOGGING ==============================
inline void logSDLError(std::ostream &os, const std::string &msg) {
  printf("[ERROR] %s error: %s\n", msg.c_str(), SDL_GetError());
}

#endif
