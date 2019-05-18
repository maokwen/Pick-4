#include <cstddef>
#include <string>
#include "BitmapFont.hpp"
#include <iostream>

BitmapFont::BitmapFont(SDL_Renderer* renderer) : renderer_(renderer) {
  const auto bitmap = SDL_LoadBMP("font.bmp");
  if (!bitmap) {
    std::cout << "Create Surface From BMP File: " << SDL_GetError() << std::endl;
    return;
  }
  texture_ = SDL_CreateTextureFromSurface(renderer, bitmap);
  SDL_FreeSurface(bitmap);
  if (!texture_) {
    std::cout << "Create Texture From Surface: " << SDL_GetError() << std::endl;
    return;
  }

  build();
}

void BitmapFont::build() {
  int char_number = 0;
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      chars_table_[char_number].x = j * chat_size;
      chars_table_[char_number].y = i * chat_size;
      chars_table_[char_number].w = chat_size;
      chars_table_[char_number].h = chat_size;

      char_number += 1;
    }
  }
}

void BitmapFont::render(const int x, const int y, const char ch) const {
  if (!texture_) return;
  if (ch >= 256) return;

  SDL_Rect renderQuad = {x, y, chat_size, chat_size};

  SDL_RenderCopyEx(renderer_, texture_, &chars_table_[ch], &renderQuad, 0., nullptr,
                   SDL_FLIP_NONE);
}
