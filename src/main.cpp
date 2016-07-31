#include <cstdio>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>

#include "common.h"

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 750
#define SCREEN_TITLE "C++ Voxel Engine"
#define TARGET_FPS 120

SDL_Window* gWindow = nullptr;
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

  debug("Setting up OpenGL Matrices");
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.f, SCREEN_WIDTH / SCREEN_HEIGHT, 0.0001f, 1000.f);
  glMatrixMode(GL_MODELVIEW);

  return true;
}

void update() {
  while (SDL_PollEvent(&gEvent)) {
    switch (gEvent.type) {
      case SDL_QUIT:
        debug("Quit Requested");
        quit(0);
      default:
        break;
    }
  }
}

void render() {
  glClearColor(0, 0, 0.75f, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

  debug("Entering Main Loop");

  int frames = 0;
  int frameCounter = 0;
  const double frameTime = 1.0 / TARGET_FPS;
  long lastTime = getTimeMs();
  bool doRender = false;
  double unprocessedTime = 0.0;
  while (true) {
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
        sprintf(s, SCREEN_TITLE " (%d FPS)", frames);
        SDL_SetWindowTitle(gWindow, s);
        frames = 0;
        frameCounter = 0;
      }
    }

    if (doRender) {
      render();
      doRender = false;
      frames++;
    } else {
      sleep((frameTime - unprocessedTime) * 1000000000L);
    }
  }

  quit(0);
}
