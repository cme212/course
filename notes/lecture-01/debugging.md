# CME 212: Lecture 01 - Debugging



Most of your programming time will be spent figuring out why your
code doesn't work the way you wanted it to work. Learning how
to discover and fix issues in your code, i.e. debug it, will
help you spend less time troubleshooting your homework assignments
and leave you more time to learn about new software design concepts.

## Defensive programming

The most difficult bugs to identify are those that only slightly change
results of your computation, but otherwise let your code run uninterupted.
These are also the most costly ones. If your code crashes, you will spend
some time fixing it, but other than extra time you spent on your
code, there is no other damage. If, on the other hand, your code produces
incorrect but believable results, the damage could be much more. For example, 
your company may decide to build a prototype of an aircraft component
based on your computation, only to find in (immensly expensive) hardware tests
that the prototype does not meet the specifications.

Defensive programming means that you try to anticipate mistakes that can 
accidentaly get in your code, and structure your code in the way that it fails
to compile or stops execution if that happens. Take a look, for example,
at the following code:
```c++
#include <iostream>

// b <~ b + a
void add(int& a, int& b)
{
  a += b;
}

int main()
{
  int x = 2;
  int y = 3;

  std::cout << x << " + " << y << " = ";
  add(x, y)
  std::cout << y << "\n";

  return 0;
}
```
We implemented a simple function that adds two numbers, but
in the process variable `a` is changed, what was not our intention. 
The output of the code is:
```
$ ./a.out 
2 + 3 = 3
$
```
By stating our design intention explicitly, using constant data
types, we can have compiler catch our mistake.
```c++
// b <~ b + a
void add(const int& a, int& b)
{
  a += b; // does not compile
}
```
Trying to compile the modified code will result in the compile error:
```
$ g++ -Wall defensive.cpp
compiler.cpp:5:5: error: read-only variable is not assignable
  a += b; // does not compile
  ~ ^
1 error generated.
$
```
The compiler mesage provides the description of the problem and the line
where the problem occured, as opposed to the previous case, where the code
run happily without giving us any indication about the damage it was doing
in the background.

Unfortunately, not all bugs can be caught at compile time. In those cases
we need to debug our executable.

## Simple debugging techniques

### Print statements

The most basic and widely used debugging methodology involves inserting print
statements (`cout`) in your code to determine the state of various things as the
program is running. It is likely that you are already doing this! Here are some
things to keep in mind:

* Make sure to commit your code to version control before embarking on a print
  statement fueled bug hunt. After you find the bug, it is nice to be able to
  revert the code to clean up all of the print statements.
  
* Make sure to commit your code before you make changes in an attempt to fix the
  bug. It can be very difficult to remember what to undo without version
  control. You want to be able to quickly undo a mess created in an attempt to
  fix a bug.

* You can use `__FILE__` and `__LINE__` preprocessor macros to output the filename
  and line number.  For example, the code:
```c++
  cout << "__FILE__: " << __FILE__ << endl;
  cout << "__LINE__: " << __LINE__ << endl;
```
will output the file name and line number.  See `src/print.cpp`.

### Debug macro

It is often handy to use a preprocessor macro for debugging statements.  This can
alleviate some of the burden of always writing `std::cout << x << std::endl;`.
Let's look at a simple example in `src/debug_macro.hpp`:

```c++
#ifdef PRINT_DEBUG
#define BUGPRINT(x)                                     \
  do {                                                  \
    std::cerr << __FILE__ << ":" << __LINE__ << ": ";   \
    std::cerr << #x << " -> " << (x) << std::endl;      \
  } while (0)
#else
#define BUGPRINT(X)
#endif
```

