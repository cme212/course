#pragma once

#include <cstdint>

class BankAccount {
 private:
  int32_t balance;
  uint32_t ndeposits;
  uint32_t nwithdrawals;
 public:
  BankAccount() {
    balance      = 0;
    ndeposits    = 0;
    nwithdrawals = 0;
  }
  void DepositMoney(uint32_t amount) {
    balance += amount;
    ndeposits++;
  }
  void WriteCheck(uint32_t amount) {
    balance -= amount;
    nwithdrawals++;
  }
  int32_t GetBalance(void) { return balance; }
  uint32_t GetNumberWithdrawals(void) { return nwithdrawals; }
  uint32_t GetNumberDeposits(void) { return ndeposits; }
};
