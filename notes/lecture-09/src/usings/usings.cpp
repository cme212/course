
#include <iostream>

template <class T>
class Square
{
public:
  Square(){}
  ~Square(){}
  T get(const T& x)
  {
    return x*x;
  }
};


//using square_type = Square<T>; // error: use of undeclared identifier 'T'

using square_type = Square<double>;

template <class T, class B>
class Fair
{
public:
  using square_type = Square<B>;

  Fair(){}
  ~Fair(){}
  B get(const T& x)
  {
    square_type sq;
    return sq.get(B(x)); // Assumes one can construct B from T!
                         // Big assumption, but let's play along.
  }
};

template <class B>
using fair_type = Fair<int, B>;

int main()
{
  Square<double> sq1;
  square_type sq2;
  Fair<double, bool> fr1;
  fair_type<bool> fr2;

  double a = 2.0;
  int b = 2;
  std::cout << sq1.get(a) << " ?= " << sq2.get(b) << "\n";
  std::cout << fr1.get(a) << " ?= " << fr2.get(b) << "\n";
  return 0;
}
