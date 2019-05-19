#include "Scene.hpp"
#include <iostream>
#include "Pick4.hpp"
#include "BitmapFont.hpp"

Scene::Scene() {}

Scene::~Scene() { SDL_DestroyTexture(target_); }

void Scene::cls() {
  SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer_);
}

bool Scene::init(SDL_Renderer* renderer) {
  renderer_ = renderer;
  target_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                              Pick4::screen_width,
                              Pick4::screen_height);
  if (!target_) return false;
  //SDL_SetRenderTarget(renderer_, target_);
  return true;
}

ConsoleScene::ConsoleScene(): Scene() {}
ConsoleScene::~ConsoleScene() = default;

ConsoleScene& ConsoleScene::instance() {
  static ConsoleScene instance;
  return instance;
}

void ConsoleScene::text(const std::string& str, int x, int y, Color c) {
  SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
  auto font = BitmapFont(renderer_);

  for (auto ch : str) {
    font.render(x, y, ch);
    if (x >= Pick4::screen_height - BitmapFont::chat_size) {
      x = 0;
      y += BitmapFont::chat_size;
    }
    else { x += BitmapFont::chat_size; }
  }
}

bool ConsoleScene::run() {
  SDL_SetRenderTarget(renderer_, target_);
  cls();
  SDL_StartTextInput();

  bool quit = false;
  SDL_Event event;
  while (!quit) {
    SDL_Delay(20);

    SDL_SetRenderTarget(renderer_, nullptr);
    SDL_RenderCopy(renderer_, target_, nullptr, nullptr);
    SDL_RenderPresent(renderer_);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
      case SDL_TEXTINPUT: {
        SDL_SetRenderTarget(renderer_, target_);
        if (row >= Pick4::screen_width - 2 * BitmapFont::chat_size) { row = 0, col += BitmapFont::chat_size; }
        text(std::string(event.text.text), row += BitmapFont::chat_size, col, Color{0xff, 0xff, 0x00});
      } break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          exit();
          return false;
        }
      }
    }
  }

  return true;
}

void ConsoleScene::exit() {
  SDL_SetRenderTarget(renderer_, nullptr);
  SDL_StopTextInput();
}

void ConsoleScene::cls() {
  Scene::cls();
  text(std::string("> "), 0, 0, Color{0xff, 0xff, 0x00});
  row = 0;
  col = 0;
}

DisplayScene::DisplayScene(): Scene() {}
DisplayScene::~DisplayScene() = default;

DisplayScene& DisplayScene::instance() {
  static DisplayScene instance;
  return instance;
}

void DisplayScene::set_update(const std::function<void()>& update) { update_ = update; }
void DisplayScene::set_draw(const std::function<void()>& draw) { draw_ = draw; }

void DisplayScene::pixel(int x0, int y0, Color c) {
  SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
  SDL_RenderDrawPoint(renderer_, x0, y0);
}

void DisplayScene::line(int x0, int y0, int x1, int y1, Color c) {
  SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
  int dx = x1 - x0, dy = y1 - y0;

  int step = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

  float x = (float)x0, y = (float)y0;
  for (int i = 0; i <= step; i++) {
    SDL_RenderDrawPoint(renderer_, (int)x, (int)y);
    x += dx / (float)step;
    y += dy / (float)step;
  }
}

void DisplayScene::circle(int x, int y, int r, Color c) {
  SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);

  const int32_t diameter = (r * 2);

  int32_t dx = (r - 1);
  int32_t dy = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);

  while (dx >= dy) {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(renderer_, x + dx, y - dy);
    SDL_RenderDrawPoint(renderer_, x + dx, y + dy);
    SDL_RenderDrawPoint(renderer_, x - dx, y - dy);
    SDL_RenderDrawPoint(renderer_, x - dx, y + dy);
    SDL_RenderDrawPoint(renderer_, x + dy, y - dx);
    SDL_RenderDrawPoint(renderer_, x + dy, y + dx);
    SDL_RenderDrawPoint(renderer_, x - dy, y - dx);
    SDL_RenderDrawPoint(renderer_, x - dy, y + dx);

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

bool DisplayScene::run() {
  SDL_SetRenderTarget(renderer_, target_);
  draw_();
  SDL_SetRenderTarget(renderer_, nullptr);

  bool quit = false;
  SDL_Event event;
  while (!quit) {
    SDL_Delay(20);

    SDL_SetRenderTarget(renderer_, target_);
    update_();
    SDL_SetRenderTarget(renderer_, nullptr);
    SDL_RenderCopy(renderer_, target_, nullptr, nullptr);
    SDL_RenderPresent(renderer_);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          exit();
          return false;
        }
      }
    }
  }

  return true;
}

void DisplayScene::exit() {}
void DisplayScene::cls() { Scene::cls(); }
