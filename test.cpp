#include "Pick4.hpp"
#include  <iostream>
using namespace std;

int main(int argc, char* args[]) {
  auto& p4 = Pick4::instance();
  p4.create_window();
  p4.run();

  return 0;
}
