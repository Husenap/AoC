#include "common.hpp"

int main() {
  std::ifstream in("day_2016_01");

  int dx = 0, dy = 1;
  int x = 0, y = 0;

  std::string text;
  std::getline(in, text);
  std::set<std::pair<int, int>>      seen;
  std::optional<std::pair<int, int>> hq;
  for (std::string_view op : shared::split_regex(text, "[\\s,]+")) {
    if (op[0] == 'R') {
      dy = -std::exchange(dx, dy);
    } else {
      dx = -std::exchange(dy, dx);
    }
    int d = std::atoi(op.substr(1).data());
    while (d > 0) {
      x += dx;
      y += dy;
      --d;
      if (!hq) {
        const auto p = std::make_pair(x, y);
        if (seen.contains(p)) {
          hq = p;
        }
        seen.insert(p);
      }
    }
  }

  expectEq(std::abs(x) + std::abs(y), 278);
  expectEq(std::abs(hq->first) + std::abs(hq->second), 161);

  return 0;
}
