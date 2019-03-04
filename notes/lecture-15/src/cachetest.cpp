#include <iostream>
#include <cstdlib>
#include <time.h>

/**
 * Dense matrix implemented as an array of arrays
 */
class Matrix
{
public:
  Matrix(int N) : N_(N)
  {
    data_ = new double*[N];
    for (int i=0; i<N; ++i)
      data_[i] = new double[N];
  }

  ~Matrix()
  {
    for(int i=0; i < N_; ++i)
      delete data_[i];
    delete [] data_;
  }

  int size()
  {
    return N_;
  }
  
  double* operator[](int i)
  {
    return data_[i];
  }
  
private:
  double** data_;
  int N_;
};


void randMatrix(Matrix& m)
{
  int N = m.size();
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      m[i][j] = ((double) rand())/RAND_MAX;
}

double sumMatrixRow(Matrix& m)
{
  double sum = 0.0;
  int N = m.size();
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      sum += m[i][j];
  return sum;
}

double sumMatrixColumn(Matrix& m)
{
  double sum = 0.0;
  int N = m.size();
  for(int j=0; j<N; ++j)
    for(int i=0; i<N; ++i)
      sum += m[i][j];
  return sum;
}


int main()
{
  clock_t start=0, end=0;
  int N = 8000;

  {
    Matrix m(N);
    randMatrix(m);

    start=clock();
    double sum = sumMatrixRow(m);
    end=clock();
    std::cout << "Row-wise matrix sum:    " << sum << "\n";
    std::cout << "Row-wise sum time:      " << ((double) end - start)/CLOCKS_PER_SEC << "\n";
  }
  
  {
    Matrix m(N);
    randMatrix(m);

    start=clock();
    double sum = sumMatrixColumn(m);
    end=clock();
    std::cout << "Column-wise matrix sum: " << sum << "\n";
    std::cout << "Column-wise sum time:   " << ((double) end - start)/CLOCKS_PER_SEC << "\n";
  }
  
  return 0;
}
