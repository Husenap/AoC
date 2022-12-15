#include <cstdint>

#include "common.hpp"

using namespace std;

struct Pos {
  int x, y;

  friend Pos operator+(const Pos& lhs, const Pos& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }
  friend Pos operator-(const Pos& lhs, const Pos& rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y}; }

  bool operator==(const Pos& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(const Pos& rhs) const { return !(*this == rhs); }

  friend std::ostream& operator<<(std::ostream& os, const Pos& pos) {
    os << "(" << pos.x << "," << pos.y << ")";
    return os;
  }
};

int main() {
  ifstream in("day_2022_15");

  int64_t lowerRange = 0;
  int64_t upperRange = 4000000;

  std::vector<std::vector<std::pair<int64_t, int64_t>>> rows(
      upperRange + 1, std::vector{std::make_pair(lowerRange, upperRange)});

  const auto dump = [&rows] {
    int y = -1;
    for (auto& row : rows) {
      ++y;
      if (row.empty()) continue;
      cerr << y << ": ";
      for (auto& [l, r] : row) {
        cerr << l << "->" << r << ", ";
        expectEq(l * 4000000 + y, 11796491041245);
      }
      cerr << endl;
    }
  };

  in.ignore(12);
  Pos sensor, beacon;
  while (in >> sensor.x) {
    in.ignore(4);
    in >> sensor.y;
    in.ignore(25);
    in >> beacon.x;
    in.ignore(4);
    in >> beacon.y;
    std::string garbage;
    std::getline(in, garbage);
    in.ignore(12);

    const auto delta    = beacon - sensor;
    const auto distance = std::abs(delta.x) + std::abs(delta.y);
#pragma omp parallel for
    for (int y = sensor.y - distance; y <= sensor.y + distance; ++y) {
      if (y < lowerRange || y > upperRange) continue;
      const auto offset = distance - std::abs(y - sensor.y);
      const int  l      = sensor.x - offset;
      const int  r      = sensor.x + offset;
      const auto row    = rows[y];
      rows[y].clear();
      for (auto [left, right] : row) {
        if (r < left || l > right) {
          rows[y].emplace_back(left, right);
          continue;
        }
        const auto s1 = std::make_pair(left, l - 1);
        const auto s2 = std::make_pair(r + 1, right);
        if (s1.first <= s1.second) rows[y].push_back(s1);
        if (s2.first <= s2.second) rows[y].push_back(s2);
      }
    }
  }

  dump();

  return 0;
}
