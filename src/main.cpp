#include <cstdio>

#include <OpenGL/GL.h>
#include <SDL2/SDL.h>

#include "common.h"
#include "screen.h"

const unsigned int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
const char *TITLE = "C++ Voxel Engine";

SDL_Window *gWindow = nullptr;
SDL_GLContext gContext = nullptr;

bool init() {
  debug("Initializing SDL");
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    logSDLError("SDL_Init");
    return false;
  }

  debug("Setting OpenGL Version to 2.1");
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

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
  debug("Quitting");
  SDL_Quit();
  exit(code);
}

int main() {
  // TODO: Error handling
  debug("Hello, cpp_voxel!");
  if (!init())
    return 1;

  quit(0);
}
