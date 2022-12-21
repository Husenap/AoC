#include "common.hpp"

using Number = u64;

int main() {
  std::ifstream in("day_2022_21");

  std::unordered_map<std::string, std::function<Number()>> monkeys;

  std::string rootLeft, rootRight;

  std::string line;
  while (std::getline(in, line)) {
    const auto splits = shared::split_regex(line, ":\\s+");
    const auto name   = splits[0];
    const auto action = splits[1];

    if (name == "root") {
      const auto actionSplits = shared::split(action, ' ');
      rootLeft                = actionSplits[0];
      rootRight               = actionSplits[2];
    }

    if (::isdigit(action[0])) {
      monkeys[name] = [&monkeys, action] { return std::stoi(action); };
    } else {
      const auto actionSplits = shared::split(action, ' ');
      monkeys[name]           = [&monkeys, actionSplits] {
        const auto m0 = monkeys[actionSplits[0]]();
        const auto m1 = monkeys[actionSplits[2]]();
        char       op = actionSplits[1][0];
        if (op == '+')
          return m0 + m1;
        else if (op == '-')
          return m0 - m1;
        else if (op == '*')
          return m0 * m1;
        else
          return m0 / m1;
      };
    }
  }

  expectEq(monkeys["root"](), 118565889858886);

  const auto right = monkeys[rootRight]();
  for (Number i = 3032671800350; i < 3032671800355; ++i) {
    monkeys["humn"] = [=] { return i; };
    const auto left = monkeys[rootLeft]();
    if (left == right) {
      std::cerr << "possible solution: " << i << std::endl;
    }
  }

  const auto left = monkeys[rootLeft]();
  expectEq(left, right);

  return 0;
}