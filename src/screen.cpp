#include <SDL2/SDL.h>

#include "screen.h"

Screen::Screen(int width, int height, std::string title) {
  m_width = width;
  m_height = height;
  // TODO: Error handling
  m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, m_width, m_height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
  m_surface = SDL_GetWindowSurface(m_window);
  m_pixels = (int *)m_surface->pixels;
}

void Screen::update() {
  // NOTE: Get input

  // NOTE: Change things
}

void Screen::render() {
  SDL_RenderClear(m_renderer);
  // NOTE: Rendering code here
  SDL_RenderPresent(m_renderer);
}

Screen::~Screen() {
  // TODO: More robust check?
  if (m_surface) {
    SDL_FreeSurface(m_surface);
  }

  if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
  }

  if (m_window) {
    SDL_DestroyWindow(m_window);
  }
}
