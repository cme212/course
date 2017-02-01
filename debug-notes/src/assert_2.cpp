#include <cassert>
#include <iostream>

/** add two non-negative integers
 * @param x integer to add
 * @param y integer to add
 * @return the value of x+y
 *
 * @pre 0 <= x and 0 <= y
 */
int non_negative_add(int x, int y) {
  assert(0 <= x);
  assert(0 <= y);
  return x+y;
}

int main() {
  using std::cout;
  using std::endl;

  cout << non_negative_add(2,2) << endl;
  cout << non_negative_add(2,-5) << endl;
}
