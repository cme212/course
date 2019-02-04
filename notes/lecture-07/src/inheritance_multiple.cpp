///
/// Multiple inheritance
/// Get desired functionality by inheriting from multiple classes.
/// Reuse code, minimize duplication.
///

#include <iostream>
#include <string>

/// The class Person has a name.
class Person
{
public:
  Person(const std::string name)
    : name_(name)
  {
  }

  ~Person()
  {
  }

  std::string getName()
  {
    return name_;
  }

protected:
  std::string name_;
};


/// The class Scholar has an affiliation.
class Scholar
{
public:
  Scholar(const std::string affiliation)
    : affiliation_(affiliation)
  {
  }

  ~Scholar()
  {
  }

  std::string getAffiliation()
  {
    return affiliation_;
  }

protected:
  std::string affiliation_;
};

/// Declaration (definition) of the class Student
/// The Student is a Person and the Student is a Scholar
/// The Student has a student ID
class Student : public Person, public Scholar
{
public:
  /// Constructor
  Student(std::string name, std::string affiliation, int studentID)
    : Person(name),
      Scholar(affiliation),
      studentID_(studentID)
  {
  }

  /// Destructor
  ~Student()
  {
  }

  /// Return a copy of the student's ID number
  int getStudentID() const
  {
    return studentID_;
  }
  
private:
  int studentID_;    ///< Student's ID number
};


int main()
{
  /// Create a geography student (who is an instance of the Student) on the heap.
  /// Pointer pGeographyStudent point to the instance of the geography student.
  Student* pGeographyStudent = new Student("Terry Gilliam", "Stanford University", 111234);

  std::cout << "Student's name: " << pGeographyStudent->getName() << ", "
            << "Affiliation: " << pGeographyStudent->getAffiliation() << ", "
            << "ID#: " << pGeographyStudent->getStudentID()  << "\n";

  delete pGeographyStudent;
  return 0;
}
