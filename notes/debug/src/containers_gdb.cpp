#include <iostream>
#include <map>
#include <vector>
#include <string>

// simple function to print map value designed for use in GDB
void mv(const std::map<std::string,int>& m, const char* a) {
  std::cout << m.at(a) << std::endl;
}

int main() {
  std::vector<int> x = {1,3,5,2,6};
  std::map<std::string,int> m = {{"one",1},{"two",2}};

  std::cout << "x[0] = " << x[0] << std::endl;
  std::cout << "m[\"two\"] = " << m["two"] << std::endl;
}
