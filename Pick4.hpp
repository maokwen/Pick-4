#pragma once
#include <functional>
#include <string>
// SDL headers
#include <SDL.h>
// lua headers
#include <lauxlib.h>
#include <lua.h>
#include <luaconf.h>
#include <lualib.h>

#include "Color.hpp"
#include "Scene.hpp"

class Pick4 {
  Pick4();
  ~Pick4() = default;

public:
  static Pick4& instance();

  void create_window();
  void run();
  static long time();

  static const int screen_width = 128;
  static const int screen_height = 128;

private:
  void close();

  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  ConsoleScene& console_;
  DisplayScene& display_;
};
