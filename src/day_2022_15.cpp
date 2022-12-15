#include "common.hpp"

using namespace std;

struct Pos {
  int x, y;
};
std::vector<std::pair<Pos, int>> sensors;

static constexpr int lowerRange = 0;
static constexpr int upperRange = 4000000;

inline void isValid(Pos p) {
  if (p.x < lowerRange || p.x > upperRange || p.y < lowerRange || p.y > upperRange) return;
  for (const auto& [sensor, range] : sensors) {
    const auto dx       = p.x - sensor.x;
    const auto dy       = p.y - sensor.y;
    const auto distance = std::abs(dx) + std::abs(dy);
    if (distance <= range) return;
  }

  expectEq(p.x * 4000000ull + p.y, 11796491041245ull);
  exit(0);
};

int main() {
  ifstream in("day_2022_15");

  Pos sensor, beacon;

  in.ignore(12);
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

    const auto distance = std::abs(beacon.x - sensor.x) + std::abs(beacon.y - sensor.y);
    sensors.emplace_back(sensor, distance);
  }

#pragma omp parallel for
  for (const auto& [pos, range] : sensors) {
    const int d = range + 1;
    for (int dx = -d; dx <= d; ++dx) {
      const int y = d - std::abs(dx);
      const int x = pos.x + dx;
      isValid({x, pos.y - y});
      isValid({x, pos.y + y});
    }
  }

  return 0;
}
