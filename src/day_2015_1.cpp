#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream in("day_2015_1");

  std::string line;
  in >> line;
  int floor = 0;
  for (int i = 0; i < line.size(); ++i) {
    floor += line[i] == '(' ? 1 : -1;
    if (floor < 0) {
      cout << "Basement: " << (i + 1) << endl;
      break;
    }
  }

  return 1;
}
