#ifndef _MY_HEADER_HPP_
#define _MY_HEADER_HPP_

#include <iostream>

inline void printStuff() // Linking fails in not inline!
{
  std::cout << "Printing ... \n";
}

#endif //  _MY_HEADER_HPP_
