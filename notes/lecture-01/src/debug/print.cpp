#include <iostream>

int main() {
  using std::cout;
  using std::endl;

// Compile with `-D MY_DEBUG` to enable printing debug output
#ifdef MY_DEBUG
  cout << "__FILE__: " << __FILE__ << endl;
  cout << "__LINE__: " << __LINE__ << endl;
#endif

  return 0;
}
