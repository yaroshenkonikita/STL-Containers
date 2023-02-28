#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H

#include <cmath>
#include <iostream>

namespace s21 {
template<typename V, class Allocator = std::allocator<V>>
class vector {
 public:
  using value_type = V;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = VectorIterator<value_type>;
  using const_iterator = ConstVectorIterator<value_type>;
  using size_type = size_t;
  using allocator_type = Allocator;
  using pointer = value_type *;

  vector() {}
  vector(size_type n) {}
  vector(std::initializer_list<value_type> const& items) {}
  vector(const vector &v) {}
  vector(vector && v) {}
  ~vector() {}
  vector &operator=(vector &&v) {}

  reference at(size_type pos) {}
  reference operator[](size_type pos) {}
  reference front() {}
  reference back() {}
  pointer data() noexcept {}

  iterator begin() noexcept {}
  iterator end() noexcept {}

  bool empty() const noexcept {}
  size_type size() const noexcept {}
  size_type max_size() const noexcept {}
  void reserve(size_type new_size) {}
  size_type capacity() const noexcept {}
  void shrink_to_fit() {}

  void clear() noexcept {}
  iterator insert(iterator iter, const_reference value) {}
  void erase(iterator pos) {}
  void push_back(const_reference value) {}
  void pop_back() {}
  void swap(vector<value_type> &other) {}

 private:
  size_type size_;
  size_type capacity_;
  pointer arr_;
  allocator_type allocator_;
};
}


#endif //CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H
