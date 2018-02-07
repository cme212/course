# CME 212: Lecture 12

## Inheritance and Polymorphism ##

Inheritance is a fundamental motif in object oriented programming.
It allows a class to inherit member variables and methods from another
class, so that we do not have to replicate those multiple times.
The inheritance can be described as *is-a* relationship. For
example, a triangle is a shape. Or, student is a scholar. Let us explain
basics of inheritance in a simple example. Consider the class `Rectangle`
in example code [inheritance_none.cpp](src/inheritance_none.cpp):
```c++
class Rectangle
{
public:
  Rectangle(double width, double length)
    : width_(width),
      length_(length),
      area_(width_*length_)
  {
  }

  ~Rectangle()
  {
  }

  /// Same method exists in Circle class.
  double getArea()
  {
    return area_;
  }

private:
  double width_;
  double length_;
  double area_;  ///< Same member exists in Circle class
};
```
and the class `Circle`:
```c++
class Circle
{
public:
  Circle(double x, double y, double radius)
    : radius_(radius),
      area_(radius_*radius_*M_PI)
  {
  }

  ~Circle(){}

  /// Same method exists in Rectangle class.
  double getArea()
  {
    return area_;
  }

private:
  double radius_;
  double area_;  ///< Same member exists in Circle class
};
```
Each class represents a shape, has member variable `area_`,
and has method `getArea()`. If we want to add more shapes (e.g. triangles),
we would need to replicate the same variable and the same method
for those shapes, too, because all shapes have an area. If we
want to add another general shape property (e.g. color), we would
have to add it to all classes representing shapes that we created.
This will cause our code to grow quickly as we add more features,
and that will in turn make maintenance of our code expensive.

### Inheritance ###

The inheritance allows us to implement all the common features
of our objects in a *base* class. A *derived* class will need to
implement only its own specific features thus leading to a leaner
and easier to maintain code. We can, for example, create class
`Shape` like this:
```c++
class Shape
{
public:
  Shape()
    : area_(0.0)
  {
    std::cout << "Invoking Shape constructor ...\n";
  }
  
  ~Shape()
  {
    std::cout << "Invoking Shape destructor ...\n";
  }

  double getArea()
  {
    return area_;
  }

protected: // protected instead of private     
  double area_;
};
```
Note that variable `area_` is now *protected* rather than
*private* member. Now, we can create a class `Circle`, which
*is a* `Shape` by declaring it as
```c++
Circle : public Shape
{
public:
  Circle(double radius)
    : radius_(radius)
  {
    std::cout << "Invoking Circle constructor ...\n";
    area_ = radius_*radius_*M_PI;
  }

  ~Circle()
  {
    std::cout << "Invoking Circle destructor ...\n";
  }

  double getRadius()
  {
    return radius_;
  }
  
private:
  double radius_;
};
```
The class `Circle` will inherit member variables and functions from
`Shape`, and all public methods and variables from `Shape` will also
be public in `Circle`. We defined variable `area_` as *protected* so
it is accessible by `Circle` and other classes that inherit from `Shape`.
If `area_` was private, `Circle` would inherit it, but it would not
be able to access it.
Note that accessibility in C++ is based on classes and not objects.
Therefore instances of the same class can access each other private
members.
In a similar manner, we can implement class `Rectangle` to inherit
from `Shape`. The complete code is provided in
[inheritance_public.cpp](src/inheritance_public.cpp). Let us look
at the execution of the following code calling shape classes:
```c++
#include <iostream>

int main()
{
  Circle*    pc = new Circle(1.0);
  Rectangle* pr = new Rectangle(3.0, 2.0);
  
  std::cout << "\n";
  std::cout << "Circle area = " << pc->getArea() << "\n";
  std::cout << "Circle radius = " << pc->getRadius() << "\n";
  std::cout << "Rectangle area = " << pr->getArea() << "\n";
  std::cout << "\n";

  delete pc;
  delete pr;

  return 0;
}
```
The output looks like this:
```
$ ./a.out 
Invoking Shape constructor ...
Invoking Circle constructor ...
Invoking Shape constructor ...
Invoking Rectangle constructor ...

Circle area = 3.14159
Circle radius = 1
Rectangle area = 6

Invoking Circle destructor ...
Invoking Shape destructor ...
Invoking Rectangle destructor ...
Invoking Shape destructor ...
$
```
Let us see what is going on here. We first invoke
constructors for `Circle` and `Rectangle`. Each derived
class constructor will first call the base class constructor,
which will be executed before the derived class constructor.
After we created a `Circle` and a `Rectangle`, we
can access their own and inherited public features alike.
When the destructor of a derived class is called, it will
call the destructor of the base class. The base class destructor
will be executed after the derived class destructor.
Let us now try something different. Consider code:
```c++
int main()
{
  Shape* pc = new Circle(2.0);

  std::cout << "\n";
  std::cout << "Circle area = " << pc->getArea() << "\n";
  //std::cout << "Circle radius = " << pc->getRadius() << "\n"; // Compiler error
  std::cout << "\n";

  delete pc; ///< Circle not destoryed, memory leak!
  
  return 0;
}
```
We create a `Circle` on the heap, but we access it through
a pointer to `Shape`. The output of this code looks like this:
```
Invoking Shape constructor ...
Invoking Circle constructor ...

Circle area = 12.5664

Invoking Shape destructor ...
```
With pointer to `Shape` as our handle to `Circle`, we can
access only methods that `Circle` inherited from `Shape`.
The compiler will not be aware that the object behind
pointer `pc` is actually a `Circle`. When we try to delete
the object, only `Shape` destructor will be invoked; the `Circle`
part of the object will remain on the heap, only now without a
pointer to access it. We got ourselves a memory leak.


### Virtual Functions and Polymorphism ###

Let us define `Shape` destructor as a virtual function:
```c++
  virtual ~Shape()
  {
    std::cout << "Invoking Shape destructor ...\n";
  }

```
If we recompile and rerun the earlier code with redefined `Shape`
destructor, the new output will be:
```
Invoking Shape constructor ...
Invoking Circle constructor ...

Circle area = 12.5664

Invoking Circle destructor ...
Invoking Shape destructor ...
```
Even though `Circle` was hiding behind a `Shape` pointer,
the executable was able to figure out at the runtime that
the `Shape` pointer was pointing to a `Circle`. With this
small modification to our code, we can now access any shape
object using only `Shape` pointer without introducing a memory
leak. Furthermore, we will be able to override any other
virtual function in the derived class, and still be able to
access it through the pointer to the base class. This is
called *runtime polymorphism*. Take a look at the code in
[inheritance_polymorphysm.cpp](src/inheritance_polymorphysm.cpp).
There, both, the base class destructor and the `getArea()` method
are virtual. That allows us to override `getArea()` in `Rectangle`
class, for example. The output this code produces looks like:
```
$ ./a.out 
Invoking Shape constructor ...
Invoking Shape constructor ...
Invoking Circle constructor ...
Invoking Shape constructor ...
Invoking Rectangle constructor ...

No shape specified; area set to 0
Circle area = 3.14159
Rectangle area =  (using overriden getArea) 6

Invoking Shape destructor ...
Invoking Circle destructor ...
Invoking Shape destructor ...
Invoking Rectangle destructor ...
Invoking Shape destructor ...
$
```


