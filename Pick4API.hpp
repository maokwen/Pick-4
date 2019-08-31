#pragma once
#include <functional>
#include "pick_memory.hpp"

struct graphic_api {
  std::function<void(pick_memory, int,int,color)> pixel;
  std::function<void(pick_memory, int,int,int,int,color)> line;
  std::function<void(pick_memory, int x, int y, int w, int h, color)> rect;
  std::function<void(pick_memory, color)> cls;
};

static void api_pixel(pick_memory &mem, int x, int y, color col) {
  if (x > Pick4::screen_width || y > Pick4::screen_height) return;
  mem.screen[y * Pick4::screen_width + x] = col;
}

static void api_line(pick_memory &mem, int x0, int y0, int x1, int y1, color col) {
  const auto dx = x1 - x0, dy = y1 - y0;
  const auto step = static_cast<float>(std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy));

  auto x = static_cast<float>(x0), y = static_cast<float>(y0);
  for (auto i = 0; i <= step; i++) {
    api_pixel(mem, x, y, col);
    x += dx / step;
    y += dy / step;
  }
}

static void api_rect(pick_memory &mem, int x, int y, int w, int h, color col) {
  for (auto i = y; i < y+h; ++i) {
    for (auto j = x; j < x+w; ++j)
      api_pixel(mem, j, i, col);
  }
}

static void api_cls(pick_memory &mem, color col) {
  api_rect(mem, 0, 0, Pick4::screen_width, Pick4::screen_height, col);
}

static void api_char(pick_memory &mem, int x, int y, char ch, color color) {
  if (ch >= 'a' && ch <= 'z') {
    ch = tolower(ch);
  } else if (ch >= '{' && ch <= '~') {
    ch -= 16;
  }

  api_rect(mem, x, y, 4, 6, 0);

  if (ch > ' ' && ch < 'z') {
    ch -= ' ';
    const auto row = ch / 16, col = ch % 16;
    for (auto i = 0; i < 5; ++i)
      for (auto j = 0; j < 3; ++j)
        if (mem.font[( row * 5 + i) * Pick4::screen_width * col * 3 + j])
          api_pixel(mem, x + j, y + i, color);
  }
}