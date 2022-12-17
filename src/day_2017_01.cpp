#include "common.hpp"

int main() {
  std::ifstream in("day_2017_01");

  std::string line;
  in >> line;

  {
    int sum = 0;
    for (int i = 0; i < line.size(); ++i) {
      if (line[i] == line[(i + 1) % line.size()]) sum += line[i] - '0';
    }
    expectEq(sum, 1150);
  }
  {
    int sum = 0;
    for (int i = 0; i < line.size(); ++i) {
      if (line[i] == line[(i + line.size() / 2) % line.size()]) sum += line[i] - '0';
    }
    expectEq(sum, 0);
  }

  return 0;
}
