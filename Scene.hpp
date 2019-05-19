#pragma once
#include <functional>
#include <string>
#include <SDL.h>
#include "Color.hpp"

class Scene {
public:
  Scene();
  virtual ~Scene();

  virtual void cls();

  bool init(SDL_Renderer* renderer);
  virtual bool run() { return false; }
  virtual void exit() {}

protected:
  SDL_Texture* target_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
};

class ConsoleScene final : public Scene {
  ConsoleScene();
  ~ConsoleScene();
public:
  static ConsoleScene& instance();

  void text(const std::string& str, int x, int y, Color c);

  bool run() override;
  void exit() override;
  void cls() override;
private:
  int row = 0;
  int col = 0;
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

  bool run() override;
  void exit() override;
  void cls() override;
private:
  std::function<void()> update_ = []() { };
  std::function<void()> draw_ = []() { };
};
