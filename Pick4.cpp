#include <chrono>
#include <iostream>
#include <thread>
#include "BitmapFont.hpp"
#include "Pick4.hpp"

using std::string;

Pick4& Pick4::instance() {
  static Pick4 instance;
  return instance;
}

void Pick4::create_window() { if (!init()) { printf("Failed to initialize!\n"); } }

void Pick4::set_update(const std::function<void()>& update) { this->update_ = update; }

void Pick4::set_draw(const std::function<void()>& draw) { this->draw_ = draw; }

void Pick4::run() {
  draw_();

  bool quit = false;
  SDL_Event event;
  while (!quit) {
    update_();

    SDL_RenderPresent(render_);
    SDL_Delay(20);
    
    SDL_UpdateWindowSurface(window_);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
        break;
        case SDL_TEXTINPUT:
          text(std::string(event.text.text), 0,0, Color{0xff,0xff,0x00});
        break;
      }
    }
  }

  close();
}

long Pick4::time() { return SDL_GetTicks(); }

void Pick4::cls() const {
  SDL_SetRenderDrawColor(render_, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(render_);
  SDL_UpdateWindowSurface(window_);
}

bool Pick4::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  window_ = SDL_CreateWindow("Pick-4", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, screen_width << 2,
                             screen_height << 2, SDL_WINDOW_SHOWN);
  if (!window_) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetWindowResizable(window_, SDL_TRUE);

  render_ = SDL_CreateRenderer(window_, -1, 0);
  SDL_RenderSetLogicalSize(render_, screen_width, screen_height);

  return true;
}

void Pick4::close() {
  SDL_DestroyWindow(window_);
  window_ = nullptr;
  SDL_Quit();
}

void Pick4::pixel(const int x0, const int y0, const Color c) {
  SDL_SetRenderDrawColor(render_, c.r, c.g, c.b, c.a);
  SDL_RenderDrawPoint(render_, x0, y0);
}

void Pick4::line(int x0, int y0, int x1, int y1, Color c) {
  SDL_SetRenderDrawColor(render_, c.r, c.g, c.b, c.a);
  int dx = x1 - x0, dy = y1 - y0;

  int step = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

  float x = x0, y = y0;
  for (int i = 0; i <= step; i++) {
    SDL_RenderDrawPoint(render_, x, y);
    x += dx / (float)step;
    y += dy / (float)step;
  }
}

void Pick4::midpoint_line(int x0, int y0, int x1, int y1, Color c) {
  SDL_SetRenderDrawColor(render_, c.r, c.g, c.b, c.a);

  int dx = x1 - x0, dy = y1 - y0;

  int d = dy - (dx / 2);
  int x = x0, y = y0;

  SDL_RenderDrawPoint(render_, x, y);

  for (; x < x1; x += 1) {
    if (d < 0)
      d += dy;
    else
      d += (dy - dx), y += 1;

    SDL_RenderDrawPoint(render_, x, y);
  }
}

void Pick4::circle(const int x, const int y, const int r, Color c) {
  const int32_t diameter = (r * 2);

  int32_t dx = (r - 1);
  int32_t dy = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);

  while (dx >= dy) {
    //  Each of the following renders an octant of the circle
    SDL_SetRenderDrawColor(render_, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(render_, x + dx, y - dy);
    SDL_RenderDrawPoint(render_, x + dx, y + dy);
    SDL_RenderDrawPoint(render_, x - dx, y - dy);
    SDL_RenderDrawPoint(render_, x - dx, y + dy);
    SDL_RenderDrawPoint(render_, x + dy, y - dx);
    SDL_RenderDrawPoint(render_, x + dy, y + dx);
    SDL_RenderDrawPoint(render_, x - dy, y - dx);
    SDL_RenderDrawPoint(render_, x - dy, y + dx);

    if (error <= 0) {
      ++dy;
      error += ty;
      ty += 2;
    }

    if (error > 0) {
      --dx;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

void Pick4::text(const std::string& str, int x, int y, Color c) {
  SDL_SetRenderDrawColor(render_, c.r, c.g, c.b, c.a);
  auto font = BitmapFont(render_);

  for (auto ch : str) {
    font.render(x, y, ch);
    if (x >= screen_height - BitmapFont::chat_size) {
      x = 0;
      y += BitmapFont::chat_size;
    } else {
      x += BitmapFont::chat_size;
    }
  }
}
