#include "common.hpp"

using namespace std;

int main() {
  ifstream in("day_2015_01");

  std::string line;
  in >> line;
  int floor = 0;
  for (int i = 0; i < line.size(); ++i) {
    floor += line[i] == '(' ? 1 : -1;
    if (floor < 0) {
      expectEq(i + 1, 1795);
      break;
    }
  }

  return 0;
}
