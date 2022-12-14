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
  ifstream in("day_2022_14");

  std::vector<std::pair<Pos, Pos>> segments;

  Pos source{500, 0};
  Pos min{500, 0}, max{500, 0};

  std::string       line;
  std::stringstream ss;
  while (std::getline(in, line)) {
    ss.clear();
    ss << line;
    int              x, y;
    std::vector<Pos> positions;
    while (ss >> x) {
      ss.ignore();
      ss >> y;
      ss.ignore(4);
      positions.emplace_back(x, y);
      min.x = std::min(min.x, x);
      min.y = std::min(min.y, y);
      max.x = std::max(max.x, x);
      max.y = std::max(max.y, y);
    }
    for (int i = 1; i < positions.size(); ++i) {
      segments.emplace_back(positions[i - 1], positions[i]);
    }
  }
  min.x -= 500;
  max.x += 500;

  for (auto& [from, to] : segments) {
    from = from - min;
    to   = to - min;
  }
  max = max - min;
  max.y += 2;
  source = source - min;
  min    = min - min;

  segments.emplace_back(Pos{0, max.y}, max);

  cerr << "AABB: " << min << ", " << max << endl;
  cerr << "Source: " << source << endl;
  for (const auto& [from, to] : segments) {
    cerr << "from " << from << " to " << to << endl;
  }

  std::vector<std::string> grid(max.y + 1, std::string(max.x + 1, '.'));
  grid[source.y][source.x] = '+';
  for (const auto& [from, to] : segments) {
    const Pos delta{std::clamp(to.x - from.x, -1, 1), std::clamp(to.y - from.y, -1, 1)};
    for (auto pos = from; pos != to; pos = pos + delta) {
      grid[pos.y][pos.x] = '#';
    }
    grid[to.y][to.x] = '#';
  }

  static constexpr std::array<Pos, 3> directions{{{0, 1}, {-1, 1}, {1, 1}}};

  int  sandCount = 0;
  bool simulate  = true;
  while (simulate) {
    auto pos     = source;
    bool falling = true;
    while (falling) {
      bool success = false;
      for (const auto& dir : directions) {
        const auto next = pos + dir;
        if (grid[next.y][next.x] == '.') {
          pos     = next;
          success = true;
          break;
        }
      }
      if (pos == source) {
        ++sandCount;
        simulate = false;
      }
      if (!simulate) break;
      if (!success) {
        grid[pos.y][pos.x] = 'o';
        falling            = false;
        ++sandCount;
      }
    }
  }
  expectEq(sandCount, 25585);

  return 0;
}
