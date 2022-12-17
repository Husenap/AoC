#include <cstdlib>
#include <iostream>

static bool hasFailed = false;
static void expectExitHandler() {
  if (hasFailed) exit(1);
}

template <typename T, typename U>
void expectEq(const T& value, const U& expected) {
  static bool registeredHandler = false;
  if (!registeredHandler) {
    registeredHandler = true;
    std::atexit(expectExitHandler);
  }

  if (value == expected) return;
  hasFailed = true;
  std::cerr << "Expected equality between:" << std::endl;
  std::cerr << "   value: " << value << std::endl;
  std::cerr << "expected: " << expected << std::endl;
}