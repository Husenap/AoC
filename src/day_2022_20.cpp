#include "common.hpp"

struct Node {
  i64   x;
  Node *prev, *next;
};

using Number = i64;

static constexpr Number DecryptionKey = 811589153;

int main() {
  std::ifstream in("day_2022_20");

  std::vector<Node*> xs;
  Number             x;
  while (in >> x) {
    Node* node = new Node;
    node->x    = x * DecryptionKey;
    if (!xs.empty()) {
      xs.back()->next = node;
      node->prev      = xs.back();
    }
    xs.push_back(node);
  }
  xs.back()->next  = xs.front();
  xs.front()->prev = xs.back();

  for (int i = 0; i < 10; ++i) {
    for (auto x : xs) {
      auto offset = x->x;

      const auto b = static_cast<Number>(xs.size()) - 1;

      offset -= (offset / b) * b;

      while (offset < 0) {
        ++offset;

        auto left  = x->prev;
        auto left2 = left->prev;
        auto right = x->next;

        x->prev     = left2;
        left2->next = x;
        x->next     = left;
        left->prev  = x;
        right->prev = left;
        left->next  = right;
      }

      while (offset > 0) {
        --offset;

        auto left   = x->prev;
        auto right  = x->next;
        auto right2 = right->next;

        x->next      = right2;
        right2->prev = x;
        x->prev      = right;
        right->next  = x;
        left->next   = right;
        right->prev  = left;
      }
    }
  }

  Number coords = 0;

  auto cur = xs.front();
  while (cur->x != 0) cur = cur->next;
  for (int i = 1; i <= 3000; ++i) {
    cur = cur->next;
    if (i % 1000 == 0) {
      coords += cur->x;
    }
  }

  expectEq(coords, 912226207972ll);

  return 0;
}
