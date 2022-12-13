#include "common.hpp"

using namespace std;

int main() {
  ifstream in("day_2015_02");

  int  a, b, c;
  char x;

  int wrappingPaper = 0;
  int ribbon        = 0;
  while (in >> a >> x >> b >> x >> c) {
    const int a0   = a * b;
    const int a1   = a * c;
    const int a2   = b * c;
    const int area = 2 * (a0 + a1 + a2) + ranges::min({a0, a1, a2});
    wrappingPaper += area;

    std::array sides{a, b, c};
    ranges::sort(sides);
    ribbon += sides[0] * 2 + sides[1] * 2 + a * b * c;
  }

  cout << wrappingPaper << endl;
  cout << ribbon << endl;

  expectEq(wrappingPaper, 1598415);
  expectEq(ribbon, 3812909);

  return 0;
}
