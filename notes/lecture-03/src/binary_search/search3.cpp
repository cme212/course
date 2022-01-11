#include <iostream>

/** 
 * Search a sorted array for a value using binary search.
 * 
 * @param[in] a         Sorted array to search.
 * @param[in] low,high  Search in the index range [ low,  high).
 * @param[in] v         Value to search for.
 * @return    An index into array _a_ or -1.
 *
 * @tparam T Type of the array elements. Following operators must be defined:
 *             - Comparison   `bool operator<(T,T)`
 *             - Comparison   `bool operator>(T,T)`
 * 
 * @pre 0 <= low <= high <= Size of the array _a_.
 * @pre For all i,j with  low <= i < j < high,  a[i] <= a[j].
 * @post ( low <= result <  high and  a[result] ==  v within tolerance eps) 
 *    or (result == -1 and there is no _i_ s.t. low <= i < high, and a[i] == v).
 *
 * The complexity of the serach algorithm is O(log(high - low))
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
      return mid; // Value found (return position)
  }
  return -1;      // Value not found
}


int main()
{
  //             0    1     2     3     4     5     6     7     8      9 
  float a[10] = {2.f, 12.f, 15.f, 72.f, 73.f, 77.f, 90.f, 91.f, 100.f, 200.f};

  // Explicitly specified template parameter
  std::cout << binary_search<float>(a, 0, 10, 74.f) << "\n";
  std::cout << binary_search<float>(a, 0, 10, 73.f) << "\n";
  // Compiler deduces template parameter
  std::cout << binary_search(a, 0, 10, 89.f) << "\n";
  std::cout << binary_search(a, 0, 10, 90.f) << "\n";

  std::cout << "\n";
  
  int b[10] = {2, 12, 15, 72, 73, 77, 90, 91, 100, 200};
  int tol2 = 0; // should be zero for integers
  std::cout << binary_search<int>(b, 5, 7, 90) << "\n";
  std::cout << binary_search<int>(b, 5, 6, 90) << "\n";

  
  return 0;
}
