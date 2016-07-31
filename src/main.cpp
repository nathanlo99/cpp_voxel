#include <cstdio>

#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>

#include "common.h"

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 750
#define SCREEN_TITLE "C++ Voxel Engine"
#define TARGET_FPS 60

SDL_Window *gWindow = nullptr;
SDL_GLContext gContext = nullptr;
SDL_Event gEvent;

bool init();
void update();
void render();
void quit(int);

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
      SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
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

  debug(" === Printing System Info: === ");
  debug(" === Vendor:   %s", glGetString(GL_VENDOR));
  debug(" === Renderer: %s", glGetString(GL_RENDERER));
  debug(" === Version:  %s", glGetString(GL_VERSION));

  debug("Setting VSync");
  if (SDL_GL_SetSwapInterval(1) < 0) {
    logSDLError("SDL_GL_SetSwapInterval");
    return false;
  }

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

  return true;
}

void update() {
  while (SDL_PollEvent(&gEvent)) {
    switch (gEvent.type) {
    case SDL_QUIT:
      debug("Quit Requested");
      quit(0);
    case SDL_MOUSEMOTION:
      //   static char s[64];
      //   sprintf(s, "%s (%d, %d)", SCREEN_TITLE, gEvent.motion.x,
      //   gEvent.motion.y);
      //   SDL_SetWindowTitle(gWindow, s);
      break;
    default:
      // debug("Unhandled event 0x%X", e.type);
      break;
    }
  }
}

void render() {}

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

  debug("Entering Main Loop");

  int frames = 0;
  int frameCounter = 0;
  const double frameTime = 1.0 / TARGET_FPS;
  long lastTime = getTimeMs();
  double unprocessedTime = 0.0;
  while (true) {
    bool doRender = false;
    long startTime = getTimeMs();
    long passedTime = startTime - lastTime;
    lastTime = startTime;
    unprocessedTime += passedTime / 1000.0;
    frameCounter += passedTime;
    while (unprocessedTime > frameTime) {
      doRender = true;
      unprocessedTime -= frameTime;
      update();
      if (frameCounter >= 1000.0) {
        static char s[64];
        sprintf(s, "%s (%d FPS)", SCREEN_TITLE, frames);
        SDL_SetWindowTitle(gWindow, s);
        // debug("%d FPS", frames);
        frames = 0;
        frameCounter = 0;
      }
    }

    if (doRender) {
      render();
      frames++;
    }
  }

  quit(0);
}
