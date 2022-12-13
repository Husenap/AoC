#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

using Coord = std::pair<int, int>;

static const std::vector<Coord> Directions{{
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1},
}};

int shortestPath(Coord start, Coord end, const std::vector<std::string>& grid) {
  const int rows = grid.size();
  const int cols = grid.front().size();

  std::priority_queue<std::pair<int, Coord>> frontier;
  std::map<Coord, Coord>                     cameFrom;
  std::map<Coord, int>                       costSoFar;

  frontier.push({0, start});
  cameFrom[start]  = start;
  costSoFar[start] = 0;

  while (!frontier.empty()) {
    const auto [currentPriority, current] = frontier.top();
    frontier.pop();

    if (current == end) break;

    for (const auto& [dx, dy] : Directions) {
      const int   x    = current.first + dx;
      const int   y    = current.second + dy;
      const Coord next = std::make_pair(x, y);
      if (x < 0 || x >= cols || y < 0 || y >= rows) continue;
      const int diff = (int)grid[y][x] - (int)grid[current.second][current.first];
      if (diff > 1) continue;
      const int newCost = costSoFar[current] + 1;
      if (!costSoFar.count(next) || newCost < costSoFar[next]) {
        costSoFar[next] = newCost;
        frontier.push({-newCost, next});
        cameFrom[next] = current;
      }
    }
  }

  if (costSoFar.count(end)) {
    return costSoFar[end];
  }
  return 10000;
}

int main() {
  ifstream in("day_2022_12");

  Coord start, end;

  std::vector<std::string> grid;
  {
    std::string line;
    while (std::getline(in, line)) {
      for (int x = 0; x < line.size(); ++x) {
        if (line[x] == 'S') {
          start   = {x, grid.size()};
          line[x] = 'a';
        } else if (line[x] == 'E') {
          end     = {x, grid.size()};
          line[x] = 'z';
        }
      }
      grid.push_back(line);
    }
  }

  int best = 10000;
  for (int y = 0; y < grid.size(); ++y) {
    for (int x = 0; x < grid[y].size(); ++x) {
      if (grid[y][x] != 'a') continue;
      int next = shortestPath({x, y}, end, grid);
      best     = std::min(next, best);
    }
  }

  cout << best << endl;

  return 1;
}
