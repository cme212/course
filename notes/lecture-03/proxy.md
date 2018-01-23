# CME 212: Lecture 03

## Proxy Pattern

Let us consider a simple class Student implemented
in a header file [`student.hpp`](src/proxy/student.hpp).
The class stores student's name, ID number and credit
card number. We want to create a classroom as a vector of
students and perform some operations on it.

### Classroom of students

To create a classroom, we can use vector from Standard
Template Library and do something like this (see [`direct.cpp`](src/proxy/direct.cpp)):
```
  // Create vector of Students
  std::vector<Student> classroom;

  // Populate the vector
  classroom.push_back(Student("Terry Gilliam", 123444, 1111222233334));
  classroom.push_back(Student("Eric Idle"    , 123555, 5555222233334));
  classroom.push_back(Student("Michael Palin", 123666, 6666222233334));

  // Do something with Students
  for (unsigned i=0; i<classroom.size(); ++i)
    std::cout << classroom[i].getName() << "\n";
```
Note that each vector element stores an instance of the Student class.
Assuming that a student record will eventually hold a lot of data
(much more than in this particular example), this implementation of
the classroom object may not be the most efficient. For example,
`push_back` command will trigger large memory reallocation once
the vector capacity is exceeded. If we want to sort student records,
say by student names, this will cause a lot of data copying.


### Classroom of pointers to students

We can implement this in a more efficient way by using a vector
of _pointers_ to `Student`, rather than vector of `Student`s.
Here is a snippet from the implementation in [`pointer.cpp`](src/proxy/pointer.cpp):
```
  // Create vector of pointers to Student
  std::vector<Student*> classroom;

  // Populate the vector
  classroom.push_back(new Student("Terry Gilliam", 123444, 1111222233334));
  classroom.push_back(new Student("Eric Idle"    , 123555, 5555222233334));
  classroom.push_back(new Student("Michael Palin", 123666, 6666222233334));

  // Do something with Students
  for (unsigned i=0; i<classroom.size(); ++i)
    std::cout << classroom[i]->getName() << "\n";

  std::cout << "Hey, everybody, " << classroom[1]->getName()
            << "'s credit card number is " << ss[1]->getCreditCardNo() << "!\n";
```
Since we now use pointers, the `push_back` method is less taxing,
even when the vector capacity is exceeded. Sorting of the vector
elements is also cheaper, because we move only pointers, while the
each `Student` instance stays at the same place in memory.

While this implementation addresses performance efficiency,
there is another issue we haven't discussed yet. Imagine
that our application needs access only to student names and
ID numbers, but not credit card information. In such case,
it would be good to safeguard against application developers
accidentally accessing data they don't need to use as nothing
good can come out of it.
To create better data encapsulation we create a proxy
for the `Student` class (see [`proxy.cpp`](src/proxy/proxy.cpp)):
```
class StudentProxy
{
public:
  StudentProxy() {}

  ~StudentProxy() {}

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

```
The `StudentProxy` is a lightweight class with pointer
to `Student` as its only member variable. The proxy class
methods provide access to the select public methods of the `Student`
class. If we implement our classroom object as a vector of
`StudentProxy`s, our example code will look something like this
```
  // Create vector of proxy Students
  std::vector<StudentProxy> classroom(3);

  // Create real Students
  classroom[0].create("Terry Gilliam", 123444, 1111222233334);
  classroom[1].create("Eric Idle"    , 123555, 5555222233334);
  classroom[2].create("Michael Palin", 123666, 6666222233334);

  // Do something with Students
  for (unsigned i=0; i<classroom.size(); ++i)
    std::cout << classroom[i].getName() << "\n";
```
Vector push backs and sorting is slightly more expensive than in the
previous example where we used pointers to `Student`, however
these operations are still much cheaper than in the case of the vector
of `Students`. The new value this implementation adds is better data
encapsulation. Developers now can access only `Student` methods they
need, but not the other methods, such as the one retrieving student
credit card info. This may prevent introducing some bugs and may even
make malicious attempts to get student data more difficult. Another benefit of
this approach is that it leads to a code that is easier to maintain.
Imagine that the class `Student` and our application that uses 
that class are large codes developed by different teams.
If developers of `Student` decide to change its interface, we
would need to track all of the uses of `Student` methods in
our code and make changes where needed. Since our code is
presumably using `Student` methods frequently, this would
be a lot of work. However, if we use a proxy, all the changes will
be made in the proxy class itself. So this is one change per
method, instead of one change per method use.

For further reading, there is a nice discussion on proxy
pattern on [StackOverflow](https://stackoverflow.com/questions/994488/what-is-proxy-class-in-c).

