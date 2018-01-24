#include <iostream>

#include "student.hpp"

/** 
 * Search a sorted array for a value using binary search.
 * 
 * @param[in] a         Sorted array to search.
 * @param[in] low,high  Search in the index range [@a low, @a high).
 * @param[in] v         Value to search for.
 * @return    An index into array @a a or -1.
 * 
 * @tparam T Comparison operator defined: bool operator<(T,T)
 * @tparam T Comparison operator defined: bool operator>(T,T)
 * @tparam T Not appropriate for floating point type
 *
 * @pre 0 <=  low <=  high <= Size of the array _a_.
 * @pre For all i,j with  low <= i < j <  high,  a[i] <= a[j].
 * @post ( low <= result <  high and  a[result] ==  v) 
 *    or (result == -1 and there is no _i_ s.t. low <= i < high, and a[i] == v).
 *
 * Complexity O(log(high - low))
 */
template <class T>
int binary_search(const T* a, int low, int high, const T& v)
{
  --high;

  while (low <= high) {
    int mid = (low + high) / 2;
    if (a[mid] < v)
      low = mid + 1;
    else if (a[mid] > v)
      high = mid - 1;
    else
      return mid;   // Value found (return position)
  }
  return -1;        // Value not found
}


int main()
{
  //             0    1     2     3     4     5     6     7     8      9 
  float a[10] = {2.f, 12.f, 15.f, 72.f, 73.f, 77.f, 90.f, 91.f, 100.f, 200.f};
  
  std::cout << binary_search<float>(a, 0, 10, 74.) << "\n";
  std::cout << binary_search<float>(a, 0, 10, 73.) << "\n";
  std::cout << binary_search<float>(a, 0, 10,  2.) << "\n";

  std::cout << "\n";
  
  int b[10] = {2, 12, 15, 72, 73, 77, 90, 91, 100, 200};
  int tol2 = 0;
  std::cout << binary_search<int>(b, 5, 7, 90) << "\n";
  std::cout << binary_search<int>(b, 5, 6, 90) << "\n";

  Student classroom[3];
  Student* s1 = new Student("Idle, Eric", 100100);
  Student* s2 = new Student("Jones, Terry", 100200);
  Student* s3 = new Student("Palin, Michael", 100300);
  Student* s4 = new Student("Chleese, John", 100300);
  classroom[0] = *s1; classroom[1] = *s2; classroom[2] = *s3;
  
  std::cout << "\n";
  
  std::cout << binary_search<Student>(classroom, 0, 3, *s3) << "\n";
  std::cout << binary_search<Student>(classroom, 0, 3, *s1) << "\n";
  std::cout << binary_search<Student>(classroom, 0, 3, *s4) << "\n";
  
  return 0;
}
