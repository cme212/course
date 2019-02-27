# CME 212: Lecture 15

## Code optimization

The compiler is a fundamental tool:
* performs several types of optimization
* in general, produces far better assembly code than people
* knows the hardware to some extent

Modern hardware attempts to run code as fast as possible with:
* pipelining
* instruction level parallelism
* out-of-order execution
* caching in fast memory

Programmer’s job:
* first make the program work
* write code in a way that does not block efforts of compiler and
CPU
* use profiler to identify bottlenecks and optimize the code

## Best practices

* Premature optimization is root of all evil! Do not optimize prematurely.
Make the program work first, this is most important.
* Selecting a fast algorithm will do more than optimizing a slow algorithm.
An algorithm that scales linearly with input data will do better than one
that scales quadratically.
* Code readability is extremely important. Avoid sacrificing code readability
for performance. Developer time is still more expensive than computer time.
* Most of the time we just try to avoid certain blockers that limit compiler
optimization and hardware capabilities.

## The compilation process


## Intermediate representation

During compilation, the source code is first transformed into a sequence of
"atomic" instructions. This *intermediate representation* helps compiler
optimize execution of *abstract* instructions specified in the source code.
The difference between intermediate representation and the assembly code
is that the intermediate representation is hardware agnostic, while the
assembly code is specific to the hardware platform where the source code
is compiled. The intermediate representation allows compiler developers to
write different language (C, C++, Fortran, etc.) frontends and different
hardware backends, while reusing the same optimization engine.

A simple model of intermediate representation consists of a stream of
quadruples (_op_, _o1_, _o2_, _r_), where _op_ is an operator,
_o1_ and _o2_ are operands, and _r_ is the result of the operation.

### Simple example

The line of C++ code
```c++
    a = -b + c * d / e;
```
could be rewritten as a series of atomic instructions like this:
```
  T1 := D / E
  T2 := C * T1
  T3 := -B
  A :=T3+T2
```
Each statement in this representation fits into a quadruple.

### Loop example

Consider a simple while-loop:
```c++
while (j < n)
{
  k = k + j * 2;
  m = j * 2;
  j++
}
```
It's intermediate representation may look something like this:
```
A:: t1 :=j
    t2 :=n
    t3 :=t1<t2
    jmp (B) t3
    jmp (C) TRUE

B:: t4 :=k
    t5 := j
    t6:=t5*2
    t7 :=t4+t6
    k :=t7
    t8 :=j
    t9 :=t8*2
    m :=t9
    t10 := j
    t11 := t10 + 1
    j :=t11
    jmp (A) TRUE
C::
```
Here `A::`, `B::` and `C::` are labels of atomic instructions,
`+` and `*` are arithmetic operators, and `:=` is the assignment
operator. Command `jmp(LABEL) value` jumps to the command labeled
with `LABEL` if `value` is boolean `TRUE`.


## Compiler optimization

Most common compiler optimization methods include:
* Copy propagation
* Constant folding
* Dead code removal
* Strength reduction
* Variable renaming
* Common subexpression elimination
* Loop-invariant code motion
* Induction variable simplification
* Loop unrolling
* Vectorization

While modern day compiler optimizers will perform these
automatically, it is desirable that the developer do as much
of the optimization herself as possible. More importantly,
the developer should be careful not to write her code in the way
that will prevent compiler from doing some of the optimizations.

### Copy propagation

Consider following code snippet:
```
X = Y;
Z = 1.0 + X;
```
Changing order of these instructions will change the result of
the computation. This gives compiler less flexibility to optimize
the code that includes this snippet. To remove this restriction,
the compiler can *propagate* a copy of `Y` and transform this
code as:
```
X = Y;
Z = 1.0 + Y;
```
Now the two statements can be executed in any order or in parallel.


### Constant folding

Consider this code:
```c++
int const i = 100;
int k = 200;

// code not modifying k
...

int j = i + k;
```
The compiler should recognize that `k` does not change before
`j` is defined. Since `i` is defined as constant, the compiler
will replace the statement `i + k` with literal `300` and eliminate
the addition operation at runtime. If `k` is modified before the
definition of `j`, the compiler will replace only `i` with literal
`100` in the initialization of `j`.

Using `const` keyword proactively in your code will help compiler
perform more aggressive optimization. It will also lead to more
readable, "self documenting" code.

### Dead code removal

This should be a no brainer. Look at the following code:
```c++
main ()
{
  int i, k;
  i = k = 1;
  i += 1;
  k += 2;
  printf ("%d\n",i);
  if ( 1==0 ) printf("I am not going to be printed\n");
}
```
Variable `k` is defined and modified, but never *used*. Therefore,
it could be removed from the code. Next the `if` statement is
always false, so the second `printf` command will never be executed.
The compiler will typically remove the dead code and give you a warning.
It is a good coding practice to identify and remove dead code from
your source and not let compiler do it for you. If the code is complex,
the compiler may fail to find and remove some of the dead code.

### Strength reduction

