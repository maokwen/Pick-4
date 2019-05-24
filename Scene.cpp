#include <iostream>
#include <sstream>
#include <vector>
#include "Pick4.hpp"
#include "BitmapFont.hpp"
#include "Scene.hpp"
#include "FileSystem.hpp"

Scene::Scene() {}

Scene::~Scene() { SDL_DestroyTexture(target_); }

void Scene::cls() {
  SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer_);
}

bool Scene::init(SDL_Renderer* renderer) {
  renderer_ = renderer;
  target_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_TARGET, Pick4::screen_width,
                              Pick4::screen_height);
  return target_ != nullptr;
}
