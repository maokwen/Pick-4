#pragma once
#include <SDL.h>

class BitmapFont {
public:
  BitmapFont(SDL_Renderer* renderer);

  void render(const int x, const int y, const char ch) const;

  static const int char_width = 6;
  static const int char_height = 7;

private:
  SDL_Texture* texture_;
  SDL_Renderer* renderer_;

  SDL_Rect chars_table_[176]{};

  void build();
};