It is tempting to use `std::pow` function to compute integer powers of
floating point numbers. For example:
```c++
double x = 7.0;
double x2 = pow(x, 2);
```
To compute an arbitrary floating point power _x<sup>y</sup>_,
the compiler will execute something like this: `exp(y*log(x))`.
Executing `pow` function takes order of 100 clock cycles, while
multiplication `x*x` takes 4-6 cycles, depending on the compiler.
A good compiler will recognize integer literal as the argument for
power, and replace `pow(x,2)` with `x*x`, thus reducing the
computation "strength".

Again, it is recommended that developer performs strength reduction
for as long as it will not significantly obscure the code.


### Variable renaming

The compiler may rename variables to keep unrelated statements
separate. Consider code:
```c++
tmp = y * z;
q = r + tmp + tmp;
tmp = a + b;
```
The last statement is unrelated to previous two, but we
decided to reuse variable name `tmp`. Rename `tmp` in the
last statement to `tmp2`:
```c++
tmp = y * z;
q = r + tmp + tmp;
tmp2 = a + b;
```
Now the last statement is decoupled from the previous two, and
it can be executed in different order or in parallel with either
of other two statements.


### Common subexpression elimination

A compiler can recognize that certain subexpression repeats in the
code. In that case compiler evaluates that subexpression once, stores
the result in a temporary variable, and substitutes that variable for
the subexpression elsewhere in the code to avoid repeating same
calculation over. Take, for example code
```c++
D = C * (A + B);
E = (A + B)/2.0;
```
The compiler recognizes `A + B` repeats, so it changes the intermediate
representation to avoid repeated addition:
```c++
temp = A + B;
D = C * temp;
E = temp/2.0;
```
Note that changing order of floating point computations will
result in different truncation error, the optimized code will not
produce bit-exact results as the unoptimized code.


### Moving loop-invariant code

A compiler will move loop-invariant code outside the loop
in order to avoid performing redundant repeated operations.
For example, in loop
```c++
for(int i=0; i != n; ++i)
{
  a[i] = b[i] + c * d;
  e = g[k];
}
```
expression `e = g[k]` is invariant to loop iterations, therefore one
assignment operation will produce the same result as `n` of them.
Taking the assignment outside the loop will eliminate redundant
operations:
```c++
for(int i=0; i != n; ++i)
{
  a[i] = b[i] + c * d;
}
e = g[k];
```


### Induction variable simplification

Consider loop

```c++
for(int i=0; i != n; ++i)
{
  k = i*4 + m; // 3 operations per loop iteration
  ...
}
```
The induction value `k` is computed in (at least) three
steps -- multiplication of `i` by 4, addition to `m`, and
assignemt of the result to `k`. A good compiler can "rewrite"
the loop to reduce the number of computations per loop iteration:
```c++
k = m-4;
for(int i=0; i != n; ++i)
{
  k += 4; // 1 operations per loop iteration
  ...
}
```
Here there is only one in-place addition per loop iteration.


### Loop unrolling

Loop unrolling is an optimization which partially unrolls the loop
in order to avoid loop's overhead. Consider a simple loop

```c++
sum = 0;
for(int i=0; i != n; ++i)
{
  sum += data[i];
}
```
By rewriting this loop as
```c++
sum0 = 0; sum1 = 0; sum2 = 0; sum3 = 0;
for(int i = 0; i < n; i += 4)
{
  sum0 += data[i];
  sum1 += data[i+1];
  sum2 += data[i+2];
  sum3 += data[i+3];
}
sum = sum0 + sum1 + sum2 + sum3;
```
we reduce number of loop iterations, and therefore the loop overhead,
by 4 times. Also, the four summations inside the loop are independent
of each other and can be executed in any order or in parallel. This
allows the compiler to perform further, more aggressive optimization.


### Vectorizing

In order to speed up computtions, compilers sometimes perform
operations on data blocks rather than on individual array elements.
This is called vectorizing. Consider a simple loop
```c++
for(int i=0; i < n; ++i)
{
  C[i] = A[i] + B[i];
}
```
Vectorization will turn this loop into something like this
```c++
for(int i=0; i < n; i += 4)
{
  C[i:i+4] = A[i:i+4] + B[i:i+4];
}
```
Here we borrow Matlab notation to denote operations on data
ranges.

Vectorization is done by compiler automatically. However, a developer
can write code that is more or less likely to be vectorized by the compiler.
For example, compiler may not be able to vectorize this loop:
```c++
for(int i=0; i < n; ++i)
{
  C[i] =  i > 0   ? A[i-1] : 0;
  C[i] += i < n-1 ? B[i+1] : 0;
}
```
But, if we pad array `A` with a zero on the left, pad array `B` with
a zero on the right, and allocate array `C` with `n+1` elements,
we can rewrite the loop above as
```c++
for(int i=0; i < n+1; ++i)
{
  C[i] = A[i] + B[i];
}
```
This loop is more likely to be vectorized by the compiler.
