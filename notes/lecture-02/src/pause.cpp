#include <iostream>

int main() {
  std::cout << "before pause" << std::endl;
  // will wait for user to hit enter
  std::cin.get();
  std::cout << "after pause" << std::endl;

  // pause in a loop
  for (int i=0; i != 5; ++i) {
    std::cout << "iter: " << i << std::endl;
    std::cin.get();
  }
}
