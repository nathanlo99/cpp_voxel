#include <cstdio>

#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>

#include "common.h"

const unsigned int SCREEN_WIDTH = 1100, SCREEN_HEIGHT = 750;
const char *TITLE = "C++ Voxel Engine";

SDL_Window *gWindow = nullptr;
SDL_GLContext gContext = nullptr;

bool init() {
  debug("Initializing SDL");
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    logSDLError("SDL_Init");
    return false;
  }

  const int OPENGL_MAJOR_VERSION = 3;
  const int OPENGL_MINOR_VERSION = 3;

  debug("Setting OpenGL Version to %d.%d", OPENGL_MAJOR_VERSION,
        OPENGL_MINOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  debug("Creating SDL Window");
  gWindow = SDL_CreateWindow(
      TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
      SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  if (gWindow == nullptr) {
    logSDLError("SDL_CreateWindow");
    return false;
  }

  debug("Creating GLContext");
  gContext = SDL_GL_CreateContext(gWindow);
  if (gContext == nullptr) {
    logSDLError("SDL_GL_CreateContext");
    return false;
  }

  debug("Setting VSync");
  if (SDL_GL_SetSwapInterval(1) < 0) {
    logSDLError("SDL_GL_SetSwapInterval");
    return false;
  }

  return true;
}

void quit(int code) {
  debug("Quitting with exit code %d", code);
  if (gContext != nullptr)
    SDL_GL_DeleteContext(gContext);
  if (gWindow != nullptr)
    SDL_DestroyWindow(gWindow);
  SDL_Quit();
  exit(code);
}

int main() {
  if (!init())
    return 1;

  SDL_Event e;

  debug("Entering Main Loop");
  while (true) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        debug("Quit Requested");
        quit(0);
      case SDL_MOUSEMOTION:
        char s[64];
        sprintf(s, "%s (%d, %d)", TITLE, e.motion.x, e.motion.y);
        SDL_SetWindowTitle(gWindow, s);
        break;
      default:
        // info("Unhandled event 0x%X", e.type);
        break;
      }
    }
  }

  quit(0);
}
