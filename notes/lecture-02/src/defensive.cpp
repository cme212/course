#include <iostream>

double add(double& a, double& b)
{
  a += b; // does not compile
  return a;
}


int main()
{
  double x = 2.0;
  double y = 3.0;
  double z = add(x, y);

  std::cout << x << " + " << y << " = " << z << "\n";

  return 0;
}
