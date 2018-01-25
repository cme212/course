#include <iostream>

/** 
 * @brief Search a sorted array for a value using binary search.
 *
 * @param[in] a        Sorted array of floats.
 * @param[in] low,high Search in the index range [ low,  high).
 * @param[in] v        Value to search for.
 * @return    An index into array _a_ or -1.
 * 
 * @pre 0 <= low < high <= Size of the array  _a_.
 * @pre For all i,j with low <= i < j <  high,  a[i] <=  a[j].
 * @post (low <= result <  high and  a[result] ==  v) 
 *    or (result == -1 and there is no _i_ s.t. low <= i < high, and  a[i] == v).
 *
 * Complexity O(log(high - low))
 */
int binary_search(const float* a, int low, int high, float v)
{
  --high;
  const float eps = 1e-10f;

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

  std::cout << binary_search(a, 0, 10, 74.) << "\n";
  std::cout << binary_search(a, 0, 10, 73.) << "\n";
  std::cout << binary_search(a, 0, 10,  2.) << "\n";
  
  return 0;
}
