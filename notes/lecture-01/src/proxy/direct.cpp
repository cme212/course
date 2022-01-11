#include <string>
#include <vector>
#include <iostream>

#include "student.hpp"



int main()
{
  // Create vector of Students
  std::vector<Student> ss;

  // Populate the vector
  ss.push_back(Student("Terry Gilliam", 123444, 1111222233334));
  ss.push_back(Student("Eric Idle"    , 123555, 5555222233334));
  ss.push_back(Student("Michael Palin", 123666, 6666222233334));

  // Do something with Students
  for (unsigned i=0; i<ss.size(); ++i)
    std::cout << ss[i].getName() << "\n";

  return 0;
}