This code defines a "macro" called `BUGPRINT`. If the identifier `PRINT_DEBUG`
is defined, the preprocessor will replace each instance of `BUGPRINT(x)` in
the code with the do-loop in the macro; note that we use a do-while loop such that a call to `BUGPRINT` can be executed as part of `if-else` statements and other control flow [see StackOverflow](https://stackoverflow.com/a/1067238) Otherwise, the preprocessor will
replace `BUGPRINT(x)` with nothing. See `src/debug_macro.cpp`:

```c++
#include "debug_macro.hpp"
#include <iostream>

int main() {
  using std::cout;
  using std::endl;

  int a = 5;
  int b = 6;

  BUGPRINT(a*b);

  cout << "a = " << a << endl;
  cout << "b = " << b << endl;

  return 0;
}
```

Under normal compilation, the call to `BUGPRINT` has no effect:

```sh
$ clang++ debug_macro.cpp -o debug_macro
$ ./debug_macro
a = 5
b = 6
```

We add a compiler flag `-DPRINT_DEBUG` to define the identifier
`PRINT_DEBUG` and thus enable preprocessor code replacement:

```sh
$ clang++ -DPRINT_DEBUG debug_macro.cpp -o debug_macro
$ ./debug_macro
debug_macro.cpp:11: a*b -> 30
a = 5
b = 6
```
In the output we get a lot of useful information!
The operator `#` in the macro is called "stringizing" operator. It will
return string representation of the expression to which it is applied.

**IMPORTANT NOTE** The macro argument `x` does not behave in the same way as an
argument of a function. Remember -- macro is just a text replacement pattern
applied to your code before compilation. If you, for example, have macro
```c++
#define F(x) x*2
```
then using it like this
```c++
c = F(a+b);
```
will result in the following code being compiled:
```c++
c = a+b*2;
```
Because of operator precedence in C++, the result will be *a* + 2*b* instaed of
2(*a* + *b*). To avoid mistakes like this, the argument of the macro should always
be put within brackets, even when it may appear redundant:
```c++
#define F(x) (x)*2
```
This will ensure that the expression `x` is always evaluated first.

**ANOTHER IMPORTANT NOTE**: if you use a macro like `BUGPRINT`, it is important that the
input have no side-effects.  That is, no variables should be changed.  If a call
to `BUGPRINT` caused variables to change, then you would have different behavior
when the macro is enabled and make your bug even harder to find.


### Assert statements

Assert statements are a useful tool to check conditions in code.  It looks like this:

```c++
assert(condition);
```

If `condition` evaluates to `true`, nothing happens. If `condition` evaluates to
false, the program will terminate and print a (hopefully useful) error message.
Let's look at the example from <http://en.cppreference.com/w/cpp/error/assert>
(see `src/assert_1.cpp`):

```c++
#include <cassert>
#include <iostream>

int main() {
  assert(2 + 2 == 4);
  std::cout << "Execution continues past the first assert\n";
  assert(2 + 2 == 5);
  std::cout << "Execution continues past the second assert\n";
}
```

If we compile and run, we see:

```sh
$ clang++ assert_1.cpp -o assert_1
$ ./assert_1
Execution continues past the first assert
assert_1: assert_1.cpp:7: int main(): Assertion `2 + 2 == 5' failed.
Aborted (core dumped)
```

`assert` is a preprocessor macro. All `assert` statements can be disabled by
defining `NDEBUG`:

```sh
$ clang++ -DNDEBUG assert_1.cpp -o assert_1
$ ./assert_1
Execution continues past the first assert
Execution continues past the second assert
```

### Assert statements in functions

It is often a good idea to test preconditions for functions using `assert`
statements.  It could go something like this (see: `assert_2.cpp`):

```c++
/** add two non-negative integers
 * @param x integer to add
 * @param y integer to add
 * @return the value of x+y
 *
 * @pre x >= 0 and y >= 0
 */
int non_negative_add(int x, int y) {
  assert(x >= 0);
  assert(y >= 0);
  return x+y;
}
```

Let's write a simple main function:

```cpp
int main() {
  using std::cout;
  using std::endl;

  cout << non_negative_add(2,2) << endl;
  cout << non_negative_add(2,-5) << endl;
}
```

And use it:

```sh
$ clang++ assert_2.cpp -o assert_2
$ ./assert_2
4
assert_2: assert_2.cpp:13: int non_negative_add(int, int): Assertion `y >= 0' failed.
Aborted (core dumped)
```

We can also disable the `assert` statements at compile time:

```sh
$ clang++ -DNDEBUG assert_2.cpp -o assert_2
$ ./assert_2
4
-3
```

### Simple pause

It is often very handy to pause a program so a human can read terminal output
before continuing. This may help you debug a loop, for example. This is easy to
do in C++ with `std::cin.get()` (in `<iostream>`).  See `src/pause.cpp`:

```c++
#include <iostream>

int main() {
  std::cout << "before pause" << std::endl;
  // will wait for user to hit enter
  std::cin.get();
  std::cout << "after pause" << std::endl;

  // pause in a loop
  for (int i=0; i != 5; ++i) {
    std::cout << "iter: " << i << std::endl;
    std::cin.get();
  }
}
```

Usage:

```sh
$ clang++ pause.cpp -o pause
$ ./pause
before pause
# (user hit enter)
after pause
iter: 0
# (user hit enter)
iter: 1
# (user hit enter)
iter: 2
# (user hit enter)
iter: 3
# (user hit enter)
iter: 4
# (user hit enter)
```

Be sure to remove all pauses before releasing your code into the wild. It is
often good to provide a prompt:

```c++
std::cout << "hit enter to continue." << std::endl;
std::cin.get();
```

## Command line debugger -- LLDB

Command line debuggers such as GDB and LLDB come without graphical
bells and whistles, but can be as effective when you get some
experience with them. Once you learn how to use a console-based
debugger, it will be fairly straightforward to learn almost any
graphics-based one.

Let's use this simple C++ code in file [student.cpp](src/student.cpp)
to introduce LLDB basics:
```c++
#include <string>


// Definition of the class Student
class Student
{
public:
  // Constructor
  Student(std::string name, int studentID)
  {
    name_      = name; // set break point here
    studentID_ = studentID;
  }

  // Destructor
  ~Student()
  {
    studentID_ = 0;
  }

private:
  std::string name_; // Student's name
  int studentID_;    // Student's ID number
};


int main()
{
  // The instance of Student on the stack.
  Student icmeStudent("Terry Gilliam", 123444);

  // The instance of Student on the heap.
  Student* pGeographyStudent = new Student("Terry Jones", 123555);

  delete pGeographyStudent;
    
  return 0;
}
```

### Compiling code for debugging

In order to enable debugging, we nned to compile the code with `-g` flag to
tell compiler to enable debugging symbols in the executable. It is also
highly desirable to turn off optimization with flag `-O0`, so that the debugger
can keep track of what line in the source code is being executed. We can
build our code by
```
clang++ -g -O0 -o student student.cpp
```
This code produces no output, so to see what is going on inside we need
to use debugger.

### Starting debugger

To start debugger simply enter `lldb` followed by the executable name
on the command line:
```
$ lldb student
(lldb) target create "student"
Current executable set to 'student' (x86_64).
(lldb)
```
To run the executable, enter `run` at the debugger command prompt.
```
(lldb) run
Process 27818 launched: '/Users/peles/lectures/classes/debug' (x86_64)
Process 27818 exited with status = 0 (0x00000000) 
(lldb)
```
This tells us that the code ran without any errors. By the way, most difficult
bugs to find are those when your code produces believable results and
returns no errors. These are situations when you need a debugger the most.

### Setting break points

Running the code in a debugger by itself does not give you much information.
You typically want to pause at certain places in the code and review what
is going on there. You can set up break points (i.e. places for quiet reflection)
in your code by using debugger `breakpoint` command. We want to set a breakpoint
inside the constructor of the Student class at line 11:
```
(lldb) breakpoint set --file student.cpp --line 11
Breakpoint 1: where = student`Student::Student(std::__1::basic_string<char,
std::__1::char_traits<char>, std::__1::allocator<char> >, int) + 158 at
student.cpp:11, address = 0x0000000100000d0e
(lldb) 
```
Note that GDB command for setting the break point is different: `break student.cpp:11`.
Now, when we run the code, we stop at the break points we set. The first is the
constructor for `icmeStudent` instance of class `Student`.
```
(lldb) run
Process 27952 launched: '/Users/peles/lectures/classes/debug' (x86_64)
Process 27952 stopped
* thread #1: tid = 0x29cb6f, 0x0000000100000cfe student`Student::Student(this=
0x00007fff5fbffa58, name="Terry Gilliam", studentID=123444) + 158 at student.cpp:11,
queue = 'com.apple.main-thread',
stop reason = breakpoint 1.1
    frame #0: 0x0000000100000cfe student`Student::Student(this=0x00007fff5fbffa58,
    name="Terry Gilliam", studentID=123444) + 158 at student.cpp:11
   8   	  // Constructor
   9   	  Student(std::string name, int studentID)
   10  	  {
-> 11  	    name_      = name; // set break point here
   12  	    studentID_ = studentID;
   13  	  }
   14  	
