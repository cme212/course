#include <iostream>
#include <cassert>

/**
 * @brief A prototype for a unit test
 */
int gcd(int orig_a, int orig_b)
{
  int a = orig_a;
  int b = orig_b;
  /* @pre: a >= 1, b >= 1 */
  while (a != b) {
    /* LI: a, b both divisible by gcd(orig_a, orig_b) */
    if (a > b)
        a = a - b;
    else /* b > a */
        b = b - a;
    /* LI: a, b both divisible by gcd(orig_a, orig_b) */
  }
  /* @post: gcd(orig_a, orig_b) == a */
  return a;
}


int main()
{
  std:: cout << gcd(48, 64) << "\n";
  return 0;
}
