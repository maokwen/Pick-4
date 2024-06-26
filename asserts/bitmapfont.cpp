#include <array>

std::array &&create_font() {
  std::array<uint8_t, 5*5 * 3*16>&& font {
    0,0,0,	0,1,0,	1,0,1,	1,0,1,	1,1,1,	1,0,1,	1,1,0,	0,1,0,	0,1,0,	0,1,0,	1,0,1,	0,1,0,	0,0,0,	0,0,0,	0,0,0,	0,0,1,
    0,0,0,	0,1,0,	1,0,1,	1,1,1,	1,1,0,	0,0,1,	1,0,0,	0,1,0,	1,0,0,	0,0,1,	0,1,0,	0,1,0,	0,0,0,	0,0,0,	0,0,0,	0,0,1,
    0,0,0,	0,1,0,	0,0,0,	1,0,1,	0,1,1,	0,1,0,	0,1,0,	0,0,0,	1,0,0,	0,0,1,	1,1,1,	1,1,1,	0,0,0,	1,1,1,	0,0,0,	0,1,0,
    0,0,0,	0,0,0,	0,0,0,	1,1,1,	1,1,1,	1,0,0,	1,0,1,	0,0,0,	1,0,0,	0,0,1,	0,1,0,	0,1,0,	0,1,0,	0,0,0,	0,0,0,	1,0,0,
    0,0,0,	0,1,0,	0,0,0,	1,0,1,	0,1,0,	1,0,1,	1,1,0,	0,0,0,	0,1,0,	0,1,0,	1,0,1,	0,1,0,	1,0,0,	0,0,0,	1,0,0,	1,0,0,
    
    1,1,1,	1,1,0,	1,1,1,	1,1,1,	1,0,1,	1,1,1,	1,1,1,	1,1,1,	1,1,1,	1,1,1,	0,0,0,	0,0,0,	0,0,1,	0,0,0,	1,0,0,	1,1,1,
    1,0,1,	0,1,0,	0,0,1,	0,0,1,	1,0,1,	1,0,0,	1,0,0,	0,0,1,	1,0,1,	1,0,1,	0,1,0,	0,1,0,	0,1,0,	1,1,1,	0,1,0,	0,0,1,
    1,0,1,	0,1,0,	1,1,1,	1,1,1,	1,1,1,	1,1,1,	1,1,1,	0,0,1,	1,1,1,	1,1,1,	0,0,0,	0,0,0,	1,0,0,	0,0,0,	0,0,1,	0,1,0,
    1,0,1,	0,1,0,	1,0,0,	0,0,1,	0,0,1,	0,0,1,	1,0,1,	0,0,1,	1,0,1,	0,0,1,	0,1,0,	0,1,0,	0,1,0,	1,1,1,	0,1,0,	0,0,0,
    1,1,1,	1,1,1,	1,1,1,	1,1,1,	0,0,1,	1,1,1,	1,1,1,	0,0,1,	1,1,1,	1,1,1,	0,0,0,	1,0,0,	0,0,1,	0,0,0,	1,0,0,	0,1,0,
    
    0,1,1,	1,1,1,	1,1,1,	1,1,1,	1,1,0,	1,1,1,	1,1,1,	0,1,1,	1,0,1,	1,1,1,	1,1,1,	1,0,1,	1,0,0,	1,0,1,	1,1,0,	0,1,1,
    1,0,1,	1,0,1,	1,0,1,	1,0,1,	1,0,1,	1,0,0,	1,0,0,	1,0,0,	1,0,1,	0,1,0,	0,1,0,	1,0,1,	1,0,0,	1,1,1,	1,0,1,	1,0,1,
    1,1,1,	1,1,1,	1,1,0,	1,0,0,	1,0,1,	1,1,1,	1,1,1,	1,0,0,	1,1,1,	0,1,0,	0,1,0,	1,1,0,	1,0,0,	1,1,1,	1,0,1,	1,0,1,
    1,0,0,	1,0,1,	1,0,1,	1,0,1,	1,0,1,	1,0,0,	1,0,0,	1,0,1,	1,0,1,	0,1,0,	0,1,0,	1,0,1,	1,0,0,	1,0,1,	1,0,1,	1,0,1,
    0,1,1,	1,0,1,	1,1,1,	1,1,1,	1,1,0,	1,1,1,	1,0,0,	1,1,1,	1,0,1,	1,1,1,	1,1,0,	1,0,1,	1,1,1,	1,0,1,	1,0,1,	1,1,0,
    
    1,1,1,	0,1,1,	1,1,1,	0,1,1,	1,1,1,	1,0,1,	1,0,1,	1,0,1,	1,0,1,	1,0,1,	1,1,1,	1,1,0,	1,0,0,	0,1,1,	0,1,0,	0,0,0,
    1,0,1,	1,0,1,	1,0,1,	1,0,0,	0,1,0,	1,0,1,	1,0,1,	1,0,1,	1,0,1,	1,0,1,	0,0,1,	1,0,0,	1,0,0,	0,0,1,	1,0,1,	0,0,0,
    1,1,1,	1,0,1,	1,1,0,	1,1,1,	0,1,0,	1,0,1,	1,0,1,	1,1,1,	0,1,0,	1,1,1,	0,1,0,	1,0,0,	0,1,0,	0,0,1,	0,0,0,	0,0,0,
    1,0,0,	1,1,0,	1,0,1,	0,0,1,	0,1,0,	1,0,1,	1,0,1,	1,1,1,	1,0,1,	0,0,1,	1,0,0,	1,0,0,	0,0,1,	0,0,1,	0,0,0,	0,0,0,
    1,0,0,	0,0,1,	1,0,1,	1,1,0,	0,1,0,	0,1,1,	0,1,0,	1,0,1,	1,0,1,	1,1,1,	1,1,1,	1,1,0,	0,0,1,	0,1,1,	0,0,0,	1,1,1,
    
    1,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,1,1,	0,1,0,	1,1,0,	0,0,0,	0,0,0,
    0,1,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,1,0,	0,1,0,	0,1,0,	0,0,1,	0,0,0,
    0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	1,1,0,	0,1,0,	0,1,1,	1,1,1,	0,0,0,
    0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,1,0,	0,1,0,	0,1,0,	1,0,0,	0,0,0,
    0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,0,0,	0,1,1,	0,1,0,	1,1,0,	0,0,0,	0,0,0,
  };
  return font;
}