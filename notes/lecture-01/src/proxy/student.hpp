#include <string>


// Definition of the class Student
class Student
{
public:
  // Constructor
  Student(std::string name, int studentID, long creditCardNo)
    : name_(name),
      studentID_(studentID),
      creditCardNo_(creditCardNo)
  {
  }

  // Destructor
  ~Student()
  {
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

  /// Return a copy of the student's ID number
  long getCreditCardNo() const
  {
    return creditCardNo_;
  }


private:
  std::string name_;  ///< Student's name
  int studentID_;     ///< Student's ID number
  long creditCardNo_; ///< Student's credit card #
};

