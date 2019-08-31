#pragma once
#include <cstdint>
#include <array>
#include "define.hpp"
#include "Pick4.hpp"

class P4Memory {
public:
  std::array<uint8_t, 128 * 128> screen;
  //cartridge cart;
  std::array<uint8_t, 5*3*80> font;

  P4Memory();

  //rect char_map(char);
};