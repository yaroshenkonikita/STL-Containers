#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_0_SRC_S21_QUEUE_H_

#include "s21_list.h"

namespace s21 {

template <typename T>
class queue : protected s21::list<T> {
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
  using list::back;
  using list::front;

  // Queue Capacity
  using list::empty;
  using list::size;
  // Queue Modifiers
  void push(const_reference value) { list::push_back(value); };
  void pop() { list::pop_front(); };
  void swap(queue &other) { list::swap(other); };
  template <typename... Args>
  void emplace_front(Args &&...args) {
    for (auto element : {std::forward<Args>(args)...}) {
      push(element);
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_S21_QUEUE_H_
