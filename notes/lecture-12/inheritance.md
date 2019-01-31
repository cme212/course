# CME 212: Lecture 12

## Inheritance and Polymorphism ##

Inheritance is a fundamental motif in object oriented programming.
It allows a class to reuse code of another class and in that way
inherit member variables and methods from that class.
The inheritance can be described as an *is-a* relationship. For
example, a triangle is a shape, or a student is a scholar. Let us explain
basics of inheritance in a simple example. Consider the class `Rectangle`
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
and the class `Circle`
(see [inheritance_none.cpp](src/inheritance_none.cpp))
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
Each class represents a shape, has a member variable `area_`,
and has a method `getArea()`. If we want to add more shapes (like triangles, pentagons, etc.),
we would need to replicate the same variable and the same method
for those shapes, too, since all shapes have an area. If we
want to add another general shape property (e.g. color), we would
have to add it to all classes representing shapes that we created.
This will cause our code to grow quickly as we add more features,
and that will in turn make maintenance of our code expensive.



### Inheritance ###

The inheritance allows us to implement all the common features
of our objects in a *base* class. When we derive a class from the base class,
the *derived* class will inherit the common features implemented in the base,
so we will need to implement only the features specific to the *derived* class.
This approach leads to a leaner and easier to maintain code. 
For example, we can create class `Shape` like this:
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
Note that we defined variable `area_` as a *protected* rather than
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
`Shape`. All public methods and variables from `Shape` will also
be public in `Circle`. We defined variable `area_` as *protected* so
it is accessible by `Circle` and other classes that inherit from `Shape`.
If `area_` was private, `Circle` would inherit it, but it would not
be able to access it. 
Note that accessibility in C++ is based on classes and not objects.
Therefore instances of the same class can access each other's private
members.
We can implement class `Rectangle` to inherit from `Shape` in a similar
manner. The complete code is provided in
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
Let us take a look at what is going on here. We first invoke
constructors for `Circle` and `Rectangle`. Each derived
class constructor will call the base class constructor,
which will be executed before the derived class constructor.
After we created a `Circle` and a `Rectangle`, we
can access their own and inherited public features alike.
When the destructor of a derived class is called, it will
call the destructor of the base class. The base class destructor
will be executed after the derived class destructor.

## Public, Protected or Private



## Polymorphism

The concept that a different version of a method can be called based on the inheritance structure of the classes.  This allows us to interact with "Student" objects whose underlying functionality is dictated by their actual type.

```c++
#include <iostream>
```

```c++
std::vector<Student*> students_;
```

```c++
students_.push_back(&local);
```

```c++
students_.push_back(&remote_student);
```

```c++
for (int i = 0; i < students_.size(); i++){
    std::cout << students_[i]->student_type_ << " " << students_[i]->get_id() << ": " 
        << students_[i]->get_dorm() << std::endl;
}
```

Note that if we hadn't included the `virtual` keyword, then the base class's version of `get_dorm()` would have been called, even for the local student.

The `virtual` keyword signals to the compiler that we don't want **static linkage** for this function (function call determined before the program is executed).

Intead, we want the selection of which version of `get_dorm()` to call to be dictated by the kind of object for which it is called - this is called **dynamic linkage** or late binding.



Note: We used a vector of pointers to Students in our example above:

`std::vector<Student*> students_;`

Would we still have been able to take advantage of Polymorphism with a vector of Student objects?

```c++
std::vector<Student> students_2;
```

```c++
students_2.push_back(local);
```

```c++
students_2.push_back(remote_student);
```

```c++
for (int i = 0; i < students_2.size(); i++){
    std::cout << students_2[i].student_type_ << " " << students_2[i].get_id() << ": " 
        << students_2[i].get_dorm() << std::endl;
}
```

```c++
students_2[1].get_location()
```

What happened when instead of creating a vector of pointers to Student objects, we created a vector of Student objects?

- We were still able to add the "local" and "remote_student" objects to the vector, but the copy constructor of the "Student" class was called, creating new Student objects and implicitly casting the derived objects to the base class
- That's why the type changed to "Student", and get_dorm() follows the Student class behavior

**TL;DR**: In order to make use of polymorphism, use pointers to objects of the Base class type