(lldb)
```
Now that we stopped the code execution at the place we wanted,
we would like to inspect variable values there. 
You can view the variables in the curret scope by typing
```
(lldb) frame variable
(Student *) this = 0x00007fff5fbffa58
(std::__1::string) name = "Terry Gilliam"
(int) studentID = 123444
(lldb)
```
To continue execution of the code simply type `continue` or `c` at the
debugger command prompt. That gets us to the next break point inside
the constructor for the Georgraphy student instance of the class `Student`
(who happens to be Terry Jones).
```
(lldb) continue
Process 27952 resuming
Process 27952 stopped
* thread #1: tid = 0x29cb6f, 0x0000000100000cfe student`Student::Student(
this=0x0000000100104b40, name="Terry Jones", studentID=123555) + 158
at student.cpp:11, queue = 'com.apple.main-thread', stop reason =
breakpoint 1.1
    frame #0: 0x0000000100000cfe student`Student::Student(
    this=0x0000000100104b40, name="Terry Jones", studentID=123555)
    + 158 at student.cpp:11
   8   	  // Constructor
   9   	  Student(std::string name, int studentID)
   10  	  {
-> 11  	    name_      = name; // set break point here
   12  	    studentID_ = studentID;
   13  	  }
   14  	
(lldb) 
```
We can take a look at the varibales again:
```
(lldb) frame variable name
(std::__1::string) name = "Terry Jones"
(lldb) frame variable name_
(std::__1::string) name_ = ""
(lldb)
```
At this point in the code execution,
the constructor argument `name` is set to `Terry Jones`,
while `Student` member variable `name_` has been initialized
to an empty string, but it has not yet been assigned the value
passed to the constructor.

### Navigating through the code

We saw that command `continue` resumes the code execution
and gets us to the next break point. Command `next` will execute
the current and stop at the next line of the code. 
In this situation, the command `step` will do the same.
```
(lldb) next
   ...
   (some cryptic stuff)
   ...
   9   	  Student(std::string name, int studentID)
   10  	  {
   11  	    name_      = name; // set break point here
-> 12  	    studentID_ = studentID;
   13  	  }
   14  	
   15  	  // Destructor
