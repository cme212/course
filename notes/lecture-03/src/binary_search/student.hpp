#include <string>


// Definition of the class Student
class Student
{
public:
  // Default constructor
  Student()
  {
  }
  
  // Constructor
  Student(std::string name, int studentID)
    : name_(name),
      studentID_(studentID)
  {
  }

  // Destructor
  ~Student()
  {
  }

  // Assignment operator
  Student& operator=(const Student& rhs)
  {
    if (this == &rhs)
      return *this;

    name_ = rhs.name_;
    studentID_ = rhs.studentID_;
    
    return *this;
  }
  
  /// Return a copy of the student's ID number
  int getStudentID() const
  {
    return studentID_;
  }

  /// Return a copy of student's name
  std::string getName() const
  {
    return name_;
  }

private:
  std::string name_;  ///< Student's name
  int studentID_;     ///< Student's ID number
};


// Overloaded operators
// Here, we rely on std::string comparison

bool operator<(const Student& x, const Student& y)
{
  return (x.getName() < y.getName());
}

bool operator>(const Student& x, const Student& y)
{
  return (x.getName() > y.getName());
}

/// Addition operator
/// Adding students really does not make sense. Furthermore, this addition
/// is not commutative. Legal, but quite unintuitive. Bad design choice!
Student operator+(const Student& lhs, const Student& rhs)
{
  return Student(lhs.getName() + rhs.getName(), lhs.getStudentID());
}
