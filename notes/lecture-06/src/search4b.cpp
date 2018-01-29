#include <iostream>

#include "student.hpp"

/** 
 * Search a sorted array for a value using binary search.
 * 
 * @param[in] a         Sorted array to search.
 * @param[in] low,high  Search in the index range [@a low, @a high).
 * @param[in] v         Value to search for.
 * @return    An index into array _a_ or -1.
 * 
 * @tparam T Type of the array elements
 * @tparam T Comparison operator defined: bool operator<(T,T)
 * @tparam T Not appropriate for floating point types
 *
 * @pre 0 <=  low <=  high <= Size of the array _a_.
 * @pre For all i,j with  low <= i < j <  high,  a[i] <= a[j].
 * @post ( low <= result <  high and  a[result] ==  v) 
 *    or (result == -1 and there is no _i_ s.t. low <= i < high, and a[i] == v).
 *
 * The complexity of the serach algorithm is O(log(n))
 */
template <class T>
int binary_search(const T* a, int low, int high, const T& v)
{
  --high;

  while (low <= high) {
    int mid = (low + high) / 2;
    if (a[mid] < v)
      low = mid + 1;
    else if (v < a[mid])
      high = mid - 1;
    else
      return mid;   // Value found (return position)
  }
  return -1;        // Value not found
}


int main()
{
  //           0  1   2   3   4   5   6   7   8    9
  int b[10] = {2, 12, 15, 72, 73, 77, 90, 91, 100, 200};

  std::cout << binary_search<int>(b, 5, 7, 90) << "\n";
  std::cout << binary_search<int>(b, 5, 6, 90) << "\n";

  std::cout << "\n";
  
  Student classroom[3];
  Student* idle   = new Student("Idle, Eric", 100100);
  Student* jones  = new Student("Jones, Terry", 100200);
  Student* palin  = new Student("Palin, Michael", 100300);
  Student* cleese = new Student("Cleese, John", 100400);
  // Create a classroom ordered alphabetically by student name
  classroom[0] = *idle; classroom[1] = *jones; classroom[2] = *palin;
  
  std::cout << "\n";
  
  std::cout << binary_search(classroom, 0, 3, *palin)  << "\n"; // Palin ~> 2
  std::cout << binary_search(classroom, 0, 3, *idle)   << "\n"; // Idle  ~> 0
  std::cout << binary_search(classroom, 0, 3, *cleese) << "\n"; // Cleese X
  
  return 0;
}
