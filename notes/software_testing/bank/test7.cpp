#include <cmath>
#include <gtest/gtest.h>

TEST(FloatingPoint, FPTest1) {
  double x = 0.0;
  double y = std::sin(2*M_PI);
  //EXPECT_EQ(x,y);
  //EXPECT_DOUBLE_EQ(x,y);
  EXPECT_NEAR(x,y,1e-8); // uses absolute error
  // note, use EXPECT_FLOAT_EQ for float (32-bit)
}
