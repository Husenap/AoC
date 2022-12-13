#include "common.hpp"

using namespace std;

using Pos = std::pair<int, int>;

static const std::map<char, Pos> Delta = {{
    {'L', {-1, 0}},
    {'D', {0, -1}},
    {'U', {0, 1}},
    {'R', {1, 0}},
}};

int main() {
  ifstream in("day_2022_09");

  {
    std::array<Pos, 10> Ps;
    std::set<Pos>       visited;
    visited.insert(Ps.back());

    char dir;
    int  steps;
    while (in >> dir >> steps) {
      const auto delta = Delta.at(dir);
      while (steps--) {
        Ps[0].first += delta.first;
        Ps[0].second += delta.second;
        for (int i = 1; i < Ps.size(); ++i) {
          auto& previous = Ps[i - 1];
          auto& current  = Ps[i];

          if (std::abs(current.first - previous.first) > 1 ||
              std::abs(current.second - previous.second) > 1) {
            if (current.first < previous.first) {
              ++current.first;
            }
            if (current.second < previous.second) {
              ++current.second;
            }
            if (current.first > previous.first) {
              --current.first;
            }
            if (current.second > previous.second) {
              --current.second;
            }
          }
        }
        visited.insert(Ps.back());
      }
    }
    expectEq(visited.size(), 2352);
  }

  return 0;
}
