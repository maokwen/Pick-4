#include <iostream>
#include <sstream>
#include <vector>
#include "Pick4.hpp"
#include "BitmapFont.hpp"
#include "Scene.hpp"
#include "FileSystem.hpp"

Scene::Scene() {}

Scene::~Scene() { SDL_DestroyTexture(target_); }

void Scene::cls() {
  SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer_);
}

bool Scene::init(SDL_Renderer* renderer) {
  renderer_ = renderer;
  target_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_TARGET, Pick4::screen_width,
                              Pick4::screen_height);
  return target_ != nullptr;
}

ConsoleScene::ConsoleScene() : Scene() {}

ConsoleScene::~ConsoleScene() {}

ConsoleScene& ConsoleScene::instance() {
  static ConsoleScene instance;
  return instance;
}

void ConsoleScene::print(const std::string& str, color c) {
  SDL_Color col = to_sdl_color(c);
  SDL_SetRenderDrawColor(renderer_, col.r, col.g, col.b, col.a);
  auto font = BitmapFont(renderer_);

  for (auto ch : str) {
    if (ch == '\n' ||
      cursor_.x >= Pick4::screen_height - BitmapFont::chat_size) {
      cursor_.x = 0;
      cursor_.y += BitmapFont::chat_size;
    }
    else { cursor_.x += BitmapFont::chat_size; }

    font.render(cursor_.x, cursor_.y, ch);
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
  else {
    print("\nCommand not found.");
  }
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
        if (cursor_.x >= Pick4::screen_width - 2 * BitmapFont::chat_size) {
          cursor_.x = 0, cursor_.y += BitmapFont::chat_size;
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
      }
      break;
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

  cursor_.x = 0;
  cursor_.y = 0;
  print(">");
}

DisplayScene::DisplayScene() : Scene() {}
DisplayScene::~DisplayScene() = default;

DisplayScene& DisplayScene::instance() {
  static DisplayScene instance;
  return instance;
}

void DisplayScene::set_update(const std::function<void()>& update) { update_ = update; }
void DisplayScene::set_draw(const std::function<void()>& draw) { draw_ = draw; }

void DisplayScene::pixel(int x0, int y0, color c) const {
  SDL_Color col = to_sdl_color(c);
  SDL_SetRenderDrawColor(renderer_, col.r, col.g, col.b, col.a);
  SDL_RenderDrawPoint(renderer_, x0, y0);
}

void DisplayScene::line(int x0, int y0, int x1, int y1, color c) const {
  SDL_Color col = to_sdl_color(c);
  SDL_SetRenderDrawColor(renderer_, col.r, col.g, col.b, col.a);
  int dx = x1 - x0, dy = y1 - y0;

  int step = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

  float x = (float)x0, y = (float)y0;
  for (int i = 0; i <= step; i++) {
    SDL_RenderDrawPoint(renderer_, (int)x, (int)y);
    x += dx / (float)step;
    y += dy / (float)step;
  }
}

void DisplayScene::circle(int x, int y, int r, color c) const {
  SDL_Color col = to_sdl_color(c);
  SDL_SetRenderDrawColor(renderer_, col.r, col.g, col.b, col.a);

  const int32_t diameter = (r * 2);

  int32_t dx = (r - 1);
  int32_t dy = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);

  while (dx >= dy) {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(renderer_, x + dx, y - dy);
    SDL_RenderDrawPoint(renderer_, x + dx, y + dy);
    SDL_RenderDrawPoint(renderer_, x - dx, y - dy);
    SDL_RenderDrawPoint(renderer_, x - dx, y + dy);
    SDL_RenderDrawPoint(renderer_, x + dy, y - dx);
    SDL_RenderDrawPoint(renderer_, x + dy, y + dx);
    SDL_RenderDrawPoint(renderer_, x - dy, y - dx);
    SDL_RenderDrawPoint(renderer_, x - dy, y + dx);

    if (error <= 0) {
      ++dy;
      error += ty;
      ty += 2;
    }

    if (error > 0) {
      --dx;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

scene_type DisplayScene::run() {
  Pick4::instance().load_script();

  SDL_SetRenderTarget(renderer_, target_);
  Pick4::instance().run_draw_script();
  SDL_SetRenderTarget(renderer_, nullptr);

  bool exit = false;
  SDL_Event event;
  while (!exit) {
    SDL_Delay(20);

    SDL_SetRenderTarget(renderer_, target_);

    Pick4::instance().run_update_script();

    SDL_SetRenderTarget(renderer_, nullptr);
    SDL_RenderCopy(renderer_, target_, nullptr, nullptr);
    SDL_RenderPresent(renderer_);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        exit = true;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) { return scene_console; }
      }
    }
  }

  return scene_exit;
}

void DisplayScene::cls() { Scene::cls(); }
