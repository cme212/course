///
/// Using virtual methods allows you to override base class methods.
///

#include <iostream>
#include <cmath>

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

  /// Virtual method
  virtual double getArea()
  {
    return area_;
  }
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

  double getRadius()
  {
    return radius_;
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

  double getArea()
  {
    std::cout << " (using overriden getArea) ";
    return area_;
  }
  
private:
  double width_;
  double length_;
};


int main()
{
  /// Array of pointers to Shape class instances
  Shape* myShapes[3] = {new Shape(), new Circle(1.0), new Rectangle(3.0, 2.0)};

  std::cout << "\n\n";
  std::cout << "No shape specified; area set to " << myShapes[0]->getArea() << "\n";
  std::cout << "Circle area = "    << myShapes[1]->getArea() << "\n";
  std::cout << "Rectangle area = " << myShapes[2]->getArea() << "\n";
  //std::cout << "Circle radius = " << myShapes[1]->getRadius() << "\n"; // Compiler error
  std::cout << "\n\n";

  delete myShapes[0];
  delete myShapes[1];
  delete myShapes[2];
  
  return 0;
}
    
