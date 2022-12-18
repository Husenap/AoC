#include "common.hpp"

using Coord = std::tuple<int, int, int>;

static constexpr std::array<Coord, 6> Directions{{
    {-1, 0, 0},
    {1, 0, 0},
    {0, -1, 0},
    {0, 1, 0},
    {0, 0, -1},
    {0, 0, 1},
}};

int main() {
  std::ifstream in("day_2022_18");

  std::set<Coord> cubes;

  int  x, y, z;
  char garbage;

  Coord min{100, 100, 100};
  Coord max{0, 0, 0};
  auto& [minX, minY, minZ] = min;
  auto& [maxX, maxY, maxZ] = max;

  while (in >> x >> garbage >> y >> garbage >> z) {
    shared::format_to(std::cerr, "({},{},{})\n", x, y, z);
    cubes.insert({x, y, z});

    minX = std::min(minX, x);
    minY = std::min(minY, y);
    minZ = std::min(minZ, z);
    maxX = std::max(maxX, x);
    maxY = std::max(maxY, y);
    maxZ = std::max(maxZ, z);
  }

  {
    int surfaceArea = 0;
    for (auto [x, y, z] : cubes) {
      int sides = 6;
      for (auto [dx, dy, dz] : Directions) {
        if (cubes.contains({x + dx, y + dy, z + dz})) --sides;
      }
      surfaceArea += sides;
    }
    expectEq(surfaceArea, 3542);
  }

  std::set<Coord> visited;
  for (auto [x, y, z] : cubes) {
    for (auto [dx, dy, dz] : Directions) {
      Coord root{x + dx, y + dy, z + dz};
      if (cubes.contains(root)) continue;
      if (visited.contains(root)) continue;

      std::queue<Coord> q;
      std::set<Coord>   blob;
      q.push(root);
      blob.insert(root);

      bool exposed = false;
      while (!q.empty()) {
        const auto [x, y, z] = q.front();
        q.pop();

        for (auto [dx, dy, dz] : Directions) {
          Coord next{x + dx, y + dy, z + dz};
          if (x < minX || y < minY || z < minZ || x > maxX || y > maxY || z > maxZ) {
            exposed = true;
            continue;
          }
          if (cubes.contains(next)) continue;
          if (visited.contains(next)) continue;
          visited.insert(next);
          blob.insert(next);
          q.push(next);
        }
      }

      if (exposed) {
      } else {
        for (auto p : blob) {
          cubes.insert(p);
        }
      }
    }
  }

  {
    int surfaceArea = 0;
    for (auto [x, y, z] : cubes) {
      int sides = 6;
      for (auto [dx, dy, dz] : Directions) {
        if (cubes.contains({x + dx, y + dy, z + dz})) --sides;
      }
      surfaceArea += sides;
    }
    expectEq(surfaceArea, 2080);
  }

  return 0;
}
