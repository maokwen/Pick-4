#include <chrono>
#include <iostream>
#include <thread>
#include "Pick4.hpp"

using std::string;

Pick4::Pick4(): console_(ConsoleScene::instance()), display_(DisplayScene::instance()) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return;
  }
  window_ = SDL_CreateWindow("Pick-4", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, screen_width << 2,
                             screen_height << 2, SDL_WINDOW_SHOWN);
  if (!window_) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  SDL_SetWindowResizable(window_, SDL_TRUE);

  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  SDL_RenderSetLogicalSize(renderer_, screen_width, screen_height);

  if (!console_.init(renderer_)) {
    printf("ConsoleScene could not be created! SDL_Error: %s\n", SDL_GetError());
    return;
  }
  if (!display_.init(renderer_)) {
    printf("DisplayScene not be created! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  lua.set_function("cls", []() { DisplayScene::instance().cls(); });
  lua.set_function("pixel", [](int x,int y,int c) { DisplayScene::instance().pixel(x, y, c); });
  lua.set_function(
    "line", [](int x0,int y0,int x1, int y1, int c) { DisplayScene::instance().line(x0, y0, x1, y1, c); });
}

Pick4& Pick4::instance() {
  static Pick4 instance;
  return instance;
}

void Pick4::create_window() {}

void Pick4::run() {

  scene_type next = scene_display;

  while (next != scene_exit) {
    switch (next) {
    case scene_console: next = console_.run();
      break;
    case scene_display: next = display_.run();
      break;
    case scene_editor:
    default:
      next = display_.run();
      break;
    }
  }

  close();
}

long Pick4::time() { return SDL_GetTicks(); }

void Pick4::set_script(const std::string& script) { lua_script_ = script; }

bool Pick4::load_script() {
  lua.script(lua_script_);
  return true;
}

bool Pick4::run_draw_script() {
  lua.script("_draw()");
  return true;
}

bool Pick4::run_update_script() {
  lua.script("_update()");
  return true;
}

void Pick4::close() {
  SDL_DestroyWindow(window_);
  window_ = nullptr;
  SDL_Quit();
}
