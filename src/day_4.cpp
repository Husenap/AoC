#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream in("day_4");

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

  cout << contained << endl;
  cout << overlapping << endl;

  return 1;
}
