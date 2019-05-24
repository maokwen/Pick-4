#pragma once
#include <functional>
#include <string>
#include <SDL.h>
#include "define.hpp"
#include "FileSystem.hpp"

enum scene_type {
  scene_exit,
  scene_console,
  scene_display,
  scene_editor
};

class Scene {
public:
  Scene();
  virtual ~Scene();

  virtual void cls();

  bool init(SDL_Renderer* renderer);
  virtual scene_type run() { return scene_exit; }

protected:
  SDL_Texture* target_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
};
