#include <iostream>

/** 
 * Search a sorted array for a value using binary search.
 * 
 * @param[in] a         Sorted array to search.
 * @param[in] low,high  Search in the index range [ low,  high).
 * @param[in] v         Value to search for.
 * @return    An index into array  a or -1.
 *
 * @tparam T Comparison operator defined: bool operator<(T,T)
 * @tparam T Comparison operator defined: bool operator>(T,T)
 * @tparam T Substraction operator defined: T operator-(T,T)
 * @tparam T Negation operator defined: T operator-(T)
 * 
 * @pre 0 <=  low <=  high <= Size of the array _a_.
 * @pre For all i,j with  low <= i < j <  high,  a[i] <= a[j].
 * @post ( low <= result <  high and  a[result] ==  v) 
 *    or (result == -1 and there is no _i_ s.t. low <= i < high, and a[i] == v).
 *
 * Complexity O(log(high - low))
 */
template <class T>
int binary_search(const T* a, int low, int high, const T& v, const T& eps)
{
  --high;

  while (low <= high) {
    int mid = (low + high) / 2;
    if ((a[mid] - v) < -eps)
      low = mid + 1;
    else if ((a[mid] - v) > eps)
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
  float tol = 1e-10f;
  
  std::cout << binary_search<float>(a, 0, 10, 74., tol) << "\n";
  std::cout << binary_search<float>(a, 0, 10, 73., tol) << "\n";
  std::cout << binary_search<float>(a, 0, 10,  2., tol) << "\n";
  std::cout << binary_search<float>(a, 0, 10,200., tol) << "\n";
  std::cout << binary_search<float>(a, 0, 10,  1., tol) << "\n";
  std::cout << binary_search<float>(a, 0, 10,250., tol) << "\n";
  std::cout << binary_search<float>(a, 0, 10, 89., tol) << "\n";
  std::cout << binary_search<float>(a, 0, 10, 90., tol) << "\n";
  std::cout << binary_search<float>(a, 0, 10, 91., tol) << "\n";

  std::cout << "\n";
  
  int b[10] = {2, 12, 15, 72, 73, 77, 90, 91, 100, 200};
  int tol2 = 0;
  std::cout << binary_search<int>(b, 5, 7, 90, tol2) << "\n";
  std::cout << binary_search<int>(b, 5, 6, 90, tol2) << "\n";

  
  return 0;
}
