#include "common.hpp"

using namespace std;

using Int = std::uint64_t;

struct Monkey {
  std::vector<Int>        items;
  std::function<Int(Int)> operation;
  Int                     M, monkey0, monkey1;
  Int                     inspections = 0;
};

static const std::vector<Monkey> StartingMonkeys{{
    Monkey{{50, 70, 89, 75, 66, 66}, [](Int old) { return old * 5; }, 2, 2, 1},
    Monkey{{85}, [](Int old) { return old * old; }, 7, 3, 6},
    Monkey{{66, 51, 71, 76, 58, 55, 58, 60}, [](Int old) { return old + 1; }, 13, 1, 3},
    Monkey{{79, 52, 55, 51}, [](Int old) { return old + 6; }, 3, 6, 4},
    Monkey{{69, 92}, [](Int old) { return old * 17; }, 19, 7, 5},
    Monkey{{71, 76, 73, 98, 67, 79, 99}, [](Int old) { return old + 8; }, 5, 0, 2},
    Monkey{{82, 76, 69, 69, 57}, [](Int old) { return old + 7; }, 11, 7, 4},
    Monkey{{65, 79, 86}, [](Int old) { return old + 5; }, 17, 5, 0},
}};

int main() {
  Int  M       = 9699690;
  auto monkeys = StartingMonkeys;
  for (int iteration = 0; iteration < 10000; ++iteration) {
    for (auto& monkey : monkeys) {
      for (Int item : monkey.items) {
        item = monkey.operation(item) % M;
        if (item % monkey.M == 0) {
          monkeys[monkey.monkey0].items.push_back(item);
        } else {
          monkeys[monkey.monkey1].items.push_back(item);
        }
        ++monkey.inspections;
      }
      monkey.items.clear();
    }
  }
  std::sort(monkeys.begin(), monkeys.end(), [](auto& a, auto& b) {
    return a.inspections > b.inspections;
  });
  Int prod = monkeys[0].inspections * monkeys[1].inspections;
  expectEq(prod, 51382025916);
  return 0;
}