(lldb) frame variable name_
(std::__1::string) name_ = "Terry Jones"
(lldb) step
   ...
   (some cryptic stuff)
   ...
   9   	  Student(std::string name, int studentID)
   10  	  {
   11  	    name_      = name; // set break point here
   12  	    studentID_ = studentID;
-> 13  	  }
   14  	
   15  	  // Destructor
(lldb)
```
The difference between commands `next` and `step` is if the next line
of the code is a function the command `next` will call the function and
stop at the next line of the code.
```
(lldb) next
   (...)
   32  	  // The instance of Student on the heap.
   33  	  Student* pGeographyStudent = new Student("Terry Jones", 123555);
   34  	
-> 35  	  delete pGeographyStudent;
   36  	    
   37  	  return 0;
   38  	}
(lldb) next
   (...)
   34  	
   35  	  delete pGeographyStudent;
   36  	    
-> 37  	  return 0;
   38  	}
(lldb) 
```
The command `step`, on the other hand, will step into
the function. You can use command `finish` to get out of
the function and back to the parent scope.
```
(lldb) next
   (...)
   32  	  // The instance of Student on the heap.
   33  	  Student* pGeographyStudent = new Student("Terry Jones", 123555);
   34  	
-> 35  	  delete pGeographyStudent;
   36  	    
   37  	  return 0;
   38  	}
(lldb) step
   (...)
   14  	
   15  	  // Destructor
   16  	  ~Student()
-> 17  	  {
   18  	    studentID_ = 0;
   19  	  }
   20  	
(lldb) finish
   (...)
   32  	  // The instance of Student on the heap.
   33  	  Student* pGeographyStudent = new Student("Terry Jones", 123555);
   34  	
-> 35  	  delete pGeographyStudent;
   36  	    
   37  	  return 0;
   38  	}
(lldb) step
   (...)
   34  	
   35  	  delete pGeographyStudent;
   36  	    
-> 37  	  return 0;
   38  	}
