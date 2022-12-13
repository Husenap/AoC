#include "common.hpp"

using namespace std;

int main() {
  ifstream in("day_2022_6");

  std::string message;
  in >> message;

  for (int i = 0; i < message.size(); ++i) {
    {  // part 1
      std::set<char> sfd;
      for (int s = i - 3; s <= i; ++s) {
        if (s >= 0) {
          sfd.insert(message[s]);
        }
      }
      static bool flag = false;
      if (!flag && sfd.size() == 4) {
        flag = true;
        expectEq(i + 1, 1566);
      }
    }
    {  // part 2
      std::set<char> sfd;
      for (int s = i - 13; s <= i; ++s) {
        if (s >= 0) {
          sfd.insert(message[s]);
        }
      }
      if (sfd.size() == 14) {
        expectEq(i + 1, 2265);
        break;
      }
    }
  }

  return 0;
}
