///
/// Pure virtual method must be implemented in derived class.
///

#include <iostream>
#include <cmath>

/// Base class with pure virtual methods
/// Ensures each derived class must implement method getArea()
class Shape
{
public:
  Shape()
    : area_(0.0)
  {
    std::cout << "Invoking Shape constructor ...\n";
  }

  /// Virtual destructor
  virtual ~Shape()
  {
    std::cout << "Invoking Shape destructor ...\n";
  }

  /// Pure virtual method
  virtual double getArea() = 0;

protected:
  double area_;
};


class Circle : public Shape
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

  virtual double getArea()
  {
    return area_;
  }
  
private:
  double radius_;
};

class Rectangle : public Shape
{
public:
  Rectangle(double width, double length)
    : width_(width),
      length_(length)
  {
    std::cout << "Invoking Rectangle constructor ...\n";
    area_ = width_*length_;
  }

  ~Rectangle()
  {
    std::cout << "Invoking Rectangle destructor ...\n";
  }

  virtual double getArea()
  {
    return area_;
  }
  

private:
  double width_;
  double length_;
};


int main()
{
  // Shape* ps = new Shape(); ///< Compile error
  Shape* pc = new Circle(1.0);
  Shape* pr = new Rectangle(1.0, 2.0);

  std::cout << "\n\n";
  std::cout << "Circle area = "    << pc->getArea() << "\n";
  std::cout << "Rectangle area = " << pr->getArea() << "\n";
  std::cout << "\n\n";

  delete pc;
  delete pr;
  
  return 0;
}
    
