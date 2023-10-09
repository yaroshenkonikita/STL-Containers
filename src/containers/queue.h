#ifndef STL_CONTAINERS_QUEUE_H_
#define STL_CONTAINERS_QUEUE_H_ 1

#include "containers/list.h"

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

#endif  // STL_CONTAINERS_QUEUE_H_
