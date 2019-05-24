#pragma once
#include <functional>
#include "define.hpp"
#include "Scene.hpp"

/* 
 * DisplayScene is a scene for drawing graphic for user scripts
 */
class DisplayScene : public Scene {
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
