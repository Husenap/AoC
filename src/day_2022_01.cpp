#include "common.hpp"

using namespace std;

int main() {
  ifstream in("day_2022_01");

  std::string      line;
  int              sum = 0;
  std::vector<int> sums;
  while (std::getline(in, line)) {
    if (line.empty()) {
      sums.push_back(sum);
      sum = 0;
    } else {
      sum += std::stoi(line);
    }
  }

  std::sort(sums.begin(), sums.end());

  const int tot = sums[sums.size() - 1] + sums[sums.size() - 2] + sums[sums.size() - 3];

  expectEq(tot, 203420);

  return 0;
}
