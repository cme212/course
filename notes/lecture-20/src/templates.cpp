
#include <iostream>
#include <vector>
#include <complex>

template <class T>
class ScalarTraits
{

};

template <>
class ScalarTraits<double>
{
public:
  typedef double dot_prod_type;
  typedef double norm_type;
};

template <>
class ScalarTraits<std::complex<double> >
{
public:
  typedef std::complex<double> dot_prod_type;
  typedef double norm_type;
};


template <class T>
typename ScalarTraits<T>::norm_type normL2(const std::vector<T>& x)
{
  typename std::vector<T>::size_type i; // specify size_type is a typename, 
                                        // not a (static) variable

  typename ScalarTraits<T>::norm_type norm = std::abs(x[0]) * std::abs(x[0]);

  for (i=1; i<x.size(); ++i)
  {
    norm += std::abs(x[i]) * std::abs(x[i]);
  }
  return std::sqrt(norm);
}


template <class T>
typename ScalarTraits<T>::dot_prod_type dotProduct(const std::vector<T>& x, 
                                                   const std::vector<T>& y)
{
  typename std::vector<T>::size_type i; // specify size_type is a typename, not a (static) variable
  typename ScalarTraits<T>::dot_prod_type dp = x[0]*y[0];
  
  for (i=1; i<x.size(); ++i)
  {
    dp += x[i]*y[i];
  }
  return dp;
}

int main()
{
  std::vector<double> x = {0.,4.,3.};
  std::vector<double> y = {2.,2.,2.};

  std::cout << " x.y  = " << dotProduct(x, y) << "\n";
  std::cout << "||x|| = " << normL2(x) << "\n";
  
  std::vector<std::complex<double> > a = {std::complex<double>(8.,2.), std::complex<double>(2.,3.)};
  std::vector<std::complex<double> > b = {std::complex<double>(8.,-2.), std::complex<double>(2.,-3.)};

  std::cout << " x.y  = " << dotProduct(a, b) << "\n";
  std::cout << "||x|| = " << normL2(a) << "\n";

  std::vector<int> u = {1, 2, 3};
  std::vector<int> v = {2, 2, 2};
  
  //std::cout << dotProduct(u, v) << "\n";

  return 0;
}
