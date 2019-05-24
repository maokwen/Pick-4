#include "Scene.hpp"
#include <iostream>
#include "BitmapFont.hpp"
#include "Pick4.hpp"
#include "ConsoleScene.hpp"

ConsoleScene::ConsoleScene() : Scene() {}

ConsoleScene::~ConsoleScene() {}

ConsoleScene& ConsoleScene::instance() {
  static ConsoleScene instance;
  return instance;
}

void ConsoleScene::print(const std::string& str, int line, color c) {
  SDL_Color col = to_sdl_color(c);
  SDL_SetRenderDrawColor(renderer_, col.r, col.g, col.b, col.a);
  auto font = BitmapFont(renderer_);

  for (auto ch : str) {
    if (ch == '\n' || cursor_.col >= Pick4::screen_width - BitmapFont::char_width) {
      cursor_.col = 0;
      cursor_.row += BitmapFont::char_height;
    }
    else { cursor_.col += BitmapFont::char_width; }

    font.render(cursor_.col, cursor_.row, ch);
  }
}

void ConsoleScene::exec(std::string command) {
  std::vector<std::string> argc;

  if (command.empty()) return;

  std::string buf;
  std::stringstream ss(command);
  while (ss >> buf) argc.push_back(command);

  if (argc[0] == "cls") { cls(); }
  else if (argc[0] == "run") { next_ = scene_display; }
  else if (argc[0] == "ls") {
    //std::string dirs = fs_.ls();
    print("\n");
    print(FileSystem::ls());
  }
  else { print("\nCommand not found."); }
  print("\n>");

  input_buffer_.clear();
}

scene_type ConsoleScene::run() {
  SDL_SetRenderTarget(renderer_, target_);
  cls();
  SDL_StartTextInput();

  SDL_Event event;
  for (next_ = scene_console; next_ == scene_console;) {
    SDL_Delay(20);

    SDL_SetRenderTarget(renderer_, nullptr);
    SDL_RenderCopy(renderer_, target_, nullptr, nullptr);
    SDL_RenderPresent(renderer_);

    SDL_SetRenderTarget(renderer_, target_);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        next_ = scene_exit;
        break;
      case SDL_TEXTINPUT: {
        SDL_SetRenderTarget(renderer_, target_);
        if (cursor_.col >= Pick4::screen_width - 2 * BitmapFont::char_width) {
          cursor_.col = 0, cursor_.row += BitmapFont::char_height;
        }
        print(std::string(event.text.text));
        input_buffer_ += event.text.text;
        std::cout << input_buffer_ << std::endl;
      }
      break;
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          next_ = scene_editor;
          break;
        case SDLK_RETURN:
          std::cout << "ENTER" << std::endl;
          exec(input_buffer_);
          break;
        }
        break;
      }
      }
    }
  }

  input_buffer_.clear();
  SDL_SetRenderTarget(renderer_, nullptr);
  SDL_StopTextInput();
  return next_;
}


void ConsoleScene::cls() {
  Scene::cls();

  cursor_.col = 0;
  cursor_.row = 0;
  print(">");
}
