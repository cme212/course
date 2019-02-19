#include <gtest/gtest.h>
#include "bank_account.h"

TEST(BankAccountTest,TestFailure) {
  BankAccount b;
  EXPECT_EQ(b.GetNumberDeposits(), 0);
  EXPECT_EQ(b.GetNumberWithdrawals(), 0);
  EXPECT_EQ(b.GetBalance(), 10000);
}