(lldb) 
```
Let us quickly summarize execution commands:

- `run` -- launches the code execution.
- `continue` -- continues code execution from the current position in the code.
- `next` -- executes the current line of the code and moves to the next line.
- `step` -- executes the current line of the code and steps into the function
if the current line is a function call.
- `finish` -- leaves current scope and moves to the next line in the parent scope.


### Setting a watchpoint

Sometimes we want to be alerted whenever certain variable changes.
This is when the command `watchpoint` comes to help. Let's assume
we want to track changes to the student number of our Geography
student, that is we want to see how member variable `studentID_`
changes in Geography student instance of the class `Student`.
First we put a break point in the constructor to stop the execution
just after `studentID_` is initialized, and then we look for
its memory address.
```
(lldb) run
   ...
   8   	  // Constructor
   9   	  Student(std::string name, int studentID)
   10  	  {
-> 11  	    name_      = name; // set break point here
   12  	    studentID_ = studentID;
   13  	  }
   14  	
(lldb) frame variable &studentID_
(int *) &studentID_ = 0x00007fff5fbffa70
(lldb) 
```
Then we set a watchpoint to that address, so that we break
every time the value on that address is updated.
```
(lldb) watchpoint set expression -- 0x00007fff5fbffa70
Watchpoint created: Watchpoint 1: addr = 0x7fff5fbffa70 size = 8 state = enabled type = w
    new value: 4294967400
(lldb) 
```
Now, as we continue the execution, the debugger will stop after each
change to `studentID_`.
```
(lldb) continue
Process 28492 resuming

Watchpoint 1 hit:
old value: 4294967400
new value: 4295090740
Process 28492 stopped
   (...)
   10  	  {
   11  	    name_      = name; // set break point here
   12  	    studentID_ = studentID;
-> 13  	  }
   14  	
   15  	  // Destructor
   16  	  ~Student()
(lldb) continue
Process 28492 resuming

Watchpoint 1 hit:
old value: 4295090740
new value: 4294967296
Process 28492 stopped
   (...)
   16  	  ~Student()
   17  	  {
   18  	    studentID_ = 0; // set break point here
-> 19  	  }
   20  	
   21  	private:
   22  	  std::string name_; // Student's name
(lldb)
```

### Backtrace

This is another quite useful debugging command. Sometimes,
you will mess up your pointers and your code will crash
with segmentation fault. One such example is given in
`student2.cpp` file. This code crashes with a segmentation
fault:
```sh
$ ./student2
Segmentation fault: 11
```
We recompile the code with proper flags
and launch it in the debugger.
```
(lldb) run
Process 28588 launched: '/Users/peles/cme212/debugging/student2' (x86_64)
Process 28588 stopped
   (... lots of stuff ...)
   1661	
   1662	    _LIBCPP_INLINE_VISIBILITY
   1663	    bool __is_long() const _NOEXCEPT
-> 1664	        {return bool(__r_.first().__s.__size_ & __short_mask);}
   1665	
   1666	#if _LIBCPP_DEBUG_LEVEL >= 2
   1667	
(lldb)
```
This is not very helpful, so we use `backtrace`.
```
(lldb) thread backtrace
   ( ... even more stuff ... )
    frame #2: 0x0000000100001c07 student`std::__1::basic_string<char,
    std::__1::char_traits<char>, std::__1::allocator<char> > std::__1::operator
    +<char, std::__1::char_traits<char>, std::__1::allocator<char> >
    (__lhs="", __rhs=" ") + 359 at string:3978
    frame #3: 0x0000000100001462 student2`Name::getName(this=0x0000000000000000)
    const + 50 at student2.cpp:25
    frame #4: 0x000000010000117f student2`Student::getName(this=0x0000000100104b40)
    const + 31 at student2.cpp:62
    frame #5: 0x0000000100000ce8 student2`main + 456 at student2.cpp:77
    frame #6: 0x00007fff970965c9 libdyld.dylib`start + 1
(lldb)
```
We get even more mess than before, but here we can recognize some things.
Reading the backtrace output from the bottom up, we first find that the
problem started in function `main` on line 77 in file `student2.cpp`.
We then find that the issue was in the call to `Student::getName` on
line 62 and `Name::getName` on line 25. Since we now narrowed down the problem
to accessing the student's name, we have much better chances of finding the actual bug on line 45,
where we accidentally set pointer to `Name` class to `nullptr` value.

## Reading

* [Glossary of LLDB and GDB commands](https://lldb.llvm.org/lldb-gdb.html)
* [LLDB Tutorial](https://lldb.llvm.org/tutorial.html)
* [Debugging with GDB](https://www.gnu.org/software/gdb/)
