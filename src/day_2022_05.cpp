#include "common.hpp"

using namespace std;

int main() {
  ifstream in("day_2022_05");

  std::vector<std::string> lines;
  std::string              line;
  while (std::getline(in, line), !line.empty()) {
    lines.insert(lines.begin(), line);
  }

  std::vector<std::vector<char>> stacks((lines[0].size() + 1) / 4);
  for (int y = 1; y < lines.size(); ++y) {
    const auto& line = lines[y];
    for (int s = 0; s < stacks.size(); ++s) {
      if (line[1 + s * 4] != ' ') {
        stacks[s].push_back(line[1 + s * 4]);
      }
    }
  }

  auto stacks1 = stacks;
  auto stacks2 = stacks;

  int count, from, to;
  while (in >> line >> count >> line >> from >> line >> to) {
    --from;
    --to;

    // part 2
    std::move(stacks2[from].end() - count, stacks2[from].end(), std::back_inserter(stacks2[to]));
    stacks2[from].erase(stacks2[from].end() - count, stacks2[from].end());

    // part 1
    while (count--) {
      stacks1[to].push_back(stacks1[from].back());
      stacks1[from].pop_back();
    }
  }

  std::string part1, part2;
  for (const auto& stack : stacks1) part1 += stack.back();
  for (const auto& stack : stacks2) part2 += stack.back();

  expectEq(part1, "FJSRQCFTN");
  expectEq(part2, "CJVLJQPHS");

  return 0;
}
