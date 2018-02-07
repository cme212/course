#include <iostream>
#include <cmath>


/// Create a rectangle and calculate its area
class Rectangle
{
public:
  Rectangle(double width, double length)
    : width_(width),
      length_(length),
      area_(width_*length_)
  {
    std::cout << "Invoking Rectangle constructor ...\n";
    area_ = width_*length_;
  }

  ~Rectangle()
  {
    std::cout << "Invoking Rectangle destructor ...\n";
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


/// Create a circle and calculate its area
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


int main()
{
  Rectangle r(3.0, 2.0);
  Circle c(0.0, 0.0, 1.0);

  std::cout << "Rectangle area = " << s.getArea() << "\n";
  std::cout << "Circle area    = " << c.getArea() << "\n";
  
  return 0;
}
    
