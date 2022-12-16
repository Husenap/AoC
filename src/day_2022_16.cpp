#include "common.hpp"
#include "split.hpp"
#include "string_id.hpp"

using namespace std;

shared::string_id nameToId;

struct Valve {
  int              id;
  int              rate;
  std::vector<int> jumps;

  static Valve create(std::vector<std::string> splits) {
    Valve v;
    v.id   = nameToId(splits[1]);
    v.rate = std::stoi(splits[4].substr(5));
    for (int i = 9; i < splits.size(); ++i) v.jumps.push_back(nameToId(splits[i].substr(0, 2)));
    return v;
  }

  friend std::ostream& operator<<(std::ostream& os, const Valve& valve) {
    os << valve.id << ", " << valve.rate;
    for (const auto& jump : valve.jumps) {
      os << ", " << jump;
    }
    return os;
  }
};

int main() {
  ifstream in("day_2022_16_test");

  std::vector<Valve> valves;

  std::string line;
  while (std::getline(in, line)) {
    const auto splits = shared::split(line, ' ');
    const auto valve  = Valve::create(splits);
    valves.push_back(valve);
  }

  std::array<std::vector<int>, 30> table;

  std::queue<int> q;
  q.push(nameToId("AA"));
  for (int time = 30; time > 0; --time) {
    while (!q.empty()) {
      const auto current = q.front();
      q.pop();
      const auto& currentValve = valves[current];
      if (currentValve.rate > 0) {
      }
      for (auto jump : currentValve.jumps) {
      }
    }
  }

  int answer = 42;
  expectEq(answer, 1651);

  return 0;
}
