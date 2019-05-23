#include <iostream>
#include "BitmapFont.hpp"
#include "FileSystem.hpp"

BitmapFont::BitmapFont(SDL_Renderer* renderer) : renderer_(renderer) {
  auto fontfile = (FileSystem::asserts() / "font.bmp").string();
  const auto bitmap = SDL_LoadBMP(fontfile.c_str());
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
      chars_table_[char_number].x = j * char_width;
      chars_table_[char_number].y = i * char_height;
      chars_table_[char_number].w = char_width;
      chars_table_[char_number].h = char_height;

      char_number += 1;
    }
  }
}

void BitmapFont::render(const int x, const int y, const char ch) const {
  if (!texture_) return;
  if (ch >= 256) return;

  SDL_Rect renderQuad = {x, y, char_width, char_height};

  SDL_RenderCopyEx(renderer_, texture_, &chars_table_[ch], &renderQuad, 0., nullptr,
                   SDL_FLIP_NONE);
}
