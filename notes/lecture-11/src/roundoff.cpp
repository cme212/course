#include <iostream>

int main()
{
  // Floating point arithmetic is not associative!
  float a = (1e-8f +  1.0f) - 0.99999f;
  float b =  1e-8f + (1.0f  - 0.99999f);

  std::cout << a << " =? " << b << "\n";
  // On my machine prints: 1.00136e-05 =? 1.00236e-05

  return 0;
}
