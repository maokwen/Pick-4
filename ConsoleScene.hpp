#pragma once
#include <functional>
#include <string>
#include "define.hpp"
#include "Scene.hpp"

class ConsoleScene final : public Scene {
  ConsoleScene();
  ~ConsoleScene();
public:
  static ConsoleScene& instance();

  void print(const std::string& str, int line = 0, color c = 1);
  void print_buf(const std::string& str, color c = 1);
  void exec(std::string command);

  scene_type run() override;
  void cls() override;
private:
  std::string input_buffer_;

  struct {
    int row;
    int col;
  } cursor_ = {0, 0};

  scene_type next_ = scene_exit;
};
