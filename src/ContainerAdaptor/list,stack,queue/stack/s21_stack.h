#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_QUEUE_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_QUEUE_H

#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class stack : protected s21::list<T> {
 private:
  using list = s21::list<T>;
  // Queue Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  // Queue Member functions
  using list::list;
  // Queue Element access
  const_reference top() { return list::back(); };

  // Queue Capacity
  using list::empty;
  using list::size;
  // Queue Modifiers
  void push(const_reference value) { list::push_back(value); };
  void pop() { list::pop_back(); };
  void swap(stack &other) { list::swap(other); };
  template <typename... Args>
  void emplace_front(Args &&...args) {
    for (auto element : {std::forward<Args>(args)...}) {
      push(element);
    }
  };
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_S21_QUEUE_H
