#include "common.hpp"

using namespace std;

int main() {
  ifstream in("day_2015_05");

  std::vector<std::string> words;

  std::string word;
  while (getline(in, word)) words.push_back(word);

  {  // part1
    int nice = 0;
    for (std::string_view word : words) {
      if (word.contains("ab") || word.contains("cd") || word.contains("pq") || word.contains("xy"))
        continue;

      int vowelCount = 0;
      for (char c : word) {
        if (vowelCount >= 3) break;
        static constexpr std::string_view vowels("aeiou");
        vowelCount += vowels.contains(c);
      }
      if (vowelCount < 3) continue;

      bool twice = false;
      for (char c = 'a'; !twice && c <= 'z'; ++c) {
        twice = word.contains(std::string(2, c));
      }
      if (!twice) continue;

      ++nice;
    }
    expectEq(nice, 236);
  }
  {  // part2
    int nice = 0;
    for (std::string_view word : words) {
      bool rule1 = false;
      for (int i = 0; !rule1 && i < word.size() - 1; ++i) {
        rule1 = word.substr(i + 2).contains(word.substr(i, 2));
      }
      if (!rule1) continue;

      bool rule2 = false;
      for (char c = 'a'; !rule2 && c <= 'z'; ++c) {
        for (char d = 'a'; !rule2 && d <= 'z'; ++d) {
          std::string s(3, c);
          s[1]  = d;
          rule2 = word.contains(s);
        }
      }
      if (!rule2) continue;

      ++nice;
    }
    expectEq(nice, 51);
  }

  return 0;
}
