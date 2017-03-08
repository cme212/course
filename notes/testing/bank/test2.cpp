#include <cassert>
#include <iostream>
#include "bank_account.h"

int main() {
  // sequence of operations
  BankAccount b;
  b.DepositMoney(19);
  b.WriteCheck(12);
  b.WriteCheck(5);
  // checking the results
  assert(b.GetBalance() == 2);
  assert(b.GetNumberDeposits() == 1);
  assert(b.GetNumberWithdrawals() == 2);
}
