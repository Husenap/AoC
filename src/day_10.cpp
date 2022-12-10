#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream in("day_10");

  std::vector<std::string> pixels(6, std::string(40, '.'));

  int X     = 1;
  int cycle = 0;

  int signal = 0;

  auto updateSignal = [&] {
    if ((cycle - 20) % 40 == 0) {
      cerr << "adding " << X * cycle << " at cycle " << cycle << endl;
      signal += X * cycle;
    }
  };
  auto updateScreen = [&] {
    int row = cycle / 40;
    int col = cycle % 40;
    if (cycle % 40 >= X - 1 && cycle % 40 <= X + 1) {
      pixels[row][col] = '#';
    }
  };

  std::string opcode;
  while (in >> opcode) {
    if (opcode == "noop") {
      updateScreen();
      ++cycle;
      updateSignal();
    } else if (opcode == "addx") {
      int n;
      in >> n;
      updateScreen();
      ++cycle;
      updateSignal();
      updateScreen();
      ++cycle;
      updateSignal();
      X += n;
    }
  }
  cout << "signal: " << signal << endl;
  cout << "screen: " << endl;
  for (const auto& row : pixels) {
    cout << row << endl;
  }

  return 1;
}
