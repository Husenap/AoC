#include "common.hpp"

using namespace std;

int main() {
  ifstream in("day_2022_4");

  int contained   = 0;
  int overlapping = 0;

  int a, b, c, d;

  while (in >> a) {
    in.ignore();
    in >> b;
    in.ignore();
    in >> c;
    in.ignore();
    in >> d;

    if ((a >= c && b <= d) || (c >= a && d <= b)) ++contained;

    if (!((a < c && b < c) || (a > d && b > d))) ++overlapping;
  }

  expectEq(contained, 500);
  expectEq(overlapping, 815);

  return 0;
}
