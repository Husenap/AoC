#include "common.hpp"

using namespace std;

int main() {
  ifstream in("day_2022_8");

  std::vector<std::string> lines;
  std::string              line;
  while (std::getline(in, line)) {
    lines.push_back(line);
  }

  const int rows = lines.size();
  const int cols = lines[0].size();

  int tot             = rows * cols;
  int bestScenicScore = 0;

  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      int covered = 0;
      int score   = 1;
      int steps   = 0;
      for (int ny = y - 1; ny >= 0; --ny) {
        ++steps;
        if (lines[ny][x] >= lines[y][x]) {
          ++covered;
          break;
        }
      }
      score *= steps;
      steps = 0;
      for (int ny = y + 1; ny < rows; ++ny) {
        ++steps;
        if (lines[ny][x] >= lines[y][x]) {
          ++covered;
          break;
        }
      }
      score *= steps;
      steps = 0;
      for (int nx = x - 1; nx >= 0; --nx) {
        ++steps;
        if (lines[y][nx] >= lines[y][x]) {
          ++covered;
          break;
        }
      }
      score *= steps;
      steps = 0;
      for (int nx = x + 1; nx < cols; ++nx) {
        ++steps;
        if (lines[y][nx] >= lines[y][x]) {
          ++covered;
          break;
        }
      }
      score *= steps;
      bestScenicScore = std::max(bestScenicScore, score);
      if (covered == 4) --tot;
    }
  }

  expectEq(tot, 1676);
  expectEq(bestScenicScore, 313200);

  return 0;
}
