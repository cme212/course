# CME 212: Lecture 06

## Code Specification

Specifications inform a user about a class or function, but do not refer
to its internal workings. That is, a specification will refer to abstract
behavior and not private implementation properties.

In this class, we will use Doxygen comment style specifications.
Doxygen is a tool for generating HTML or PDF documentation from comments
in the source code. To get a quick start with Doxygen, take a look at
[Documenting the Code](http://www.doxygen.nl/manual/docblocks.html)
section of the Doxygen manual.

Let us take a look at the Doxygen formatted comments in front of a C++ function:
```c++
/**
 * @brief <BRIEF DESCRIPTION>
 *
 * @param <NAME> <DESCRIPTION>
 * @tparam <NAME> <DESCRIPTION>
 * @return <DESCRIPTION OF RETURN VALUE>
 *
 * @pre <PRECONDITION>
 * @post <POSTCONDITION>
 *
 * LONGER DESCRIPTION, RUNTIME, EXAMPLES, ETC 
 */
bool signature(of& my_method)
```
In this example:
* `@brief` marks the text that will be displayed in summaries and index lists. Typically you would put here a few words description
of your function.
* `@param` describes a function parameter and takes an optional direction: `@param[in]` means the parameter's value is only read and not modified within the function, `@param[out]` means the parameter is not read and is only modified, and `@param[in,out]` means the parameter is both read and modified.
* `@pre` and `@post` define the pre- and postconditions, which should be precise but brief. When in doubt, attempt rigorous conditions but keep in mind that some concepts such as "validity" may be difficult or impossible to define precisely. Specifications are primarily for human consumption.
* `@param`, `@pre`, and `@post` sections should be repeated as many time as required.
* In any section, a parameter can be referred to by name with underscores, e.g. `_paramname_`. This helps disambiguate short parameter names by identifying them in the text and highlighting them in the Doxygen output. For instance, 
```c++
 * @return The size of _a_
```
is clearer than 
```c++
 * @return The size of a
```
when read in plain text and in formatted documentation.

*Note*: Older versions of Doxygen used command `@a` to change the font of the following word
to italics. Since newer versions of Doxygen support markdown syntax, it is recommended to
use `_ ... _` instead of `@a ...` to italicise text. 

To refer to values that change during the operation of the method we use `old X` and `new X`. Here, `old X` (where `X` may be a parameter, global variable, member variable, etc) refers to the value of `X` at the point of call, before the function executes, while `new X` refers to the value of `X` at the point of return, immediately after the function executes. For instance, postconditions will often define `new X` in terms of `old X`. 

To refer to a function's return value we use `result`.

### Specifications and Binary Search Example ###

We started this class developing these concepts in the context of a particular example: binary search. Let's start with the first implementation provided in [search0.cpp](src/search0.cpp):
```c++
int binary_search(float* a, int n, float v) {
  int low = 0;
  int high = n-1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (a[mid] < v)
      low = mid + 1;
    else if (a[mid] > v)
      high = mid - 1;
    else
      return mid;   // Value found
  }
  return -1;        // Value not found
}
```
There are a couple of bugs in this code that often go undetected. In the computation of `mid`, if the sum of low and high is greater than `2^{31}-1`, then the `int` type will overflow without warning! To fix this common mistake, we can replace that line with
```c++
int mid = low + (high - low) / 2;
```
The other, more serious bug is that the floating point numbers are compared directly. Due to round-off
error, two floating point numbers may be computed to slightly different values even when
mathematically they should be the same. See the example in [roundoff.cpp](src/roundoff.cpp).
Because of that, checking if the two floating point
numbers are equal, will often produce misleading results. To account for the truncation error,
we assume the two floating point numbers are equal if they agree to within some tolerance.
To ensure comparisons in our function are meaningful, we rewrite the conditionals as
```
    if (a[mid] < v - eps)
      low = mid + 1;
    else if (a[mid] > v + eps)
      high = mid - 1;
    else
      return mid;   // Value found
```
Here `eps` is a small positive number, chosen based on typical round-off error for
elements of the array `a`.

We want our coworkers to use our method without having to understand every detail of our implementation. In order for this to be feasible, we should write out specifications for `binary_search` that give more information about the inputs and the return value:
```c++
/** 
 * @brief Search a sorted array for a value using binary search.
 *
 * @param a  Sorted array of floats.
 * @param n  Number of elements of _a_ to search.
 * @param v  Value to find in _a_.
 * @return   An index into array _a_ or -1.
 */
```
In the above specification, we've used `_a_` in our Doxygen-style comments to emphasize the parameters within each statement.

But this isn't complete! `binary_search` assumes a number of things about it's inputs. These are preconditions -- statements about the inputs that must be true before the function is even called. An obvious precondition restricts the values of `n` that are allowed:
```c++
 * @pre 0 <= n < Size of _a_.
```
Note that even this simple statement is doing something interesting: appealing to abstract information about the array that the function does not have access to! By using a pointer to pass the array of values, the true size of the array is not accessible. Still, the user must guarantee this precondition is satisfied before using our function.

A more slippery precondition is that binary search assumes array `a` is sorted. Let's add this precondition to our specification:
```c++
 * @pre Array _a_ is sorted.
```
But this isn't good enough either! The array has to be in a specific order. For instance, if the array were sorted in descending numeric order the search will shoot to the wrong end of the array. We need:
```c++
 * @pre Array _a_ is sorted in ascending order.
```
or, more formally and equally as valid:
```c++
 * @pre For all i,j with 0 <= i < j < n, _a_[i] <= _a_[j].
```
In order to guarantee that our function will work, the user must satisfy the two preconditions.

Alright, what about postconditions for `binary_search`? Postconditions are statements that must be true after a piece of code has been run. What statements must the result of a sane binary search function satisfy? The obvious statement is
```c++
 * @post Either _a_[result] == _v_ or result == -1.
```
We use `result` here to denote the return value of the function. This avoids having to refer to the internal implementation of `binary_search` -- a specification should never refer to `mid`, for example. The specification of a function should be _independent of its implementation_.

The postcondition above is not sufficient though... Consider the following implementation of `binary_search`:
```c++
/** 
 * @brief Search a sorted array for a value using binary search.
 *
 * @param a  Sorted array of floats.
 * @param n  Number of elements of _a_ to search.
 * @param v  Value to search for.
 * @return   An index into array _a_ or -1.
 * 
 * @pre 0 <= n <= Size of _a_.
 * @pre For all i,j with 0 <= i < j < _n_, _a_[i] <= _a_[j].
 * @post Either _a_[result] == _v_ or result == -1.
 */
int binary_search(float* a, int n, float v) {
  return -1;
}
```
This satisfies the postcondition! It is a valid implementation given our specification! Oops.

The problem *is not* that our function is implemented incorrectly. Given
the specifications it is correct. Period. The problem is that the 
postcondition does not sufficiently constrain the implementation of the 
function. Ok, a better postcondition:
```c++
 * @post _a_[result] == _v_ or (result == -1 and _v_ is not in _a_).
```
or even more formally,
```c++
 * @post _a_[result] == _v_ 
 *    or (result == -1 and there is no _i_ s.t. 0 <= _i_ < _n_ and _a_[i] == _v_).
```
In class, we also mentioned the weird possibility of `result` being chosen outside of the bounds of the array. To fully cover our bases, we found the following post-condition to be the strongest and most descriptive:
```c++
 * @post (0 <= result < _n_ and _a_[result] == _v_) 
 *    or (result == -1 and there is no _i_ s.t. 0 <= _i_ < _n_ and _a_[i] == _v_).
```
Does this finally sufficiently constrain our function? Well... how about this implementation:
```c++
int binary_search(float* a, int n, float v) {
  a[0] = v;
  return 0;
}
```
This can be repaired: we need to insure that the array is immutable. By changing the signature of the function and, in our specifications, noting that each parameter is read-only, we can promise to the user (and the compiler!) that we will not change the values within the array. A final, solid version of `binary_search` might look like this (see also [search1.cpp](src/search1.cpp)):
```c++
/** 
 * @brief Search a sorted array for a value using binary search.
 *
 * @param[in] a   Sorted array of floats.
 * @param[in] n   Number of elements of _a_ to search.
 * @param[in] v   Value to search for.
 * @param[in] eps Equality tolerance
 * @return    An index into array _a_ or -1.
 * 
 * @pre 0 <= _n_ <= Size of the array _a_.
 * @pre For all i,j with 0 <= i < j < _n_, _a_[i] <= _a_[j].
 * @post (0 <= result < _n_ and _a_[result] == _v_) 
 *    or (result == -1 and there is no _i_ s.t. 0 <= _i_ < _n_ and _a_[i] == _v_).
 *
 * The complexity of the serach algorithm is O(log(n))
 */
int binary_search(const float* a, int n, float v, float eps) {
  int low = 0;
  int high = n-1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (a[mid] < v - eps)
      low = mid + 1;
    else if (a[mid] > v + eps)
      high = mid - 1;
    else
      return mid;   // Value found
  }
  return -1;        // Value not found
}
```

### Invariants ###

An **invariant** is a statement that is always true at a particular point in the code. Stating and enforcing invariants within code are useful for catching bugs and generally reasoning about code behavior.

A **precondition** is an invariant that holds when a function is called. A function's precondition is a part of the contract with the users and constrains its caller: if the caller does not obey the precondition, then all bets are off and the function can do whatever it likes.

A **postcondition** is an invariant that holds when a function returns, provided all preconditions were met. A function's postcondition is the other part of the contract with the users but constrains the function itself: assuming the caller obeyed the precondition, the function must ensure that the postcondition holds.

Implicit preconditions and postconditions don't need to be stated. All functions have the implicit precondition that memory has not been corrupted. All functions have the implicit postcondition that they don't modify seemingly-unrelated state; for instance, if a function modifies a global variable, this should be listed explicitly in the specification.

An **assertion** is a checked invariant. The command 
```c++
assert(X);
```
checks that `X` is true, and aborts the program if `X` is false. Not all invariants can or should be checked with assertions. For instance, verifying that the input array is sorted has _O_(_n_) complexity, while our specification promises _O_(log(_n_)) complexity for our function. Assertions should generally be side-effect free -- they should not modify program state. This is so they can be turned off for production code.



### Generic Programming ###

Let's start with the binary search function we defined in the previous post.
```c++
/** 
 * @brief Search a sorted array for a value using binary search.
 *
 * @param[in] a   Sorted array of floats.
 * @param[in] n   Number of elements of _a_ to search.
 * @param[in] v   Value to search for.
 * @param[in] eps Equality tolerance
 * @return    An index into array _a_ or -1.
 * 
 * @pre 0 <= n <= Size of the array _a_.
 * @pre For all i,j with 0 <= i < j < _n_, _a_[i] <= _a_[j].
 * @post (0 <= result < _n_ and _a_[result] == _v_) 
 *    or (result == -1 and there is no _i_ s.t. 0 <= _i_ < _n_ and _a_[i] == _v_).
 *
 * The complexity of the serach algorithm is O(log(n))
 */
int binary_search(const float* a, int n, float v, float eps) 
{
  int low = 0;
  int high = n-1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (a[mid] < v - eps)
      low = mid + 1;
    else if (a[mid] > v + eps)
      high = mid - 1;
    else
      return mid;   // Value found
  }
  return -1;        // Value not found
}
```
In class, we pointed out limitations of the above implementation. Namely,

* `binary_search` is only called on full arrays, or at least on ranges `0,...,n-1` of an array.
* `binary_search` only applies to a specific type, namely `float`. Writing one function for each type is undesirable.
* `binary_search` only applies to arrays that are sorted in ascending order. What about descending order, lexicographical order, etc?
* `binary_search` only applies to data stored in an array.

A simple modification addresses the first point (see [search2.cpp](src/search2.cpp)). 
The complete specification for the modified code is:
```c++
/** 
 * @brief Search a sorted array for a value using binary search.
 *
 * @param[in] a         Sorted array of floats.
 * @param[in] low,high  Search in the index range [low, high).
 * @param[in] v         Value to search for.
 * @param[in] eps       Equality tolerance
 * @return    An index into array _a_ or -1.
 * 
 * @pre 0 <= low < high <= Size of the array _a_.
 * @pre For all i,j with low <= i < j < high, _a_[i] <= _a_[j].
 * @post (low <= result < high and _a_[result] == _v_) 
 *    or (result == -1 and there is no _i_ s.t. 0 <= _i_ < _n_ and _a_[i] == _v_).
 *
 * The complexity of the serach algorithm is O(log(high - low))
 */
int binary_search(const float* a, int low, int high, float v, float eps)
```
To address the second point, we note that the body of the function (and the complete specification) applies equally well to numeric types: `int`, `unsigned`, `float`, `double`. Using C++ templates (parametric polymorphism), we lift this function from being implemented for a specific type to being a family of functions that can be used for (nearly) any type:
```c++
/** 
 * @brief Search a sorted array for a value using binary search.
 *
 * @param[in] a         Sorted array to search.
 * @param[in] low,high  Search in the index range [low, high).
 * @param[in] v         Value to search for.
 * @param[in] eps       Equality tolerance
 * @return    An index into array _a_ or -1.
 * 
 * @pre 0 <= low < high <= Size of the array _a_.
 * @pre For all i,j with low <= i < j < high, _a_[i] <= _a_[j].
 * @post (low <= result < high and _a_[result] == _v_) 
 *    or (result == -1 and there is no _i_ s.t. 0 <= _i_ < _n_ and _a_[i] == _v_).
 *
 * The complexity of the serach algorithm is O(log(high - low))
 */
template <typename T>
int binary_search(const T* a, int low, int high, const T& v, const T& eps)
{
  --high;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (a[mid] < v - eps)
      low = mid + 1;
    else if (a[mid] > v + eps)
      high = mid - 1;
    else
      return mid;   // Value found
  }
  return -1;        // Value not found
}
```
The parameter `T` takes over the roll of the previously constant `float` type. The compiler detects which type `T` we need and stamps out the appropriate function for us! We have not changed the body of the function because it applies equally well when `T` is an `int`, `unsigned`, `float`, `double`, etc.
```c++
int* a_i = ...;
int idx = binary_search(a_i, 0, n, 5, 0);        // Generates binary_search(int*, int, int, int)
float* a_f = ...;
idx = binary_search(a_f, 0, n, 3.2f, 1e-10f);    // Generates binary_search(float*, int, int, float)
idx = binary_search(a_f, 0, n, 3.2, 1e-10f);     // Error: conflicting types for parameter 'T'
idx = binary_search<float>(a_f, 0, n, 3.2, 1e-9) // Generates binary_search(float*, int, int, float)
```
The `const T&` change in the above function is to prevent a copy in the case that `T` is a heavy object that would be expensive to copy. For example, `binary_search` now works with `std::string` objects because ` bool operator<(const std::string&, const std::string&)` is implemented in the standard library to perform lexicographical comparison!

In fact, the family of functions we defined can take on an infinite number of instantiations. 
The code will compile and function properly so long as the type `T` can be added, substracted,
and compared. That is, in `binary_search`, we used two comparison operators, as well as
addition and substraction operators that take two values of `T` as parameters:
```c++
bool operator<(const T& a, const T& b);
bool operator>(const T& a, const T& b);
T operator+(const T& a, const T& b);
T operator-(const T& a, const T& b);
```
If we want `binary_search` to work for a custom type, we need to make sure these
operators are implemented for that type. Let's document the requirement of type
`T`. See full implementation in [search3.cpp](src/search3.cpp).
```c++
/** 
 * Search a sorted array for a value using binary search.
 * 
 * @param[in] a         Sorted array to search.
 * @param[in] low,high  Search in the index range [ low,  high).
 * @param[in] v         Value to search for.
 * @param[in] eps       Equality tolerance
 * @return    An index into array _a_ or -1.
 *
 * @tparam T Type of the array elements
 * @tparam T Comparison operator defined: bool operator<(T,T)
 * @tparam T Comparison operator defined: bool operator>(T,T)
 * @tparam T Substraction operator defined: T operator-(T,T)
 * @tparam T Addition operator defined: T operator+(T,T)
 * 
 * @pre 0 <= low <= high <= Size of the array _a_.
 * @pre For all i,j with  low <= i < j < high,  a[i] <= a[j].
 * @post ( low <= result <  high and  a[result] ==  v within tolerance eps) 
 *    or (result == -1 and there is no _i_ s.t. low <= i < high, and a[i] == v).
 *
 * The complexity of the serach algorithm is O(high - low)
 */
template <class T>
int binary_search(const T* a, int low, int high, const T& v, const T& eps)
```
First, we see that if we slightly modify function `binary_search`, we can
reduce the requirements on the type `T`. Let us rewrite the conditional
statements as:
```c++
    if (a[mid] + eps < v)      // a[mid] < v
      low = mid + 1;
    else if (v + eps < a[mid]) // a[mid] > v
      high = mid - 1;
    else
      return mid;
```
Now, type `T` needs to implement only addition and "less than" operator.
The `binary_search` function can operate on _any_ data type that implements
these two operators. Fewer requirements make it easier and less error-prone
implement user-defined types that our `binary_search` can use.

Let us use `binary_search` with `Student` class defined in
[student.hpp](src/student.hpp), and let us try to find a student
in a classroom by their name. The `Student` class does not have
default comparison and addition operators, so we have to define them:
```c++
bool operator<(const Student& x, const Student& y)
{
  return (x.getName() < y.getName());
}

Student operator+(const Student& lhs, const Student& rhs)
{
  return Student(lhs.getName() + rhs.getName(), lhs.getStudentID());
}
```
Here we rely on `std::string` comparison and addition. With these
definitions, we can find a student in the classroom, provided the
classroom meets our preconditions:
```c++
  Student classroom[10];
  ...
  Student* john = new Student("Cleese, John", 100400);
  Student* tol = new Student("", 0); // Fake student with name ""
  ...
  int seat = binary_search(classroom, 0, 3, *john, *tol);
```
The full code is in [search4a.cpp](src/search4a.cpp). This is really
powerful. With minor coding effort we were able to deploy our `binary_search`
code for a quite different use case.

While comparing students, as we defined it, is quite intuitive, it does not
make much sense to "add" students. Furthermore, the addition we implemented
is not commutative. This is legal in C++, but it is a poor design choice.
It is so easy to introduce a hard to find bug by simply rewriting `v + eps`
as `eps + v`.

An alternative solution would be to have separate solution for floating point
types and types where a reliable comparison operator is defined without a
tolerance. The floating point types could use the code in 
[search4a.cpp](src/search4a.cpp) as before, while for the other types we could
overload `binary_search` like this (see [search4b.cpp](src/search4b.cpp)):
```c++
/** 
 * Search a sorted array for a value using binary search.
 * 
 * @param[in] a         Sorted array to search.
 * @param[in] low,high  Search in the index range [@a low, @a high).
 * @param[in] v         Value to search for.
 * @return    An index into array _a_ or -1.
 * 
 * @tparam T Type of the array elements
 * @tparam T Comparison operator defined: bool operator<(T,T)
 * @tparam T Not appropriate for floating point types
 *
 * @pre 0 <=  low <=  high <= Size of the array _a_.
 * @pre For all i,j with  low <= i < j <  high,  a[i] <= a[j].
 * @post ( low <= result <  high and  a[result] ==  v) 
 *    or (result == -1 and there is no _i_ s.t. low <= i < high, and a[i] == v).
 *
 * The complexity of the serach algorithm is O(log(n))
 */
template <class T>
int binary_search(const T* a, int low, int high, const T& v)
```
In the type specification, we require that the overloaded method
should not be used with floating point data types. At the same
time, we drop the requirement to have the addition operator implemented.
The downside of this solution is it introduces some code duplication.
It is developers responsibility to weigh pros and cons and
make the design decision accordingly.

The take home message is that we make assumptions in our code all the time.
When making code generic, even simple abstractions can have profound
consequences and these assumptions can be of critical importance.


