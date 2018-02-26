# CME 212: Lecture 17

## Floating Point Representation ##

Floating point data types are finite precision approximations
for real numbers. C++ standard recognizes three fundamental floating
point data types:
* `float` - single precision floating point type
* `double` - double precision floating point type
* `long double` - extended precision floating point type
The C++ standard does not specify the representation or even
the precision of these three types. The C++ standard only says that:
> "The type double provides at least as much precision as float, and the 
> type long double provides at least as much precision as double. The set
> of values of the type float is a subset of the set of values of the type
> double; the set of values of the type double is a subset of the set of
> values of the type long double.
Floating point type representation may vary from compiler to compiler.
Many compilers follow [IEEE-754](http://grouper.ieee.org/groups/754/index.html)
standard in their floating point types implementation. In most cases
* `float` will be 32-bit long and have 7 decimal significant digits in its mantissa,
* `double` will be 64-bits long with 15 decimal significant digits in its mantissa.
Most common representations of `long double` type are 80-bit and 128-bit long.

### Floating point literals ###

By default, any literal number with a decimal point is interpreted as `double`.
To make compiler interpret a literal as a `float` or `long double`, one needs to
postpend it with `F` or `L`, respectively. Floating point number can be written
in an exponential form, as well. For example, `1234.5F` can be written as
`1.2345e3F`. Literals without decimal point and not written in an exponential
form are interpreted as integers. Here are a few examples:
```c++
auto x = 3.14;   // double
auto y = 3.14F;  // float
auto z = 3.14L;  // long double
auto u = 314L;   // long int
auto v = 314.L;  // long double
auto w = 3.14e2L // long double
```

### Floating point arithmetics is not associative ###

Due to fixed precision and round-off errors, associativity of 
addition and multiplication is not preserved in floating point
representations. Let's take a look at this simple example:
```c++
  float a = (1e-8F +  1.0F) - 0.99999F;
  float b =  1e-8F + (1.0F  - 0.99999F);
  std::cout << "a = " << a << "\n";
  std::cout << "b = " << b << "\n";
```  
On my machine, the output looks like this:
```
a = 1.00136e-05
b = 1.00236e-05
```
Since the mantissa of `float` has 7 significant digits, the sum of `1e-8F` and
`1.0F` will be truncated to `1.0F`. Similarly, the difference between
`1.0F` and `0.99999F` will have only 3 significant digits left. The rest will
be an artifact of the truncation.

When computing `b`, the difference between `1.0F` and `0.99999F` will again be
10^-5^ evaluated with only 3 correct digits due to finite precision truncation.
Adding the literal `1e-8F` will this time change the result as it falls within
the mantisa of `b`.

The results for `a` and `b` have the same number of significant digits and
they agree to within truncation error, but they provide different
representation of the number 1.001 x 10^-5^. This example illustrates that
associativity of addition and multiplication is not a representation invariant
of the floating point number.

### Comparing floating point numbers ###

Since during a computation different floating point representations can be used
to describe the same real number, one needs to be careful when implementing
representation of a real number comparison. The rule of thumb is never assume two
floating point numbers are equal. This is somewhat tongue in cheek statement,
but take a look at this example:
```c++
  double i = 0.0;
  while (i != 1.0)
  {
    i += 0.1;
    std::cout << i << "\n";
  }
```
With most compilers this will be an infinite loop. The decimal number 0.1
has a binary representation with infinite number of digits 0.00011001100110011...
Because of the truncation error, summing this value ten times will not produce
exactly one, and the loop condition above will always be true.

When implementing comparison representation, we have to account for the truncation
error. For example, if checking if two real numners are equal, we should check
if they agree to within some tolerance that represents the truncation error.
Let us modify our look like this:
```c++
  double i = 0.0;
  while (std::abs(i - 1.0) > 1e-14)
  {
    i += 0.1;
    std::cout << i << "\n";
  }
```
Now, we are checking if 1 - 10^-14^ < i < 1 + 10^-14^. The value of
10^-14^ is too small to affect our computation, but big enough to
account for the truncation error. Unfortunately, there are no simple
rules how to set comparison tolerances. The truncation error may accumulate
or cancel out depending on the computation, so the comparison tolerance will
be very much computation dependent. 


### Numerical limits ###

Standard template library provides class `numeric_limits` that contains
methods and constants that provide information on compiler representation
of numeral data types. 
In file [limits.cpp](src/limits.cpp) we show example usage of the
`numeric_limits` class. This code provides basic information about
floating point types implementation. On my machine, using clang compiler
the output looks like this:
```
		min		max		mantisa	exp min	exp max	radix
float		1.17549e-38	3.40282e+38	6	-37	38	2
double		2.22507e-308	1.79769e+308	15	-307	308	2
long double	3.3621e-4932	1.18973e+4932	18	-4931	4932	2
```
More information about `numeric_limits` class can be found at
[cppreference.com](http://en.cppreference.com/w/cpp/types/numeric_limits).


### Reading ###


* [Wikipedia article on C data types](https://en.wikipedia.org/wiki/C_data_types).
