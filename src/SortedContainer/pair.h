#ifndef STL_CONTAINERS_PAIR_H_
#define STL_CONTAINERS_PAIR_H_

#include <algorithm>
#include <utility>

namespace s21 {

template <class T1, class T2>
class pair {
 public:
  pair() = default;

  pair(T1 _first, T2 _second) : first(_first), second(_second) {}

  pair(pair &other) : first(other.first), second(other.second) {}

  pair(pair &&other) noexcept {
    first = std::exchange(other.first, T1());
    second = std::exchange(other.second, T2());
  }

  pair &operator=(pair other) {
    first = std::copy(other.first);
    second = std::copy(other.second);
  }

  pair &operator=(const pair &other) {
    first = std::copy(other.first);
    second = std::copy(other.second);
  }

  pair &operator=(pair &&other) noexcept {
    first = std::move(other.first);
    second = std::move(other.second);
  }

  ~pair() = default;

  T1 first{};
  T2 second{};
};

}  // namespace s21

#endif  // STL_CONTAINERS_PAIR_H_
