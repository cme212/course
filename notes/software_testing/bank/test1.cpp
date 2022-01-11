#include <iostream>

#include "bank_account.h"

int main() {
  // sequence of operations
  BankAccount b;
  b.DepositMoney(19);
  b.WriteCheck(12);
  b.WriteCheck(5);
  // checking the results
  if (b.GetBalance() != 2 or
      b.GetNumberDeposits() != 1 or
      b.GetNumberWithdrawals() != 2) {
    std::cout << "FAILED!" << std::endl;
  } else {
    std::cout << "PASSED!" << std::endl;
  }
}
