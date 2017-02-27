#include <stdio.h>
#include "foobar.h"

int main() {
  // call foo
  int c = foo(0);
  printf("c = %d\n",c);

  // call bar
  bar();
}
