#include <stdexcept>
#include <gtest/gtest.h>

class Foo {
 public:
  void bar(int n) {
    if (n < 0) {
      throw std::runtime_error("n may not be negative");
    }
  }
};

TEST(FooTest,ExceptionTest) {
  Foo f;
  EXPECT_NO_THROW(f.bar(100));
  EXPECT_THROW(f.bar(-20), std::runtime_error);
  EXPECT_ANY_THROW(f.bar(-20));
}
