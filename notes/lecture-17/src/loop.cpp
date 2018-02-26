

#include <iostream>
#include <cmath>

int main()
{
  double i = 0;

  while (std::abs(i - 1.0) > 1e-14)
  //while (i != 1.0)
  {
    i += 0.1;
    std::cout << i << "\n";
  }
  return 0;
}
