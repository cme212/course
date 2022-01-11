# CME 212: Lecture 7

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
    : x_(x),
      y_(y),
      radius_(radius),
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
  double x_;
  double y_;
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

Inheritance is an **is-a** relation between the *Base* and the *Derived* classes.  

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

protected: // protected instead of private, means derived classes can access this attribute.
  double area_;
};
```
Note that we defined variable `area_` as a *protected* rather than
*private* member, and by doing so only classes which inherit from `Shape` can access this attribute. Now, we can create a class `Circle`, which
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

Each member of a class has an access specifier that dictates the who can access it. 
you have seen 2 up to now `private` and `public`. When dealing with derived classes there is a third specifier `protected`. When a variable is `protected` it can be accessed other members of the same class *and by the derived classes*, but anyone outside the derived class or the base class cannot access protected attributes.

```c++
class Base
{
public:
    int m_public; // can be accessed by anybody
private:
    int m_private; // can only be accessed by Base members and friends (but not derived classes)
protected:
    int m_protected; // can be accessed by Base members, friends, and derived classes
};
 
class Derived: public Base
{
public:
    Derived()
    {
        m_public = 1; // allowed: can access public base members from derived class
        m_private = 2; // not allowed: can not access private base members from derived class
        m_protected = 3; // allowed: can access protected base members from derived class
    }
};
 
int main()
{
    Base base;
    base.m_public = 1; // allowed: can access public members from outside class
    base.m_private = 2; // not allowed: can not access private members from outside class
    base.m_protected = 3; // not allowed: can not access protected members from outside class
}
```



Besides access specifiers `public`, `private` and `protected ` are also used to describe the type of inheritance of a derived class and can **change the access specifiers in the base!**. 

**Public** inheritance does not change the specifiers.

```c++
class Sphere: public Shape
```

| Base class specifier | After *public* inheritance |
| -------------------- | -------------------------- |
| Public               | Public                     |
| Private              | Inaccessible               |
| Protected            | Protected                  |

**Private** inheritance is the default in C++, it will change `public ` attributes of the Base class to `private` attributes of the derived class.

| Base class specifier | After *private* inheritance |
| -------------------- | --------------------------- |
| Public               | Private                     |
| Private              | Inaccessible                |
| Protected            | Private                     |

```c++
class Derived: private Base // note: private inheritance
{
    // Private inheritance means:
    // Public inherited members become private (so m_public is treated as private)
    // Protected inherited members become private (so m_protected is treated as private)
    // Private inherited members stay inaccessible (so m_private is inaccessible)
public:
    Derived()
    {
        m_public = 1; // okay: m_public is now privately accessible from a derived class
        m_private = 2; // not okay: derived classes can't access private members in the base class
        m_protected = 3; // okay: m_protected is now private
    }
};
 
