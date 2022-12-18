#include "common.hpp"

int main() {
  std::ifstream in("day_2016_03");

  std::vector<std::array<int, 3>> rows;

  int a, b, c;
  int triangles{};
  while (in >> a >> b >> c) {
    triangles += a + b > c && a + c > b && b + c > a;
    rows.push_back({a, b, c});
  }
  expectEq(triangles, 1032);

  int verticalTriangles{};
  for (int C = 0; C < 3; ++C) {
    for (int R = 0; R < rows.size(); R += 3) {
      const int a = rows[R][C];
      const int b = rows[R + 1][C];
      const int c = rows[R + 2][C];
      verticalTriangles += a + b > c && a + c > b && b + c > a;
    }
  }
  expectEq(verticalTriangles, 1838);

  return 0;
}
