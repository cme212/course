#include "debug_macro.hpp"
#include <iostream>

int main() {
  using std::cout;
  using std::endl;

  int a = 5;
  int b = 6;

  BUGPRINT(a*b);

  cout << "a = " << a << endl;
  cout << "b = " << b << endl;

  return 0;
}
