#include "common.hpp"
#include "format.hpp"
#include "split.hpp"
#include "string_id.hpp"

using namespace std;

struct Solve {
  shared::string_id nameToId;

  std::map<int, std::unordered_set<int>> neighbours;
  std::map<int, int>                     flowRate;
  std::vector<std::vector<int>>          adj;

  using Memo = std::unordered_map<uint64_t, int>;

  inline void visit(
      const int currentNode, const int budget, const uint64_t state, const int value, Memo& memo) {
    memo[state] = std::max(memo[state], value);
    for (auto [nextNode, flow] : flowRate) {
      const uint64_t bit       = 1ull << nextNode;
      const int      newBudget = budget - 1 - adj[currentNode][nextNode];
      if (state & bit || newBudget < 0) continue;
      visit(nextNode, newBudget, state | bit, value + newBudget * flow, memo);
    }
  }

  void solve() {
    ifstream in("day_2022_16");

    std::string line;

    while (std::getline(in, line)) {
      const auto words = shared::split_regex(line, "[\\s=;,]+");
      const int  id    = nameToId(words[1]);
      const int  flow  = std::stoi(words[5]);
      if (flow > 0) flowRate[id] = flow;
      auto& neighs = neighbours[id];
      for (int i = 10; i < words.size(); ++i) {
        neighs.insert(nameToId(words[i]));
      }
    }

    adj.resize(neighbours.size(), std::vector<int>(neighbours.size(), 100));
    for (auto& [k1, v1] : neighbours) {
      for (auto& [k2, v2] : neighbours) {
        if (v1.contains(k2)) {
          adj[k1][k2] = 1;
        }
      }
    }

    for (int k = 0; k < adj.size(); ++k) {
      for (int i = 0; i < adj.size(); ++i) {
        for (int j = 0; j < adj.size(); ++j) {
          adj[i][j] = std::min(adj[i][j], adj[i][k] + adj[k][j]);
        }
      }
    }

    {
      Memo memo;
      visit(nameToId("AA"), 30, 0, 0, memo);
      int best = max_element(memo.begin(), memo.end(), [](const auto& a, const auto& b) {
                   return a.second < b.second;
                 })->second;
      expectEq(best, 1915);
    }
    {
      Memo memo;
      visit(nameToId("AA"), 26, 0, 0, memo);
      int best = 0;
      for (auto& [k1, v1] : memo) {
        for (auto& [k2, v2] : memo) {
          if (k1 & k2) continue;
          best = std::max(best, v1 + v2);
        }
      }
      expectEq(best, 2772);
    }
  }
};

int main() {
  Solve().solve();
  return 0;
}
