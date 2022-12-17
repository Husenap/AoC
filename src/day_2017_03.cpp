#include "common.hpp"

static constexpr std::array<std::pair<int, int>, 8> Directions{{
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
}};

int dist(int address) {
  int layer = 1;
  while (layer * layer < address) {
    layer += 2;
  }
  if (layer == 1) return 0;

  int yOffset = (address - (layer - 2) * (layer - 2)) % (layer - 1) - layer / 2;

  return layer / 2 + std::abs(yOffset);
}

int main() {
  std::ifstream in("day_2017_03");

  int address;
  in >> address;
  expectEq(dist(address), 326);

  std::map<std::pair<int, int>, int> memo;
  memo[{0, 0}] = 1;

  int layer    = 1;
  int lastCalc = 0;

  bool done = false;
  while (!done) {
    std::pair<int, int> p{layer, -(layer - 1)};
    const auto          calc = [&](std::pair<int, int> p) {
      int sum = 0;
      for (auto [x, y] : Directions) {
        sum += memo[{p.first + x, p.second + y}];
      }
      return memo[p] = lastCalc = sum;
    };
    while (!done && p.second < layer) {
      done = calc(p) > address;
      ++p.second;
    }
    while (!done && p.first > -layer) {
      done = calc(p) > address;
      --p.first;
    }
    while (!done && p.second > -layer) {
      done = calc(p) > address;
      --p.second;
    }
    while (!done && p.first <= layer) {
      done = calc(p) > address;
      ++p.first;
    }
    ++layer;
  }
  expectEq(lastCalc, 363010);

  return 0;
}
