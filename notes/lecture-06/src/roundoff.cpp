#include <iostream>

int main()
{
  float a = (1e-9 + 1.0e1);
  float b = 1e-9 + (1.0e1 - 0.9999999e1);

  a -= 0.9999999e1;

  std::cout << a << " =? " << b << "\n";

  return 0;
}
