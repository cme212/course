#include <gtest/gtest.h>
#include "bank_account.h"

TEST(BankAccountTest,EmptyAccount) {
  BankAccount b;
  EXPECT_EQ(b.GetBalance(), 0);
  EXPECT_EQ(b.GetNumberDeposits(), 0);
  EXPECT_EQ(b.GetNumberWithdrawals(), 0);
}

TEST(BankAccountTest,NonEmptyAccount) {
  BankAccount b;
  // do some things
  b.DepositMoney(19);
  b.WriteCheck(12);
  b.WriteCheck(5);
  // check the things
  EXPECT_EQ(b.GetBalance(), 2);
  EXPECT_EQ(b.GetNumberDeposits(), 1);
  EXPECT_EQ(b.GetNumberWithdrawals(), 2);
}
