#include <iostream>

int sequence(int* x, int nvals) {
  int sum = 0;
  //for (int i = 0; i <= nvals; ++i) {
  for (int i = 0; i < nvals; ++i) {
    x[i] = i;
    sum += x[i];
  }
  return sum;
}

int main() {
  int nvals = 1000;
  int* sequence_data;
  sequence_data = new int[nvals];
  int sum = sequence(sequence_data, nvals);
  std::cout << "sum = " << sum << std::endl;
  delete [] sequence_data;
}
