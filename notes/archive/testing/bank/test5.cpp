#include <gtest/gtest.h>
#include "bank_account.h"

class BankAccountFixture : public ::testing::Test {
 protected:
  virtual void SetUp() {
    b = new BankAccount;
  }
  virtual void TearDown() {
    delete b;
  }
  BankAccount* b = nullptr;
};

TEST_F(BankAccountFixture, EmptyAccount) {
  // SetUp() is already called
  ASSERT_NE(b, nullptr);
  EXPECT_EQ(b->GetBalance(), 0);
  EXPECT_EQ(b->GetNumberDeposits(), 0);
  EXPECT_EQ(b->GetNumberWithdrawals(), 0);
  // TearDown() will be called
}

TEST_F(BankAccountFixture, NonEmptyAccount) {
  // SetUp() is already called
  ASSERT_NE(b, nullptr);
  // do some things
  b->DepositMoney(19);
  b->WriteCheck(12);
  b->WriteCheck(5);
  // check the things
  EXPECT_EQ(b->GetBalance(), 2);
  EXPECT_EQ(b->GetNumberDeposits(), 1);
  EXPECT_EQ(b->GetNumberWithdrawals(), 2);
  // TearDown() will be called
}
