#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream in("day_6");

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
      if (sfd.size() == 4) {
        cout << "SFD: " << i + 1 << endl;
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
        cout << "SFM: " << i + 1 << endl;
        break;
      }
    }
  }

  return 1;
}
