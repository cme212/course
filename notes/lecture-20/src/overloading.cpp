#include <iostream>
#include <vector>

using namespace std;

void addVectors(const vector<double>& x,
                const vector<double>& y,
                vector<double>& z)
{
  for(unsigned i=0; i < x.size(); ++i)
    z[i] = x[i]+y[i];
}

const vector<double> operator+(const vector<double>& x,
                               const vector<double>& y)
{
  vector<double> z(x);
  for(unsigned i=0; i< x.size(); ++i)
    z[i] = x[i]+y[i];
  return z;
}


int main()
{
  vector<double> x = {1., 2., 3.};
  vector<double> y = {2., 4., 6.};

  vector<double> z = x + y;
  for(unsigned i=0; i < z.size(); ++i)
    cout << "z[" << i << "] = " << z[i] << "\n";
  
  addVectors(x,y,y);
  for(unsigned i=0; i < y.size(); ++i)
    cout << "y[" << i << "] = " << y[i] << "\n";
  
  return 0;
}