### Virtual Functions and Polymorphism ###

Let us now try something different. Consider following code:



```c++
int main()
{
  Shape* pc = new Circle(2.0);

  std::cout << "\n";
  std::cout << "Circle area = " << pc->getArea() << "\n";
  //std::cout << "Circle radius = " << pc->getRadius() << "\n"; // Compiler error
  std::cout << "\n";

  delete pc; ///< Shape is destroyed, but Circle is not, memory leak!
  
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

Let us now define `Shape` destructor as a virtual function:

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
leak. Furthermore, we are able to override any other
virtual function in the derived class, and
access it through the pointer to the base class. This is
called *runtime polymorphism*. Take a look at the code in
[inheritance_public_polymorphism.cpp](src/inheritance_public_polymorphism.cpp).
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
This is particularly helpful when we want to specify default
behavior in the base class, but still be able to override the
default in some derived classes.


### Pure Virtual Methods ###

Sometimes we want to force developers to follow certain standards.
For example, we may want every shape to provide method `getArea()`.
One way to accomplish that is to define base class method `getArea()`
as a pure virtual method. The declaration would look like this:
```c++
virtual double getArea() = 0;
```
Assigning zero to the declaration of a virtual method is C++ way
of saying this is a *pure virtual* method. We do not need to implement
a pure virtual method in the base class. On the other hand, if we
do not implement pure virtual method in any of the derived classes,
the compiler will return an error. An example of using a pure
virtual method is given in [inheritance_pure_virtual.cpp](src/inheritance_pure_virtual.cpp).
A class that has no data and only pure virtual methods is called
an abstract class or an interface class. An example of abstract
`Shape` class and its use is provided in
[inheritance_interface.cpp](src/inheritance_interface.cpp).

Recap: What did we just observe?

* We declared a function `virtual double GetArea() = 0;` in the Shape class. The =0 syntax told the compiler that this was a **pure virtual** function, meaning that any derived class must override that function.
* Any class with >= 1 pure virtual function is understood to be an **abstract class** in C++, meaning that it cannot be instantiated.

**Q: Does the concept of polymorphism still apply even with an abstract class, such as "Shape"?**
**A:** Yes. It is still valid to have a pointer of type Shape.

## Composition

Composition is another type of relationship between objects.  Composition occurs when objects relate in a "has a" relationship.

Here is an example where we create a `Point2D` class to define point-specific methods, and then re-implement our `Circle` class to **have** a `Point2D` to represent its center.

Note: We have already made use of the concept of composition in the `Student` examples, where our `Student_Course` member objects only existed in the context of a particular student, and the `Student_Course` objects didn't "know" about the `Student`.

```c++
#include <iostream>
```


```c++
class Point2D
{
private:
    double x_ = 0.0;
    double y_ = 0.0;
 
public:
    // A default constructor
    Point2D(){};
 
    Point2D(double x, double y): x_(x), y_(y){};
 
    // An overloaded output operator
    friend std::ostream& operator<<(std::ostream& out, const Point2D &point)
    {
        out << "(" << point.x_ << ", " << point.y_ << ")";
        return out;
    }
 
};
```


```c++
Point2D p = Point2D(4,5)
```


```c++
std::cout << p << std::endl;
```


```c++
class Circle2: public Shape {
    Point2D center_;
    double radius_;
    
  public:
    Circle2(double x, double y, double radius):center_(x, y), radius_(radius){};
    
    // A default constructor
    Circle2(){};
    
    double GetArea(){
        return M_PI * radius_ * radius_;
    };
    
    Point2D GetLocation(){
        return center_;
    }
    
}
```


```c++
Circle2 circle = Circle2(4,3,2);
```


```c++
circle.GetArea()
```

```c++
std::cout << circle.GetLocation() << std::endl;
```


```c++
Circle2 circle2 = Circle2();
```


```c++
// What value will this return?
std::cout << circle2.GetLocation() << std::endl;
```

### Reading ###

* [Public, protected and private inheritance](https://stackoverflow.com/questions/860339/difference-between-private-public-and-protected-inheritance)
* [Virtual functions](https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c)
* [Interfaces in C++](https://stackoverflow.com/questions/1216750/how-can-i-simulate-interfaces-in-c)

