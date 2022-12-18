#include <cstdlib>
#include <iostream>

static bool hasFailed = false;
static void expectExitHandler() {
  if (hasFailed) exit(1);
}

template <typename T, typename U>
void _expectEq(
    std::string_view file, int line, std::string_view svalue, const T& value, const U& expected) {
  static bool registeredHandler = false;
  if (!registeredHandler) {
    registeredHandler = true;
    std::atexit(expectExitHandler);
  }

  if (value == expected) return;
  hasFailed = true;
  std::cerr << std::endl;
  std::cerr << file << ":[" << line << "]: " << svalue << std::endl;
  std::cerr << "Expected equality between:" << std::endl;
  std::cerr << "   value: " << value << std::endl;
  std::cerr << "expected: " << expected << std::endl << std::endl;
}

#define expectEq(value, expected) _expectEq(__FILE__, __LINE__, #value, value, expected);