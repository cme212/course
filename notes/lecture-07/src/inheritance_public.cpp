///
/// Public inheritance allows you to pull common code from different
/// base classes into a derived class.
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

/// Rectangle is a Shape
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

  double getWidth()
  {
    return width_;
  }
  
private:
  double width_;
  double length_;
};


/// Circle is a Shape
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


int main()
{
  Shape* ps = new Shape();
  Circle* pc = new Circle(1.0);
  Shape* pc2 = new Circle(2.0);
  Rectangle* pr = new Rectangle(3.0, 2.0);
  
  std::cout << "\n\n";
  std::cout << "No shape specified; area = " << ps->getArea() << "\n";
  std::cout << "Circle area = " << pc->getArea() << "\n";
  std::cout << "Another Circle area = " << pc2->getArea() << "\n";
  std::cout << "Circle radius = " << pc->getRadius() << "\n";
  // std::cout << "Another Circle radius = " << pc2->getRadius() << "\n"; // Compiler error, since shape's don't have getRadius method.
  std::cout << "Rectangle area = " << pr->getArea() << "\n";
  std::cout << "\n\n";

  delete ps;
  delete pc;
  delete pc2; ///< Circle not completely destroyed, only enough storage for shape attributes is relinquished; memory leak!
  delete pr;
  
  return 0;
}
    
