#include "Pick4.hpp"
#include <string>

int main(int argc, char* args[]) {
  auto& p4 = Pick4::instance();

  auto draw = [&]() {
    p4.cls();
    p4.text("Hello World!", 10, 10, Pick4::Color{0xff, 0xff, 0xff});
  };
  auto update = [&]() {
  };


  p4.create_window();
  p4.set_draw(draw);
  p4.set_update(update);
  p4.run();

  return 0;
}
