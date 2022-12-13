#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream in("day_2022_1");

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

  int tot = sums[sums.size() - 1] + sums[sums.size() - 2] + sums[sums.size() - 3];

  cout << tot << endl;

  return 1;
}
