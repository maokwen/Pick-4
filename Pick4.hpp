#pragma once
#include <SDL.h>
#include <sol.hpp>
#include "Scene.hpp"
#include "DisplayScene.hpp"
#include "ConsoleScene.hpp"

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

  sol::state lua;
  void set_script(const std::string& script);
  bool load_script();
  bool run_draw_script();
  bool run_update_script();

private:
  void close();

  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  ConsoleScene& console_;
  DisplayScene& display_;

  std::string lua_script_;
};
