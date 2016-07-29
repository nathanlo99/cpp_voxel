
#include <SDL2/SDL.h>
#include <string>

class Screen {
public:
  Screen(int width, int height, std::string title);
  void update();
  void render();
  ~Screen();

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  SDL_Surface *m_surface;
  int m_width, m_height, *m_pixels;
};
