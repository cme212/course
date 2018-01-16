///
/// Composition is "has-a" relationship between classes.
/// Helps create a more modular code.
///

#include <iostream>
#include <string>

#include "Student.hpp"

int main()
{
  /// Create a geography student (who is an instance of the Student) on the heap.
  /// Pointer pGeographyStudent point to the instance of the geography student.
  Student* pGeographyStudent = new Student("Terry", "Jones", 111234);

  std::cout << "Student name: " << pGeographyStudent->getName() << ", "
            << "ID#: " << pGeographyStudent->getStudentID()  << "\n";

  /// Delete the geography student
  delete pGeographyStudent;
  return 0;
}
