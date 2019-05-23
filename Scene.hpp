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

class ConsoleScene final : public Scene {
  ConsoleScene();
  ~ConsoleScene();
public:
  static ConsoleScene& instance();

  void print(const std::string& str, color c = 1);
  void exec(std::string command);

  scene_type run() override;
  void cls() override;
private:
  std::string input_buffer_;

  struct {
    int x;
    int y;
  } cursor_ = {0, 0};

  scene_type next_ = scene_exit;
};

/* 
 * DisplayScene is a scene for drawing graphic for user scripts
 */
class DisplayScene final : public Scene {
  DisplayScene();
  ~DisplayScene();
public:
  static DisplayScene& instance();

  void set_update(const std::function<void()>&);
  void set_draw(const std::function<void()>&);

  void pixel(int x0, int y0, color c) const;
  void line(int x0, int y0, int x1, int y1, color c) const;
  void circle(int x, int y, int r, color c) const;

  scene_type run() override;
  void cls() override;
private:
  std::function<void()> update_ = []() { };
  std::function<void()> draw_ = []() { };
};
