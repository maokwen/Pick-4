#pragma once
#include "Define.hpp"
#include <filesystem>

/*
 * Load & Save & Manage Cartridge file
 */
class FileSystem {
public:
  static void init();
  static void save(const cartridge cart, const std::string &name);
  static cartridge load(const std::string &name);
  static std::string ls();

  static std::filesystem::path appdata();
  static std::filesystem::path asserts();
  static std::filesystem::path carts();
};
