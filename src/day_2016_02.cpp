#include "common.hpp"

static constexpr std::array<std::string_view, 5> WeirdPad{{
    "..1..",
    ".234.",
    "56789",
    ".ABC.",
    "..D..",
}};

int main() {
  std::ifstream in("day_2016_02");

  int r = 1, c = 1;
  int wr = 2, wc = 0;

  std::string code, weirdCode;

  std::string line;
  while (std::getline(in, line)) {
    for (char dir : line) {
      switch (dir) {
      case 'U':
        r = std::max(0, r - 1);
        if (wr > 0 && WeirdPad[wr - 1][wc] != '.') --wr;
        break;
      case 'D':
        r = std::min(2, r + 1);
        if (wr < 4 && WeirdPad[wr + 1][wc] != '.') ++wr;
        break;
      case 'L':
        c = std::max(0, c - 1);
        if (wc > 0 && WeirdPad[wr][wc - 1] != '.') --wc;
        break;
      case 'R':
        c = std::min(2, c + 1);
        if (wc < 4 && WeirdPad[wr][wc + 1] != '.') ++wc;
        break;
      }
    }

    code += std::to_string(r * 3 + c + 1);
    weirdCode += WeirdPad[wr][wc];
  }
  expectEq(code, "56983");
  expectEq(weirdCode, "8B8B1");

  return 0;
}
