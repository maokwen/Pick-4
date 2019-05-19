#include <chrono>
#include <iostream>
#include <thread>
#include "BitmapFont.hpp"
#include "Pick4.hpp"

using std::string;

Pick4::Pick4():console_(ConsoleScene::instance()), display_(DisplayScene::instance()) {
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

  if(!console_.init(renderer_))  {
    printf("ConsoleScene could not be created! SDL_Error: %s\n", SDL_GetError());
    return;
  }
  if(!display_.init(renderer_))  {
    printf("DisplayScene not be created! SDL_Error: %s\n", SDL_GetError());
    return;
  }
}

Pick4& Pick4::instance() {
  static Pick4 instance;
  return instance;
}

void Pick4::create_window() {}

void Pick4::run() {

  bool quit = false;
  SDL_Event event;

  while (!quit) {
    quit = display_.run();
    if (!quit) quit = console_.run();
  }

  close();
}

long Pick4::time() { return SDL_GetTicks(); }

void Pick4::close() {
  SDL_DestroyWindow(window_);
  window_ = nullptr;
  SDL_Quit();
}
