///
/// Pure virtual method must be implemented in derived class.
///

#include <iostream>
#include <cmath>

/// Interface class
/// Ensures that each derived class implements method getArea
class Shape
{
public:
  Shape()
  {
    std::cout << "Invoking Shape constructor ...\n";
  }

  /// Virtual inheritance (make sure destructor is virtual!)
  virtual ~Shape()
  {
    std::cout << "Invoking Shape destructor ...\n";
  }

  /// Pure virtual method
  virtual double getArea() = 0;

};


class Circle : public Shape
{
public:
  Circle(double radius)
    : radius_(radius)
  {
    std::cout << "Invoking Circle constructor ...\n";
  }

  ~Circle()
  {
    std::cout << "Invoking Circle destructor ...\n";
  }

  virtual double getArea()
  {
    return radius_*radius_*M_PI;
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
  }

  ~Rectangle()
  {
    std::cout << "Invoking Rectangle destructor ...\n";
  }

  virtual double getArea()
  {
    return width_*length_;
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
  std::cout << "Circle area = " << pc->getArea() << "\n";
  std::cout << "Rectangle area = " << pr->getArea() << "\n";
  std::cout << "\n\n";

  delete pc;
  delete pr;
  
  return 0;
}
