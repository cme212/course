#include <string>
#include <vector>
#include <iostream>

#include "student.hpp"

class StudentProxy
{
public:
  StudentProxy()
  {
  }

  ~StudentProxy()
  {
  }

  void create(std::string name, int studentID, long creditCardNo)
  {
    student_ = new Student(name, studentID, creditCardNo);
  }

  void destroy()
  {
    if (student_ != nullptr)
      delete student_;
  }

  std::string getName()
  {
    return student_->getName();
  }

private:
  Student* student_;
};

int main()
{
  // Create vector of proxy Students
  std::vector<StudentProxy> ss(3);

  // Create real Students
  ss[0].create("Terry Gilliam", 123444, 1111222233334);
  ss[1].create("Eric Idle"    , 123555, 5555222233334);
  ss[2].create("Michael Palin", 123666, 6666222233334);

  // Do something with Students
  for (unsigned i=0; i<ss.size(); ++i)
    std::cout << ss[i].getName() << "\n";

  // Delete students
  for (unsigned i=0; i<ss.size(); ++i)
    ss[i].destroy();

  return 0;
}
