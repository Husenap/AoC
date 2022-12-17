#include "common.hpp"

int main() {
  std::ifstream in("day_2019_01");

  int totalFuel = 0;

  int fuel = 0, mass;
  while (in >> mass) {
    fuel += mass / 3 - 2;

    while (mass > 0) {
      mass = mass / 3 - 2;
      if (mass <= 0) break;
      totalFuel += mass;
    }
  }
  expectEq(fuel, 3233481);
  expectEq(totalFuel, 4847351);

  return 0;
}
