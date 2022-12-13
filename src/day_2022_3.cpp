#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int priority(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 1;
  }
  return c - 'A' + 27;
}

int main() {
  ifstream in("day_2022_3");

  std::string line;
  int         sum = 0;

  int                           groupSum = 0;
  int                           group    = 0;
  std::array<std::set<char>, 3> groupSets;

  while (std::getline(in, line)) {
    // part 1
    std::set<char> seen;
    for (int i = 0; i < line.size() / 2; ++i) {
      seen.insert(line[i]);
    }
    for (int i = line.size() / 2; i < line.size(); ++i) {
      if (seen.count(line[i])) {
        sum += priority(line[i]);
        break;
      }
    }

    // part 2
    for (char c : line) {
      groupSets[group].insert(c);
    }
    if (group == 2) {
      std::vector<char> result;
      std::set_intersection(groupSets[0].begin(),
                            groupSets[0].end(),
                            groupSets[1].begin(),
                            groupSets[1].end(),
                            std::back_inserter(result));
      std::vector<char> result1;
      std::set_intersection(groupSets[2].begin(),
                            groupSets[2].end(),
                            result.begin(),
                            result.end(),
                            std::back_inserter(result1));
      groupSum += priority(result1.front());
      for (auto& s : groupSets) s.clear();
    }
    group = (group + 1) % 3;
  }

  cout << sum << endl;
  cout << groupSum << endl;

  return 1;
}
