#include <iostream>
#include "student.hpp"
/** 
 * Search a sorted array for a value using binary search.
 * 
 * @param[in] a         Sorted array to search.
 * @param[in] low,high  Search in the index range [low,  high).
 * @param[in] v         Value to search for.
 * @param[in] eps       Equality tolerance
 * @return    An index into array _a_ or -1.
 *
 * @tparam T Type of the array elements
 * @tparam T Comparison operator defined: bool operator<(T,T)
 * @tparam T Addition operator defined: T operator+(T,T)
 * 
 * @pre 0 <= low <= high <= Size of the array _a_.
 * @pre For all i,j with  low <= i < j < high,  a[i] <= a[j].
 * @post ( low <= result < high  and  a[result] == v within tolerance eps) 
 *    or (result == -1 and there is no _i_ s.t. low <= i < high, and a[i] == v).
 *
 * The complexity of the serach algorithm is O(high - low)
 */
template <class T>
int binary_search(const T* a, int low, int high, const T& v, const T& eps)
{
  --high;

  while (low <= high) {
    int mid = (low + high) / 2;
    if (a[mid] + eps < v)
      low = mid + 1;
    else if (v + eps < a[mid])
      high = mid - 1;
    else
      return mid; // Value found (return position)
  }
  return -1;      // Value not found
}


int main()
{
  //             0    1     2     3     4     5     6     7     8      9 
  float a[10] = {2.f, 12.f, 15.f, 72.f, 73.f, 77.f, 90.f, 91.f, 100.f, 200.f};
  float tol = 1e-10f;

  // Explicitly specified template parameter
  std::cout << binary_search<float>(a, 0, 10, 74.f, tol) << "\n";
  std::cout << binary_search<float>(a, 0, 10, 73.f, tol) << "\n";
  // Compiler deduces template parameter
  std::cout << binary_search(a, 0, 10, 89.f, tol) << "\n";
  std::cout << binary_search(a, 0, 10, 90.f, tol) << "\n";

  std::cout << "\n";
  
  int b[10] = {2, 12, 15, 72, 73, 77, 90, 91, 100, 200};
  int tol2 = 0; // should be zero for integers
  std::cout << binary_search<int>(b, 5, 7, 90, tol2) << "\n";
  std::cout << binary_search<int>(b, 5, 6, 90, tol2) << "\n";
  
  std::cout << "\n";
  
  Student classroom[3];
  Student* s1 = new Student("Idle, Eric", 100100);
  Student* s2 = new Student("Jones, Terry", 100200);
  Student* s3 = new Student("Palin, Michael", 100300);
  Student* s4 = new Student("Cleese, John", 100400);
  Student* tol3 = new Student("", 0); // Fake tolerance for Student class
  classroom[0] = *s1; classroom[1] = *s2; classroom[2] = *s3;
  
  std::cout << binary_search<Student>(classroom, 0, 3, *s3, *tol3) << "\n"; // Palin ~> 2
  std::cout << binary_search<Student>(classroom, 0, 3, *s1, *tol3) << "\n"; // Idle  ~> 0
  std::cout << binary_search<Student>(classroom, 0, 3, *s4, *tol3) << "\n"; // Cleese ~> -1

  delete s1;
  delete s2;
  delete s3;
  delete s4;
  delete tol3;
  
  return 0;
}
