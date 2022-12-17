#include "common.hpp"

int main() {
  std::ifstream in("day_2017_02");

  std::vector<std::vector<int>> rows;

  int checksum = 0;

  std::string line;
  while (std::getline(in, line)) {
    rows.emplace_back();

    int min = 1000000;
    int max = 0;

    for (auto word : shared::split_regex(line, "\\s+")) {
      const int n = std::stoi(word);
      min         = std::min(min, n);
      max         = std::max(max, n);
      rows.back().push_back(n);
    }
    checksum += max - min;
  }
  expectEq(checksum, 44887);

  int sum = 0;
  for (auto& row : rows) {
    bool done = false;
    for (int i = 0; !done && i < row.size(); ++i) {
      for (int j = 0; !done && j < row.size(); ++j) {
        if (row[i] == row[j]) continue;
        if (row[i] % row[j]) continue;
        sum += row[i] / row[j];
        done = true;
      }
    }
  }
  expectEq(sum, 242);

  return 0;
}
