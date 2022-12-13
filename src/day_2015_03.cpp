#include "common.hpp"

using namespace std;

int main() {
  ifstream in("day_2015_03");

  using Pos = std::pair<int, int>;

  std::set<Pos> houses;

  std::array<Pos, 2> pos;
  int                index = 0;
  houses.insert(pos[index]);

  char c;
  while (in >> c) {
    switch (c) {
    case '>':
      ++pos[index].first;
      break;
    case '<':
      --pos[index].first;
      break;
    case 'v':
      --pos[index].second;
      break;
    case '^':
      ++pos[index].second;
      break;
    }
    houses.insert(pos[index]);
    index = 1 - index;
  }
  expectEq(houses.size(), 2639);

  return 0;
}
