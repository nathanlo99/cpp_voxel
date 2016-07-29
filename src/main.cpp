#include <cstdio>

#include <OpenGL/GL.h>
#include <SDL2/SDL.h>

#include "screen.h"

int main() {
  // TODO: Error handling
  printf("Hello, cpp_voxel!\n");
  SDL_Init(SDL_INIT_EVERYTHING);
  Screen s(800, 600, "cpp_voxel!");

  SDL_Quit();
  return 0;
}
