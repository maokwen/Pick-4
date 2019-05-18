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

class Pick4 {
  Pick4() { }
  ~Pick4() = default;

public:
  static Pick4& instance();
  void create_window();
  void set_update(const std::function<void()>&);
  void set_draw(const std::function<void()>&);
  void cls() const;
  void run();
  static long time();

  using Color = SDL_Color;

  void pixel(int x0, int y0, Color c);
  void line(int x0, int y0, int x1, int y1, Color c);
  void midpoint_line(int x0, int y0, int x1, int y1, Color c);
  void circle(int x, int y, int r, Color c);

  void text(const std::string& str, int x, int y, Color c);

  static const int screen_width = 128;
  static const int screen_height = 128;

private:

  bool init();
  void close();

  SDL_Window* window_ = nullptr;
  SDL_Surface* screen_surface_ = nullptr;
  SDL_Surface* console_surface_ = nullptr;
  SDL_Renderer* render_ = nullptr;

  std::function<void()> update_ = []() { };
  std::function<void()> draw_ = []() { };
};
