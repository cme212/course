#include <iostream>

// b <~ b + a
void add(int& a, int& b)
{
  a += b;
}

int main()
{
  int x = 2;
  int y = 3;

  std::cout << x << " + " << y << " = ";
  add(x, y)
  std::cout << y << "\n";

  return 0;
}
