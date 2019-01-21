
// Use screaming letters to define macro!
#ifdef PRINT_DEBUG
#define BUGPRINT(x)                                     \
  do {                                                  \
    std::cerr << __FILE__ << ":" << __LINE__ << ": ";   \
    std::cerr << #x << " -> " << (x) << std::endl;      \
  } while (0)
#else
#define BUGPRINT(x)
#endif

#define TWOX(x) x*2
