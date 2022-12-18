#include "common.hpp"

int main() {
  std::ifstream in("day_2018_02");

  std::vector<std::string> lines;
  std::string              line;
  int                      two{}, three{};
  while (std::getline(in, line)) {
    lines.push_back(line);
    std::map<char, int> m;
    for (char c : line) {
      ++m[c];
    }
    for (auto [c, o] : m) {
      if (o == 2) {
        ++two;
        break;
      }
    }
    for (auto [c, o] : m) {
      if (o == 3) {
        ++three;
        break;
      }
    }
  }
  expectEq(two * three, 5750);

  bool done = false;
  for (int i = 0; !done && i < lines.size(); ++i) {
    for (int j = i + 1; !done && j < lines.size(); ++j) {
      int diff = 0;
      for (int c = 0; diff <= 1 && c < lines[i].size(); ++c) {
        diff += lines[i][c] != lines[j][c];
      }
      if (diff == 1) {
        done = true;
        std::string answer;
        for (int c = 0; c < lines[i].size(); ++c) {
          if (lines[i][c] == lines[j][c]) answer += lines[i][c];
        }
        expectEq(answer, "tzyvunogzariwkpcbdewmjhxi");
      }
    }
  }

  return 0;
}
