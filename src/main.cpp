#include <cstdio>

#include <OpenGL/GL.h>
#include <SDL2/SDL.h>

#include "common.h"
#include "screen.h"

int main() {
  // TODO: Error handling
  log("Hello, cpp_voxel!");
  SDL_Init(SDL_INIT_EVERYTHING);
  { // Start screen scope
    Screen s(800, 600, "cpp_voxel!");
  } // End screen scope
  SDL_Quit();
  return 0;
}
