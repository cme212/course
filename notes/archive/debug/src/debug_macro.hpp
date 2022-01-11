#include <iostream>

#ifdef PRINT_DEBUG
#define BUGPRINT(x)                                     \
  do {                                                  \
    std::cerr << __FILE__ << ":" << __LINE__ << ": ";   \
    std::cerr << #x << " -> " << (x) << std::endl;      \
  } while (0)
#else
#define BUGPRINT(X)
#endif
