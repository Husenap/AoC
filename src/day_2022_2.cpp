#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int choiceScore(int c) {
  return c + 1;
}
int gameScore(int me, int you) {
  if ((you + 1) % 3 == me) return 6;
  if ((me + 1) % 3 == you) return 0;
  return 3;
}

int main() {
  ifstream in("day_2022_2");

  char a, b;
  int  score  = 0;
  int  score2 = 0;
  while (in >> a >> b) {
    b -= 'X' - 'A';

    // part 1
    {
      int me  = b - 'A';
      int you = a - 'A';
      score += choiceScore(me);
      score += gameScore(me, you);
    }
    // part 2
    {
      int you = a - 'A';
      int me;
      switch (b) {
      case 'A':
        me = (you + 2) % 3;
        // loss
        break;
      case 'B':
        // draw
        me = you;
        break;
      case 'C':
        // win
        me = (you + 1) % 3;
        break;
      }
      score2 += choiceScore(me);
      score2 += gameScore(me, you);
    }
  }

  cout << score << endl;
  cout << score2 << endl;

  return 1;
}
