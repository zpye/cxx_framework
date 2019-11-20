#include "WaitKey.h"

#include <iostream>

int main() {
  while (true) {
    std::cout << "Please input..." << std::endl;
    int key = WaitKey();

    std::cout << "key: " << key << " " << (char)key << std::endl;

    if (key == 'q') {
      break;
    }
  }

  return 0;
}