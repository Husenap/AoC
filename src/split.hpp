#pragma once

#include <algorithm>
#include <iterator>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace shared {

inline std::vector<std::string> split(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string              token;
  std::istringstream       tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

template <typename TransformFunc>
inline auto split(const std::string& s, char delimiter, TransformFunc transform) {
  const auto                          splits = split(s, delimiter);
  std::vector<decltype(transform(s))> tokens;
  for (const auto& token : splits) {
    tokens.push_back(transform(token));
  }
  return tokens;
}

template <typename TransformFunc>
inline auto safe_split(const std::string& s, char delimiter, TransformFunc transform) {
  const auto                                         splits = split(s, delimiter);
  std::vector<std::optional<decltype(transform(s))>> tokens;
  for (const auto& token : splits) {
    try {
      tokens.push_back(transform(token));
    } catch (...) {
      tokens.push_back(std::nullopt);
    }
  }
  return tokens;
}

inline auto split_regex(const std::string& s, std::string_view expr) {
  std::regex               r(expr.data());
  std::vector<std::string> result;
  std::copy(std::sregex_token_iterator(s.begin(), s.end(), r, -1),
            std::sregex_token_iterator(),
            std::back_inserter(result));
  return result;
}

}  // namespace shared