#include <iostream>

/** 
 * @brief Search a sorted array for a value using binary search.
 *
 * @param[in] a  Sorted array of floats.
 * @param[in] n  Number of elements of _a_ to search.
 * @param[in] v  Value to search for.
 * @return    An index into array _a_ or -1.
 * 
 * @pre 0 <= n <= Size of the array  _a_.
 * @pre For all i,j with 0 <= i < j < n,  a[i] <= a[j].
 * @post (0 <= result < n and  a[result] == v) 
 *    or (result == -1 and there is no _i_ s.t  0 <= i <  n, and  a[i] ==  v).
 *
 * Complexity O(log(n))
 */
int binary_search(const float* a, int n, float v)
{
  const float eps = 1e-10;
  int low = 0;
  int high = n-1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if ((a[mid] - v) < -eps)     // a[mid] < v
      low = mid + 1;
    else if ((a[mid] - v) > eps) // a[mid] > v
      high = mid - 1;
    else
      return mid;   // Value found
  }
  return -1;        // Value not found
}


int main()
{
  //             0   1    2    3    4    5    6    7    8     9 
  float a[10] = {2., 12., 15., 72., 73., 77., 90., 91., 100., 200.};

  std::cout << binary_search(a, 10, 74.) << "\n";
  std::cout << binary_search(a, 10, 73.) << "\n";
  std::cout << binary_search(a, 10,  2.) << "\n";
  std::cout << binary_search(a, 10,200.) << "\n";
  std::cout << binary_search(a, 10, 1.) << "\n";
  std::cout << binary_search(a, 10,250.) << "\n";
  std::cout << binary_search(a, 10, 89.) << "\n";
  std::cout << binary_search(a, 10, 90.) << "\n";
  std::cout << binary_search(a, 10, 91.) << "\n";
  
  return 0;
}
