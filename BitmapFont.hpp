#pragma once
#include <SDL.h>

class BitmapFont {
public:
  BitmapFont(SDL_Renderer* renderer);

  void render(const int x, const int y, const char ch) const;

  static const int chat_size = 7;

private:
  SDL_Texture* texture_;
  SDL_Renderer* renderer_;

  SDL_Rect chars_table_[256]{};

  void build();
};
