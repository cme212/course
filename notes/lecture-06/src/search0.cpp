#include <iostream>

/** 
 * @brief Search a sorted array for a value using binary search.
 *
 */
int binary_search(float* a, int n, float v)
{
  int low = 0;
  int high = n-1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (a[mid] < v)
      low = mid + 1;
    else if (a[mid] > v)
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
  std::cout << binary_search(a, 10, 89.) << "\n";
  std::cout << binary_search(a, 10, 90.) << "\n";
  
  return 0;
}
