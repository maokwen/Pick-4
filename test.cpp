#include "Pick4.hpp"
#include "Scene.hpp"
#include <string>

int main(int argc, char* args[]) {
  auto& p4 = Pick4::instance();
  p4.create_window();

  auto& p4d = DisplayScene::instance();
  auto& p4c = ConsoleScene::instance();

  auto draw = [&]() { p4d.cls(); };
  int i = 0, d = 1;
  auto update = [&]() {
    p4d.cls();

    p4d.line(0, 0, 128, i, Color{0xff, 0xff, 0x00});
    p4d.line(128, 0, 128 - i, 128, Color{0xff, 0xff, 0x00});
    p4d.line(128, 128, 0, 128 - i, Color{0xff, 0xff, 0x00});
    p4d.line(0, 128, i, 0, Color{0xff, 0xff, 0x00});

    i += d;
    if (i == 256 || i == 0) d = -d;
  };
  p4d.set_draw(draw);
  p4d.set_update(update);
  
  p4.run();

  return 0;
}