int main()
{
    // Outside access uses the access specifiers of the class being accessed.
    // In this case, the access specifiers of base.
    Base base;
    base.m_public = 1; // okay: m_public is public in Base
    base.m_private = 2; // not okay: m_private is private in Base
    base.m_protected = 3; // not okay: m_protected is protected in Base
 
    Derived der;
    der.m_public = 1; // not okay: m_public is now private in Derived
    der.m_private = 2; // not okay: m_private is inaccessible in Derived
    der.m_protected = 3; // not okay: m_protected is now private in Derived
```



The `public` and `protected`attributes from the base class are `private` in the derived class.  

**Q: Why is this useful?**

## Accessing the base class

The `Base` constructor is called before anything else is done in the `Derived` constructor.

```c++
class Base
{
protected:
    int value_;
 
public:
    Base(int value)
        : value_(value)
    {}

class Derived: public Base
{
public:
    double m_cost;
    
    Derived(double cost=0.0, int value=0)
        : m_cost(cost),
          // Error here: we can't assign to members of the parent class.
          value_(value){}
    double getCost() const { return m_cost; }
```

**This does not work** as initialization lists can only assign to members of the initialized class.

There are two alternatives

1. Call the `Base` constructor in the initialization list.
2. Assign the variable in the body of the constructor.

```c++
// Option 1: call the Base constructor in the initialization list.
Derived(double cost=0.0, int value=0)
        : Base(value), // Call Base(int) constructor with value id!
            cost_(cost) {}

// Option 2: assign the member attribute in the body of the constructor.
Derived(double cost=0.0, int value=0)
        : cost_(cost)
        {
            value_=value // Assign Base::value_ manually.
        }      
          
```

In general it is better to use the first method as it is more efficient and ensures that variables are initialized in the right order.

The derived class has access to all the public and protected attributes of `Base`.

```c++
class Derived: public Base
{
public:
    Derived(int value)
        :Base(value)
    {}
    int getValue() {
      // value_ is a protected attributed in Base, which means it's 
      // OK to access it in a derived class.
      return value_; 
    }
};
```



We can also directly call methods from the `Base` class. Suppose we have 
defined a simple `identify` method in `Base` that prints a simple message to console, then this method would also be available to use in derived classes.

```c++
int main()
{
    Base base(5);
    base.identify();
 
    Derived derived(7);
    derived.identify();
 
    return 0;
}
```

> ```
> I am a Base
> I am a Base
> ```



We can also override the `Base` methods

```c++
class Derived: public Base
{
public:
    Derived(int value)
        : Base(value)
    {}
 
    int getValue() { return m_value; }
 
    // Here's our modified function
    void identify() { std::cout << "I am a Derived\n"; }
};
```

Derived classes can **overwrite** the access specifiers of their Base. Since the program will look in the derived scope first we can hide the functionality of the base class in the derived class. This is especially useful if the derived class is needs certain attributes of the base class to be fixed. For attributes we can simply change the access specifier.

We can also call the base function even if it is overwritten. We just have to be very careful with the scope of our call. 

```c++
void identify() { identify();}
```

Will result in an infinite loop as the program will first look for the `identify()` function in the *Derived* scope. The correct way is to specify the scope of the function we are calling

```c++
void identify() { Base::identify();}
```

This will tell the program to look in the Base scope for the `identify()` function.

Scope also allows us to change the access specifier of our Base methods in the derived classes with the `using ` keyword.  This will move the method to the scope of the derived class and attach the access specifier it is declared with.

```c++
class Base
{
private:
    int value_;
 
public:
    Base(int value)
        : value_(value)
    {}
 
protected:
    void printValue() { std::cout << m_value; }
};

class Derived: public Base
{
public:
    Derived(int value)
        : Base(value)
    {}
 
    // Base::printValue was inherited as protected, so the public has no access
    // But we're changing it to public via a using declaration
    using Base::printValue; // note: no parenthesis here
};

int main()
{
    Derived derived(7);
 
    // printValue is public in Derived, so this is okay
    derived.printValue(); // prints 7
    return 0;
}
```



## Polymorphism

As with anything we can create pointers and references to classes we have created. However with derived classes we can get some interesting behavior if we do the following:

```c++
int main()
{
    Derived derived(5);
 
    // These are both legal!
    Base &rBase = derived;
    Base *pBase = &derived;
 
cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
cout << "rBase is a " << rBase.getName() << " and has value " << rBase.getValue() << '\n';
cout << "pBase is a " << pBase->getName() << " and has value " << pBase->getValue() << '\n';
 
    return 0;
}
```

This prints:

> ```
> derived is a Derived and has value 5
> rBase is a Base and has value 5
> pBase is a Base and has value 5
> ```



The `Base ` pointers and references only see the attributes that belong to the base class and are blind to everything else. This allows us to *mask* our derived class as a base class. This is called **Polymorphism**

One useful application of this involves vectors. 

```c++
#include <iostream>
std::vector<Shape*> shapes_;
shapes_.push_back(circle);
shapes_.push_back(rectangle);
```

The above runs without any errors! Since we have an array of pointers neither `circle` nor `rectangle` will lose any information; to put it differently, had we created `vector<Shape>` we would have allocated *only just enough* storage
for `Shape` objects to be held in each slot of the vector, which would mean
there wouldn't be room left over to store additional attributes that `circle`
and `rectangle` may have defined. I.e. if we had assigned them directly they would have lost all attributes that are nor part of the `Shape` class.

Because we are dealing with references and pointers of the `Base` class we are confined to the scope of the `Base` class. This means that we cannot call any of the methods in the Derived classes and any overwritten method will revert back to the Base version. However if we assign the pointer to a reference of the Derived class we get all this functionality back.

### Virtual Functions ###

A `virtual` function tells the compiler to look for the most derived version of that function that is above the class calling it. All this is done at *runtime*.

 Consider following code:

```c++
int main()
{
  Shape* pc = new Circle(2.0);

  std::cout << "\n";
  std::cout << "Circle area = " << pc->getArea() << "\n";
  //std::cout << "Circle radius = " << pc->getRadius() << "\n"; // Compiler error, since we only have a pointer to a Shape, which doesn't have a getRadius() method.
  std::cout << "\n";

  delete pc; // Memory for a Shape is relinquished, but we allocated memory for a Circle which may hold additional attributes/methods; memory leak!
  
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
access it through the pointer to the base class.

```c++
class A
{
public:
    virtual const char* getName() { return "A"; }
};
 
class B: public A
{
public:
    virtual const char* getName() { return "B"; }
};
 
class C: public B
{
public:
    virtual const char* getName() { return "C"; }
};
 
class D: public C
{
public:
    virtual const char* getName() { return "D"; }
};
 
int main()
{
    C c;
    A &rBase = c;
    std::cout << "rBase is a " << rBase.getName() << '\n'; // Prints that our reference is a 'C', since we look for the most derived implementation of getName() at run-time.
 
    return 0;
}
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
virtual double getArea() = 0;  // By specifying = 0 along with virtual keyword we declare the function as _pure_ virtual.
```
Assigning zero to the declaration of a virtual method is C++ way
of saying this is a *pure virtual* method. We do not need to implement
a pure virtual method in the base class. On the other hand, if we
do not implement pure virtual method in any of the derived classes,
the compiler will return an error. An example of using a pure
virtual method is given in [inheritance_pure_virtual.cpp](src/inheritance_pure_virtual.cpp).
A class that has no data and only pure virtual methods is called
an **abstract** class or an **interface** class. An example of abstract
`Shape` class and its use is provided in
[inheritance_interface.cpp](src/inheritance_interface.cpp).

Recap: What did we just observe?

* We declared a function `virtual double GetArea() = 0;` in the Shape class. The =0 syntax told the compiler that this was a **pure virtual** function, meaning that any derived class must override that function.
* Any class with >= 1 pure virtual function is understood to be an **abstract class** in C++, meaning that it cannot be instantiated.

**Q: Does the concept of polymorphism still apply even with an abstract class, such as "Shape"?**
**A:** Yes. It is still valid to have a pointer of type Shape.



```c++
class B {
public:
    virtual int f();
};

class D : public B {
private:
    int f(){};
};

int main
{
    D d;
    B* pb = &d;
    D* pd = &d;

    pb->f(); //OK. Virtual specifies we should look for the most derived implementation. 
             // There isn't one available in D, so we look for a base implementation 
             // and see that B::f()is public, therefore D::f() is invoked
    pd->f(); //error: D::f()is private
}
```



## Composition

Composition is another type of relationship between objects.  Composition occurs when objects relate in a "has a" relationship.

Here is an example where we create a `Point2D` class to define point-specific methods, and then re-implement our `Circle` class to **have** a `Point2D` to represent its center.

```c++
#include <iostream>
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

We can construct instances of a point and print them out nicely.
```c++
Point2D p = Point2D(4,5)
std::cout << p << std::endl;
```

We can now define a circle as "having a" `Point2D` as its `center` attribute.
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

We can still create new circles by specifying their `center_` along with a
`radius_` 
```c++
Circle2 circle = Circle2(4,3,2);
circle.GetArea()                                 // Our GetArea method works as intended.
std::cout << circle.GetLocation() << std::endl;  // Additionally, so does GetLocation.
```

One interesting question to ask ourselves is, what is the behavior of the
default constructor for a `Circle2`?

```c++
Circle2 circle2 = Circle2();
// Preview of default constructors: what value will this return? To be demystified in upcoming lectures.
std::cout << circle2.GetLocation() << std::endl;
```

### Reading ###

* [Public, protected and private inheritance](https://stackoverflow.com/questions/860339/difference-between-private-public-and-protected-inheritance)
* [Virtual functions](https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c)
* [Interfaces in C++](https://stackoverflow.com/questions/1216750/how-can-i-simulate-interfaces-in-c)
* [Inheritance](https://www.learncpp.com/cpp-tutorial/111-introduction-to-inheritance/)



