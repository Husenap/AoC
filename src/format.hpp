#pragma once

#include <array>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace shared {

template <typename... Args>
inline void format_to(std::ostream& out, std::string_view format_string, Args&&... args);

template <typename... Args>
inline auto format(std::string_view format_string, Args&&... args);

}  // namespace shared

namespace {
template <typename T>
inline std::ostream& format_array_to(std::ostream& out, T* begin, T* end);
}  // namespace

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
  if (v.empty()) {
    return out << "[]";
  }
  return format_array_to(out, v.data(), v.data() + v.size());
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const std::array<T, N>& v) {
  return format_array_to(out, v.data(), v.data() + N);
}

template <typename T, size_t N, typename = std::enable_if_t<!std::is_same<T, char>::value>>
std::ostream& operator<<(std::ostream& out, const T (&a)[N]) {
  return format_array_to(out, a, a + N);
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& p) {
  shared::format_to(out, "({},{})", p.first, p.second);
  return out;
}

template <typename... Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t) {
  out << '(';
  bool isFirst = true;
  std::apply(
      [&out, &isFirst](auto&... x) {
        (..., (shared::format_to(out, "{}{}", isFirst ? "" : ",", x), isFirst = false));
      },
      t);
  out << ')';
  return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& v) {
  if (v.empty()) {
    return out << "{}";
  }
  out << '{';
  bool isFirst = true;
  for (const auto& i : v) {
    if (!isFirst) out << ", ";
    isFirst = false;
    out << i;
  }
  out << '}';
  return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::optional<T>& p) {
  if (p) {
    out << *p;
  } else {
    out << "{nullopt}";
  }
  return out;
}

namespace shared {

template <typename... Args>
inline void format_to(std::ostream& out, std::string_view format_string, Args&&... args) {
  ((out << format_string.substr(0, format_string.find("{}")),
    format_string.remove_prefix(format_string.find("{}") + 2),
    out << args),
   ...);
  out << format_string;
}

template <typename... Args>
inline auto format(std::string_view format_string, Args&&... args) {
  std::ostringstream output;
  format_to(output, format_string, std::forward<Args>(args)...);
  return output.str();
}

}  // namespace shared

namespace {
template <typename T>
inline std::ostream& format_array_to(std::ostream& out, T* begin, T* end) {
  out << "[";
  out << *begin++;
  while (begin < end) {
    out << ", " << *begin++;
  }
  out << "]";
  return out;
}
}  // namespace
