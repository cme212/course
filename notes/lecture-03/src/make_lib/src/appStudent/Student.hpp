///
/// @file Student.hpp contains declaration of class Student
///

#ifndef _STUDENT_HPP_
#define _STUDENT_HPP_

#include <string>

/// Forward declaration of class Name
class Name;

/// Declaration of the class Student
/// The Student has a Name
class Student
{
public:
  /// Constructor
  Student(std::string givenName, std::string familyName, int studentID);
  /// Destructor
  ~Student();
  /// Return a copy of the student's ID number
  int getStudentID() const;
  /// Return a copy of student's name
  std::string getName() const;

private:
  Name* name_;    ///< Student's name
  int studentID_; ///< Student's ID number
};


#endif // _STUDENT_HPP_
