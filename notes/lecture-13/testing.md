# CME 212: Lecture 13

## Software Testing

* You know it's important!

* How should / would / could you test your software?

### Some types of testing

* **Unit**: Small, fundamental aspect of the software (e.g. one method of a class)

* **Integration**: Groups of functions, classes, etc. are tested

* **Smoke**: Major functions of the application work (i.e. it doesn’t ""burn up" when
  powered on)

* **Regression**: Comprehensive testing of the application to make sure it has no
  defects (e.g. it gives the same results as previous versions, etc.)

* **Performance**: Does the application have the required level of performance /
  scalability?

* **Acceptance**: Making sure the software meets specified requirements (usually by
  the customer)

### Automation

Tests are useless if you don’t actually run them and check the results

* Automate, automate, automate the process

* It should be as easy as clicking a button or typing a simple command to run
  all of your tests

* Obviously some things are harder to automate than others (e.g. testing a GUI
  is more difficult to automate as compared to a command line interface)

* In many groups breaking the build (the code won’t compile or tests fail) is a
  major faux pas

* You can even automate the process of blaming the responsible party!

### Test code

* Automating your software testing means writing more code

* So you will have

  * Implementation code: the code that actually does something useful

  * Test code: the code that automates the tests of your implementation code

### Writing test code

* Writing good test code may be as, or even more important, than good
  implementation code

* There’s nothing more frustrating than trying to track down a phantom bug
  because there is a mistake in your test code!

* And you may get a false sense of security if your test code doesn’t actually
  test things properly

* Remember that your test code need not be super efficient since it’s only for
  testing, so try to avoid unnecessary complexity

### Test driven development (TDD)

* This is a model of software development where you write all the test code
  first

* After you’ve written all the tests you start writing the implementation

* When all of your tests pass you’re done with the implementation!

* Works great in theory

### What’s right for you?

* Your approach to testing should definitely depend on the situation

* You may have no test code in very research oriented work when you are just
  trying out new ideas

* At the other extreme if you have a code that has gone through significant
  testing, verification / validation, etc. you may have more test code than
  implementation code!

* Most situations fall somewhere in the middle

## Basic Example

### Getting Started

From `bank/bank_account.h`:

```c++
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
```

### A simple test

From `bank/test1.cpp`:

```c++
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
```

### Use `assert`

From `bank/test2.cpp`:

```c++
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
```

## Structured approach

* There are many, many testing frameworks out there

* Most of them have similar concepts

