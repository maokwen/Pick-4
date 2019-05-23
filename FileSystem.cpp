#include "FileSystem.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

std::filesystem::path FileSystem::appdata() {
  static fs::path appdata = fs::path(getenv("APPDATA")) / "pick-4";
  fs::create_directories(appdata);
  return appdata;
}

std::filesystem::path FileSystem::asserts() {
  static fs::path asserts = appdata() / "asserts";
  fs::create_directories(asserts);
  return asserts;
}

std::filesystem::path FileSystem::carts() {
  static fs::path carts = appdata() / "carts";
  fs::create_directories(carts);
  return carts;
}

void FileSystem::init() {
  fs::copy_file("font.bmp", asserts() / "font.bmp", fs::copy_options::skip_existing);
  fs::copy_file("hello.p4", carts() / "hello.p4", fs::copy_options::skip_existing);

  fs::current_path(carts());
}

void FileSystem::save(const cartridge cart, const std::string& name) {
  std::ofstream ostrm(fs::current_path() / (name + ".p4"));
  ostrm << "__code_begin__\n" << cart.code << "__code_end__\n" << std::flush;
  ostrm.close();
}

cartridge FileSystem::load(const std::string& name) {
  std::ifstream istrm(fs::current_path() / (name + ".p4"));
  std::string code;

  if (!istrm.is_open()) {
    std::cout << "failed to open " << fs::current_path() / (name + ".p4") << std::endl;
    return cartridge{""};
  }

  std::string line;
  std::stringstream sstrm("", std::ios_base::app | std::ios_base::out);
  while (std::getline(istrm, line)) {
    if (line == "__code_begin__") { continue; }
    if (line == "__code_end__") {
      code = sstrm.str();
      sstrm.clear();
      continue;
    }
    sstrm << line << "\n";
  }
  istrm.close();

  cartridge cart{code};

  return cart;
}

std::string FileSystem::ls() {
  std::stringstream sstrm(std::ios_base::app | std::ios::out);
  sstrm << "DIR: " << fs::current_path().filename().string() << std::endl;
  for (const auto& entry :
       fs::directory_iterator(fs::current_path()))
    sstrm << entry.path().filename().string() << std::endl;
  return sstrm.str();
}
