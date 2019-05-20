#pragma once
#include <functional>
#include <string>
#include <SDL.h>
#include "Color.hpp"

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

class ConsoleScene final : public Scene {
  ConsoleScene();
  ~ConsoleScene();
public:
  static ConsoleScene& instance();

  void print(const std::string& str, Color c = Color{0xff, 0xff, 0x00});
  void exec(std::string command);

  scene_type run() override;
  void cls() override;
private:
  std::string input_buffer_;

  struct {int x;int y;} cursor_;

  scene_type next_;
};

class DisplayScene final : public Scene {
  DisplayScene();
  ~DisplayScene();
public:
  static DisplayScene& instance();

  void set_update(const std::function<void()>&);
  void set_draw(const std::function<void()>&);

  void pixel(int x0, int y0, Color c);
  void line(int x0, int y0, int x1, int y1, Color c);
  void circle(int x, int y, int r, Color c);

  scene_type run() override;
  void cls() override;
private:
  std::function<void()> update_ = []() { };
  std::function<void()> draw_ = []() { };
};
