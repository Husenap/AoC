#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

struct Element {
  using Elements = std::vector<Element>;
  using Type     = std::variant<Elements, int>;
  Type        value;
  std::string originalText;

  bool isNumber() const { return std::holds_alternative<int>(value); }
  bool isList() const { return !isNumber(); }

  Element wrapToList() const { return Element{.value = Elements{{std::get<int>(value)}}}; }

  friend bool operator<(const Element& lhs, const Element& rhs) {
    if (lhs.isNumber() && rhs.isNumber()) {
      return std::get<int>(lhs.value) < std::get<int>(rhs.value);
    } else if (lhs.isList() && rhs.isList()) {
      const auto& leftItems  = std::get<Elements>(lhs.value);
      const auto& rightItems = std::get<Elements>(rhs.value);
      for (int i = 0; i < std::min(leftItems.size(), rightItems.size()); ++i) {
        if (leftItems[i] < rightItems[i]) {
          return true;
        } else if (rightItems[i] < leftItems[i]) {
          return false;
        }
      }
      if (leftItems.size() < rightItems.size()) {
        return true;
      } else if (rightItems.size() < leftItems.size()) {
        return false;
      }
    } else {
      if (lhs.isNumber()) {
        return lhs.wrapToList() < rhs;
      } else {
        return lhs < rhs.wrapToList();
      }
    }
    return false;
  }
};

Element parse(std::istream& text);

Element parseList(std::istream& text) {
  text.get();  // skip [

  std::vector<Element> items;
  while (text.peek() != ']') {
    items.push_back(parse(text));
    if (text.peek() == ',') text.get();
  }

  text.get();  // skip ]

  return Element{.value = items};
}
Element parseNumber(std::istream& text) {
  int number;
  text >> number;
  return Element{.value = number};
}

Element parse(std::istream& text) {
  if (text.peek() == '[') {
    return parseList(text);
  } else {
    return parseNumber(text);
  }
}
Element parse(std::string_view text) {
  std::stringstream ss;
  ss << text;
  Element e      = parse(ss);
  e.originalText = text;
  return e;
}

int main() {
  ifstream in("day_2022_13");

  std::string left;
  std::string right;

  std::vector<Element> allPackets;

  while (std::getline(in, left)) {
    std::getline(in, right);

    allPackets.push_back(parse(left));
    allPackets.push_back(parse(right));

    std::getline(in, left);
  }

  int sum   = 0;
  int index = 0;
  for (int i = 0; i < allPackets.size(); i += 2) {
    ++index;
    const auto& left  = allPackets[i];
    const auto& right = allPackets[i + 1];
    if (left < right) sum += index;
  }

  cout << "Count: " << sum << endl;

  allPackets.push_back(parse("[[2]]"));
  allPackets.push_back(parse("[[6]]"));
  std::sort(allPackets.begin(), allPackets.end());
  int prod = 1;
  for (int i = 0; i < allPackets.size(); ++i) {
    if (allPackets[i].originalText == "[[2]]" || allPackets[i].originalText == "[[6]]")
      prod *= i + 1;
  }
  cout << "Prod: " << prod << endl;

  return 1;
}