* We’ll talk about one called **Google Test**: <https://github.com/google/googletest>

  * Used by LLVM, OpenCV, Chromium Projects Protocol Buffers. Default testing
    framework used in [CLion](https://www.jetbrains.com/clion/).

* Concepts have also been ported to other languages so you can reuse your
  knowledge across Java, C, Python, etc.
  
  * <https://docs.python.org/3/library/unittest.html>
  
  * <http://junit.org/junit4/>
  
  * <http://docs.julialang.org/en/stable/stdlib/test/>

### Getting Google Test

It is recommended that you download the Google Test source code and compile it
with the same compiler and compiler flags as the rest of the project. This
allows you to avoid any issues that may come up related to language version or
ABI differences.

Process:

* Clone or download Google Test from: <https://github.com/google/googletest>

* Set up your build system to compile `gtest` and link your test cases against
  it. See `bank/Makefile` as an example. The `googletest` repo has examples for
  many other build systems as well. (Note: if you are planning a large project,
  I recommend [`cmake`](https://cmake.org/)).

### Testing BankAccount with Google Test

See `bank/test3.cpp`:

```c++
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
```

Compilation:

```sh
$ make test3
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread -c test3.cpp
clang++ -isystem ./googletest/include -I./googletest -std=c++11 -g -Wall -Wextra -pthread -c \
            ./googletest/src/gtest-all.cc
clang++ -isystem ./googletest/include -I./googletest -std=c++11 -g -Wall -Wextra -pthread -c \
            ./googletest/src/gtest_main.cc
ar rv gtest_main.a gtest-all.o gtest_main.o
ar: creating gtest_main.a
a - gtest-all.o
a - gtest_main.o
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread test3.o gtest_main.a -o test3
```

Running:

```sh
$ ./test3
Running main() from gtest_main.cc
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from BankAccountTest
[ RUN      ] BankAccountTest.EmptyAccount
[       OK ] BankAccountTest.EmptyAccount (0 ms)
[ RUN      ] BankAccountTest.NonEmptyAccount
[       OK ] BankAccountTest.NonEmptyAccount (0 ms)
[----------] 2 tests from BankAccountTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 2 tests.
```

### Simulate a bug

Let's simulate a test failure to see what happens.  See `bank/test4.cpp`:

```c++
#include <gtest/gtest.h>
#include "bank_account.h"

TEST(BankAccountTest,TestFailure) {
  BankAccount b;
  EXPECT_EQ(b.GetNumberDeposits(), 0);
  EXPECT_EQ(b.GetNumberWithdrawals(), 0);
  EXPECT_EQ(b.GetBalance(), 10000);
}
```

Compile and run it:

```sh
$ make test4 && ./test4
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread -c test4.cpp
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread test4.o gtest_main.a -o test4
Running main() from gtest_main.cc
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from BankAccountTest
[ RUN      ] BankAccountTest.TestFailure
test4.cpp:8: Failure
      Expected: b.GetBalance()
      Which is: 0
To be equal to: 10000
[  FAILED  ] BankAccountTest.TestFailure (0 ms)
[----------] 1 test from BankAccountTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] BankAccountTest.TestFailure

 1 FAILED TEST
```

## Fixtures

* Fixtures are one or more variables or objects that are setup and then torn
  down for each and every test

* The idea is to eliminate the possibility of side effects, where one test makes
  unexpected changes to an object that becomes the input for another test, which
  then causes that test to fail, etc.

* Fixture functions allow you to eliminate duplicating the code for this process

### Example BankAccount Fixture

See `bank/test5.cpp`

```c++
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
```

Compile and run:

```sh
$ make test5 && ./test5
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread -c test5.cpp
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread test5.o gtest_main.a -o test5
Running main() from gtest_main.cc
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from BankAccountFixture
[ RUN      ] BankAccountFixture.EmptyAccount
[       OK ] BankAccountFixture.EmptyAccount (0 ms)
[ RUN      ] BankAccountFixture.NonEmptyAccount
[       OK ] BankAccountFixture.NonEmptyAccount (0 ms)
[----------] 2 tests from BankAccountFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 2 tests.
```

## Testing exceptions

* In many cases we need to test not only the behavior of the code when it gets
  the expected input, but also how it deals with unusual situations

* Often this means the code will throw an exception

Check out `bank/test6.cpp`:

```c++
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
```

Compile and run:

```sh
$ make test6
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread -c test6.cpp
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread test6.o gtest_main.a -o test6
$ ./test6
Running main() from gtest_main.cc
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from FooTest
[ RUN      ] FooTest.ExceptionTest
[       OK ] FooTest.ExceptionTest (0 ms)
[----------] 1 test from FooTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
```

## Testing floating point equivalence

Floating point numbers should not be compared with `==`.  See `bank/test7.cpp`:

```c++
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
```

Compile and run:

```sh
$ make test7 && ./test7
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread -c test7.cpp
clang++ -isystem ./googletest/include -std=c++11 -g -Wall -Wextra -pthread test7.o gtest_main.a -o test7
Running main() from gtest_main.cc
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from FloatingPoint
[ RUN      ] FloatingPoint.FPTest1
[       OK ] FloatingPoint.FPTest1 (0 ms)
[----------] 1 test from FloatingPoint (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
```

## Organizing your code

* Once you start having a more complicated application with multiple files
  spread out across multiple directories, how should you organize it?

* Some people like to have the implementation and test code in the same file so
  it’s easy to see both of them at once

* Others like to have a dedicated tests/ directory where all of your
  non-implementation code goes

### A conventional directory layout

```
./makefile
./tests/
./tests/test1.cpp
./include/
./include/bank_account.h
./src/
./src/bank_account.cpp
./exe/
./exe/run_bank_account.cpp
```

Contents:

* Top-level `makefile` to control build. Sometimes `makefile`s in
  sub-directories is appropriate. However, it is a good idea to
  read
  [Recursive Make Considered Harmful](http://aegis.sourceforge.net/auug97.pdf).

* `tests/` directory to contain all tests.

* `include/` directory for header files (`*.h`, `*.hpp`).

* `src/` directory for a source files (`*.cpp`).

* `exe/` directory for source files intended for compilation into executables.
  (Note: this may not be widely used)

Some examples in practice:

* `libgit2`: <https://github.com/libgit2/libgit2>

* `lapacke`: C Interface to LAPACK <https://github.com/Reference-LAPACK/lapack/tree/master/LAPACKE>

* `thrust`: <https://github.com/thrust/thrust>

## Terminology summary

* **Test fixture**: optional setup and tear down functions that are called
  before and after each test is run

* **Test case**: Single test of functionality (could be a unit test,
  integration, regression, etc.)

* **Test suite**: Collection of test cases

* **Test runner**: Collection of one or more test suites that are run together

## Commit, nightly, weekly tests

* Some people feel like it is important to run a full set of tests every time a
  commit is made to a source repository

* Generally done in an automated way

* Makes tracking down bugs very quick

* The reality for most science and engineering applications is that this becomes
  very computationally expensive

* May want to split your tests into short, small ones that can be run each time
  you make changes

* And then longer ones that are run once a day, once a week, once a month, etc.

* See the `check` target in `bank/Makefile`.

## Beyond unit testing

* Code reviews

  * In some environments every change you make to the code will have to be hand
    reviewed by someone else on the team

* Automate running tests like Valgrind Memcheck
  
  * It’s far easier to address memory leaks, out of bounds accesses, etc. on an
    ongoing basis rather than cleaning up a giant mess every few months when you
    realize there is a problem

* Continuous Integration

  * the practice of merging all developer working copies to a shared mainline
    several times a day
    
  * Travis CI: <https://travis-ci.org/>
  
    * See: <https://travis-ci.org/JuliaLang/julia>
    
    * See: <https://github.com/JuliaLang/julia/pull/20937>
  
  * AppVeyor: <https://www.appveyor.com/>

## Summary

* Every software developer is at least partly a software tester

* Writing tests may seem like it will just take extra time, but in many
  situations it will actually save you lots of time

* Tailor your level of testing to the situation, e.g. academic research is
  different than an always up 24 x 7 service used by millions of people

* Automate: make it so easy to run your tests that you aren’t tempted to skip
  them

* Practice exercise: <https://github.com/rbharvs/testing-example>
