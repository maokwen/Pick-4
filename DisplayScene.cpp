
#include "DisplayScene.hpp"
#include "Scene.hpp"
#include "Pick4.hpp"

DisplayScene::DisplayScene() : Scene() {}
DisplayScene::~DisplayScene() = default;

DisplayScene& DisplayScene::instance() {
  static DisplayScene instance;
  return instance;
}

void DisplayScene::set_update(const std::function<void()>& update) { update_ = update; }
void DisplayScene::set_draw(const std::function<void()>& draw) { draw_ = draw; }

void DisplayScene::pixel(int x0, int y0, color c) const {
  SDL_Color col = to_sdl_color(c);
  SDL_SetRenderDrawColor(renderer_, col.r, col.g, col.b, col.a);
  SDL_RenderDrawPoint(renderer_, x0, y0);
}

void DisplayScene::line(int x0, int y0, int x1, int y1, color c) const {
  SDL_Color col = to_sdl_color(c);
  SDL_SetRenderDrawColor(renderer_, col.r, col.g, col.b, col.a);
  int dx = x1 - x0, dy = y1 - y0;

  int step = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

  float x = (float)x0, y = (float)y0;
  for (int i = 0; i <= step; i++) {
    SDL_RenderDrawPoint(renderer_, (int)x, (int)y);
    x += dx / (float)step;
    y += dy / (float)step;
  }
}

void DisplayScene::circle(int x, int y, int r, color c) const {
  SDL_Color col = to_sdl_color(c);
  SDL_SetRenderDrawColor(renderer_, col.r, col.g, col.b, col.a);

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

scene_type DisplayScene::run() {
  Pick4::instance().load_script();

  SDL_SetRenderTarget(renderer_, target_);
  Pick4::instance().run_draw_script();
  SDL_SetRenderTarget(renderer_, nullptr);

  bool exit = false;
  SDL_Event event;
  while (!exit) {
    SDL_Delay(20);

    SDL_SetRenderTarget(renderer_, target_);

    Pick4::instance().run_update_script();

    SDL_SetRenderTarget(renderer_, nullptr);
    SDL_RenderCopy(renderer_, target_, nullptr, nullptr);
    SDL_RenderPresent(renderer_);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        exit = true;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) { return scene_console; }
      }
    }
  }

  return scene_exit;
}

auto DisplayScene::cls() -> void { Scene::cls(); }
