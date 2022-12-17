#include "common.hpp"
#include "format.hpp"

static constexpr std::string_view textShapes = R"(####

.#.
###
.#.

..#
..#
###

#
#
#
#

##
##)";

using Coord = std::pair<int, int>;

std::vector<std::vector<Coord>> shapes;
std::string                     gas;

struct Solve {
  int64_t     startingRocks;
  int64_t     rocks       = 0;
  int         gasIndex    = 0;
  int64_t     height      = 0;
  int64_t     addedHeight = 0;
  __uint128_t state       = 0;

  std::set<Coord>                                                          occupied;
  std::map<std::tuple<int, int, __uint128_t>, std::pair<int64_t, int64_t>> memo;

  bool intersects(const std::vector<Coord>& rock, Coord pos) {
    for (auto [px, py] : rock) {
      const int x = pos.first + px;
      const int y = pos.second + py;
      if (x < 0 || x >= 7 || y < 0 || occupied.contains({x, y})) return true;
    }
    return false;
  }
  void simulate(int rockIndex) {
    const auto memoIndex = std::make_tuple(rockIndex, gasIndex, state);
    if (memo.contains(memoIndex)) {
      auto [r, h] = memo[memoIndex];
      h           = height - h;
      r           = rocks - r;

      const int64_t multiple = (startingRocks - rocks) / r;

      rocks += r * multiple;
      addedHeight += h * multiple;
    }

    bool       fall = false;
    const auto rock = shapes[rockIndex];
    Coord      pos{2, height + 3};
    while (true) {
      if (fall) {
        if (!intersects(rock, {pos.first, pos.second - 1})) {
          --pos.second;
        } else {
          break;
        }
      } else {
        const int gasDirection = gas[gasIndex] == '>' ? 1 : -1;
        if (!intersects(rock, {pos.first + gasDirection, pos.second})) {
          pos.first += gasDirection;
        }
        gasIndex = (gasIndex + 1) % gas.size();
      }
      fall = !fall;
    }
    int previousHeight = height;
    for (auto [px, py] : rock) {
      const int x = pos.first + px;
      const int y = pos.second + py;
      occupied.emplace(x, y);
      height = std::max<int64_t>(height, y + 1);
    }
    state = 0;
    for (int y = height - 11; y < height; ++y) {
      state <<= 7;
      for (int x = 0; x < 7; ++x) {
        if (occupied.contains({x, y})) state |= (1 << x);
      }
    }
    if (!memo.contains(memoIndex)) memo[memoIndex] = std::make_pair(rocks, height);
  }
  int64_t solve() {
    int rockIndex = 0;
    while (rocks++ < startingRocks) {
      simulate(rockIndex);
      rockIndex = (rockIndex + 1) % shapes.size();
    }
    return height + addedHeight;
  }
};

int main() {
  std::ifstream in("day_2022_17");

  std::getline(in, gas);

  const auto splits = shared::split_regex(textShapes, "\n\n");

  for (const auto& shape : splits) {
    std::vector<Coord> coords;

    const auto lines = shared::split_regex(shape, "\n");
    const int  h     = lines.size() - 1;
    for (int j = 0; j < lines.size(); ++j) {
      for (int i = 0; i < lines[j].size(); ++i) {
        if (lines[j][i] == '#') coords.emplace_back(i, h - j);
      }
    }
    shapes.push_back(coords);
  }

  expectEq(Solve{2022}.solve(), 3215);
  expectEq(Solve{1000000000000ll}.solve(), 1575811209487ll);

  return 0;
}
