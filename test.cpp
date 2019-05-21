#include "Pick4.hpp"

int main(int argc, char* args[]) {
  auto& p4 = Pick4::instance();
  p4.create_window();

  p4.set_script(R"(
    function _draw()
	    cls()
    end

    local i = 0
    local d = 1

    function _update()
      line(0, 0, 128, i, 2)
      line(128, 0, 128 - i, 128, 3)
      line(128, 128, 0, 128 - i, 4)
      line(0, 128, i, 0, 5)
      i = i + d

      if i == 256 or i == 0 then
        d = -d
      end
    end
  )");
  
  p4.run();

  return 0;
}
