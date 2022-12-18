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

  using Memo = std::array<std::array<std::array<int_fast32_t, 22>, 22>, 22>;
  Memo cubes{};

  int minX = 100, minY = 100, minZ = 100;
  int maxX = 0, maxY = 0, maxZ = 0;

  const auto calcSurfaceArea = [&cubes] {
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
    return surfaceArea;
  };

  int  x, y, z;
  char garbage;
  while (in >> x >> garbage >> y >> garbage >> z) {
    ++x;
    ++y;
    ++z;
    cubes[x][y][z] = 1;

    minX = std::min(minX, x);
    minY = std::min(minY, y);
    minZ = std::min(minZ, z);
    maxX = std::max(maxX, x);
    maxY = std::max(maxY, y);
    maxZ = std::max(maxZ, z);
  }
  expectEq(calcSurfaceArea(), 3542);

  Memo visited{};
  for (int x = 1; x <= 20; ++x) {
    for (int y = 1; y <= 20; ++y) {
      for (int z = 1; z <= 20; ++z) {
        if (!cubes[x][y][z]) continue;
        for (const auto [dx, dy, dz] : Directions) {
          const int rx = x + dx;
          const int ry = y + dy;
          const int rz = z + dz;
          Coord     root{rx, ry, rz};
          if (rx < minX || ry < minY || rz < minZ || rx > maxX || ry > maxY || rz > maxZ) continue;
          if (visited[rx][ry][rz]) continue;

          std::queue<Coord>  q;
          std::vector<Coord> blob;
          q.push(root);
          blob.push_back(root);

          bool exposed = false;
          while (!q.empty()) {
            const auto [x, y, z] = q.front();
            q.pop();

            for (const auto [dx, dy, dz] : Directions) {
              const int nx = x + dx;
              const int ny = y + dy;
              const int nz = z + dz;
              if (nx < minX || ny < minY || nz < minZ || nx > maxX || ny > maxY || nz > maxZ) {
                exposed = true;
                continue;
              }
              const Coord next{nx, ny, nz};
              if (cubes[nx][ny][nz]) continue;
              if (visited[nx][ny][nz]) continue;
              visited[nx][ny][nz] = true;
              blob.push_back(next);
              q.push(next);
            }
          }

          if (!exposed) {
            for (auto [x, y, z] : blob) {
              cubes[x][y][z] = 1;
            }
          }
        }
      }
    }
  }
  expectEq(calcSurfaceArea(), 2080);
  return 0;
}
