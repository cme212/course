#include <limits>
#include <iostream>

// min_exponent10 - smallest negative power of 10 that is valid floating point #
// max_exponent10 - largest negative power of 10 that is valid floating point #
 
int main() 
{
  std::cout << "\t\tmin\t\tmax\t\tmantisa\texp min\texp max\tradix\n"
            << "float\t\t"
            << std::numeric_limits<float>::min() << '\t'
            << std::numeric_limits<float>::max() << '\t'
            << std::numeric_limits<float>::digits10 << '\t'
            << std::numeric_limits<float>::min_exponent10 << '\t'
            << std::numeric_limits<float>::max_exponent10 << '\t'
            << std::numeric_limits<float>::radix << '\n';
  std::cout << "double\t\t"
            << std::numeric_limits<double>::min() << '\t'
            << std::numeric_limits<double>::max() << '\t'
            << std::numeric_limits<double>::digits10 << '\t'
            << std::numeric_limits<double>::min_exponent10 << '\t'
            << std::numeric_limits<double>::max_exponent10 << '\t'
            << std::numeric_limits<double>::radix << '\n';
  std::cout << "long double\t"
            << std::numeric_limits<long double>::min() << '\t'
            << std::numeric_limits<long double>::max() << '\t'
            << std::numeric_limits<long double>::digits10 << '\t'
            << std::numeric_limits<long double>::min_exponent10 << '\t'
            << std::numeric_limits<long double>::max_exponent10 << '\t'
            << std::numeric_limits<long double>::radix << '\n';

  return 0;
}
