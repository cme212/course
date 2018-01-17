///
/// @file Student.cpp contains definition of class Student
///

#include <Name.hpp>
//#include "Name.hpp"
#include "Student.hpp"

// Definition of the class Student

/// Constructor
Student::Student(std::string givenName, std::string familyName, int studentID)
  : name_(new Name(givenName, familyName)),
    studentID_(studentID)
{
}

/// Destructor
Student::~Student()
{
}

/// Return a copy of the student's ID number
int Student::getStudentID() const
{
  return studentID_;
}

/// Return a copy of student's name
std::string Student::getName() const
{
  return name_->getName();
}
