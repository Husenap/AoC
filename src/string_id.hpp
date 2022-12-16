#pragma once

#include <string>
#include <unordered_map>

namespace shared {
class string_id {
public:
  std::size_t get(const std::string& name) {
    auto it = name_to_id.find(name);
    if (it == name_to_id.end()) {
      it = name_to_id.emplace(name, id++).first;
    }
    return it->second;
  }
  std::size_t operator()(const std::string& name) { return get(name); }

private:
  std::size_t                                  id         = {};
  std::unordered_map<std::string, std::size_t> name_to_id = {};
};
}  // namespace shared