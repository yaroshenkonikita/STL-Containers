#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H

#include <cmath>
#include <iostream>

namespace s21 {
template<typename V, class Allocator = std::allocator<V>>
class vector {
 public:
//  ------------------------------Member type------------------------------
  using value_type = V;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = VectorIterator<value_type>;
  using const_iterator = ConstVectorIterator<value_type>;
  using size_type = size_t;
  using allocator_type = Allocator;
  using pointer = value_type *;
//  ------------------------------Functions------------------------------
  vector() {}
  vector(size_type n) {}
  vector(std::initializer_list<value_type> const &items) {}
  vector(const vector &v) {}
  vector(vector &&v) {}
  ~vector() {}
  vector &operator=(vector &&v) {}
//  ------------------------------Element access------------------------------
//  Возвращает ссылку на элемент в указанном месте pos с проверкой границ
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Out of range");
    }
    return arr_[pos];
  }
//  Возвращает ссылку на элемент в указанном месте
  reference operator[](size_type pos) { return arr_[pos]; }
//  Возвращает ссылку на первый элемент в контейнере
  reference front() { return arr_[0]; }
//  Возвращает ссылку на последний элемент в контейнере
  reference back() { return arr_[size_ - 1]; }
//  Возвращает указатель на базовый массив
  pointer data() noexcept { return arr_; }
//  ------------------------------Iterators------------------------------
  iterator begin() noexcept {}
  iterator end() noexcept {}
//  ------------------------------Capacity------------------------------
//  Проверяет, нет ли в контейнере элементов
  bool empty() const noexcept { return size_ == 0; }
//  Возвращает количество элементов в контейнере
  size_type size() const noexcept { return size_; }
//  Возвращает максимальное количество элементов, которые может содержать контейнер
  size_type max_size() const noexcept { return allocator_.max_size(); }
//  Увеличиваем емкость вектора до значения, которое больше или равно size
  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error("Out of memory");
    }
    V *buff = allocator_.allocate(size);
    for (size_type i = 0; i < size_; ++i) {
      buff[i] = arr_[i];
    }
    delete[] arr_;
    arr_ = buff;
    capacity_ = buff->capacity_;
    buff = nullptr;
  }
//  Возвращает количество элементов, для которых в данный момент выделено место в контейнере
  size_type capacity() const noexcept { return capacity_; }
//  Запрашивает удаление неиспользуемой емкости
  void shrink_to_fit() { if (size_ != capacity_) reserve(size_); }
//  ------------------------------Modifiers------------------------------
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
