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

  using Memo = std::array<std::array<std::array<int_fast8_t, 22>, 22>, 22>;
  Memo cubes{};

  int minX = 100, minY = 100, minZ = 100;
  int maxX = 0, maxY = 0, maxZ = 0;

  int  x, y, z;
  char garbage;
  while (in >> x >> garbage >> y >> garbage >> z) {
    ++x;
    ++y;
    ++z;
    cubes[x][y][z] = 1;

    minX = std::min(minX, x - 1);
    minY = std::min(minY, y - 1);
    minZ = std::min(minZ, z - 1);
    maxX = std::max(maxX, x + 1);
    maxY = std::max(maxY, y + 1);
    maxZ = std::max(maxZ, z + 1);
  }

  {
    int surfaceArea = 0;
    for (int x = 1; x <= 20; ++x) {
      for (int y = 1; y <= 20; ++y) {
        for (int z = 1; z <= 20; ++z) {
          surfaceArea +=
              cubes[x][y][z] * (6 - cubes[x - 1][y][z] - cubes[x + 1][y][z] - cubes[x][y - 1][z] -
                                cubes[x][y + 1][z] - cubes[x][y][z - 1] - cubes[x][y][z + 1]);
        }
      }
    }
    expectEq(surfaceArea, 3542);
  }

  {
    int               surfaceArea = 0;
    Memo              visited{};
    std::queue<Coord> q;
    q.push({0, 0, 0});
    while (!q.empty()) {
      const auto [x, y, z] = q.front();
      q.pop();
      if (visited[x][y][z]) continue;
      visited[x][y][z] = 1;

      for (const auto [dx, dy, dz] : Directions) {
        const int nx = x + dx;
        const int ny = y + dy;
        const int nz = z + dz;
        if (nx < minX || ny < minY || nz < minZ || nx > maxX || ny > maxY || nz > maxZ) continue;
        if (visited[nx][ny][nz]) continue;
        if (cubes[nx][ny][nz])
          ++surfaceArea;
        else
          q.push({nx, ny, nz});
      }
    }
    expectEq(surfaceArea, 2080);
  }

  return 0;
}
