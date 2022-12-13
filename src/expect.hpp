#include <iostream>

template <typename T, typename U>
void expectEq(const T& value, const U& expected) {
  if (value == expected) return;
  std::cerr << "Expected equality between:" << std::endl;
  std::cerr << "   value:" << value << std::endl;
  std::cerr << "expected:" << expected << std::endl;
  exit(1);
}