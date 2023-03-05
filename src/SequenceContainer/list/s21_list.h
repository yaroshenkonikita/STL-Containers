//
// Created by 12355 on 23.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H

#include "initializer_list"
#include "iostream"
#include "limits"
#include "list"
#include "utility"

namespace s21 {

template <typename T> class list {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  //    using iterator = ListIterator<T>;
  //    using const_iterator = ListConstIterator<T>;

public:
  /*__________________________________________________________________*/
  /* CONSTRUCTORS AND DESTRUCTOR */
  /*__________________________________________________________________*/
  list();
  explicit list(size_type size); // explicit ???
  list(std::initializer_list<value_type> const &items);
  list(const list<value_type> &other);
  list(list<value_type> &&other) noexcept;
  ~list();

  list<value_type> &operator=(list<value_type> &&other) noexcept;
  /*__________________________________________________________________*/

  //  iterator insert(iterator pos, const_reference value)
  void insert(value_type data, int index);
  void node_delete(int index);
  void push_back(const_reference data);
  void push_front(const_reference data);
  void pop_front();
  void pop_back();
  const_reference front() {
    length_error();
    return head->data;
  }
  const_reference back() {
    length_error();
    return tail->data;
  }
  size_type size() { return size_list; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }
  bool empty() { return size_list == 0; }
  void clear();
  void swap(list &other);

private:
  class node {
  public:
    node *next;
    node *prev;
    value_type data;

    explicit node(value_type data = value_type(), node *next = nullptr,
                  node *prev = nullptr) { // explicit ???
      this->data = data;
      this->next = next;
      this->prev = prev;
    }
  };
  node *head;
  node *tail;
  size_type size_list;

  class ListIterator {
    node *current{};
    ListIterator &operator++() {
      current = current->next;
      return this;
    }
    ListIterator &operator--() {
      current = current->prev;
      return this;
    }
    value_type &operator*() { return current->data; }

    explicit ListIterator(node *other) { current = other; }
  };

  void length_error() {
    if (head == nullptr) {
      throw std::length_error("list is empty");
    }
  }
};
template <typename value_type> void list<value_type>::node_delete(int index) {}
template <typename value_type>
void list<value_type>::insert(value_type data, int index) {
  if (!index) {
    push_front(data);
  } else if (index == size_list - 1) {
    push_back(data);
  } else {
    node *previous = head;
    for (int i = 0; i < index - 1; i++) {
      previous = previous->next;
    }
    node *new_node = new node(data, previous->next);
    previous->next = new_node;
    size_list++;
  }
}

template <typename value_type>
list<value_type> &
list<value_type>::operator=(list<value_type> &&other) noexcept {
  if (this != &other) {
    clear();
    size_list = std::exchange(other.size_list, 0);
    head = std::exchange(other.head, nullptr);
    tail = std::exchange(other.tail, nullptr);
  }
  return *this;
}
template <typename T> list<T>::list(const list<value_type> &other) {
  size_list = 0;
  head = tail = nullptr;
  node *current_other = other.head;
  while (current_other != nullptr) {
    push_back(current_other->data);
    current_other = current_other->next;
  }
}

template <typename T> void list<T>::swap(list &other) {
  node *current = head;
  node *current_other = other.head;
  while (current != nullptr && current_other != nullptr) {
    std::swap(current->data, current_other->data);
    current = current->next;
    current_other = current_other->next;
  }
  //  if(size() == other.size()) {
  //    while (current != nullptr) {
  //      std::swap(current->data, current_other->data);
  //      current = current->next;
  //      current_other = current_other->next;
  //    }
  //  } else if(size() < other.size()) {
  //    while (current_other != nullptr) {
  //      if(current == nullptr) {
  //        push_back(current_other->data);
  //        current = current->next;
  //        node *previus = current_other;
  //        current_other = current_other->next;
  //        delete previus;
  //      } else {
  //        std::swap(current->data, current_other->data);
  //        current = current->next;
  //        current_other = current_other->next;
  //      }
  //    }
  //  } else {
  //    while (current != nullptr) {
  //      if (current_other == nullptr) {
  //        other.push_back(current->data);
  //        current_other = current_other->next;
  //        node *previus = current;
  //        current = current->next;
  //        delete previus;
  //      } else {
  //        std::swap(current->data, current_other->data);
  //        current = current->next;
  //        current_other = current_other->next;
  //      }
  //    }
  //  }
}

template <typename T> void list<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <typename value_type>
void list<value_type>::push_front(const_reference data) {
  node *current = new node(data);
  current->next = head;
  current->prev = nullptr;
  if (head != nullptr) {
    head->prev = current;
  }
  if (tail == nullptr) {
    tail = current;
  }
  head = current;
  size_list++;
}

template <typename value_type>
void list<value_type>::push_back(const_reference data) {
  node *current = new node(data);
  if (tail != nullptr) {
    tail->next = current;
  }
  current->next = nullptr;
  current->prev = tail;
  if (head == nullptr) {
    head = current;
  }
  tail = current;
  size_list++;
}

template <typename value_type> list<value_type>::list() {
  size_list = 0;
  head = tail = nullptr;
}

template <typename value_type> list<value_type>::list(size_type size) {
  head = tail = nullptr;
  size_list = 0;
  for (size_type i = 0; i < size; i++) {
    push_front(value_type());
  }
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) {
  head = tail = nullptr;
  size_list = 0;
  for (value_type element : items) {
    push_back(element);
  }
}

template <typename value_type>
list<value_type>::list(list<value_type> &&other) noexcept {
  size_list = std::exchange(other.size_list, 0);
  head = std::exchange(other.head, nullptr);
  tail = std::exchange(other.tail, nullptr);
}

template <typename value_type> list<value_type>::~list() { clear(); }

template <typename value_type> void list<value_type>::pop_front() {
  length_error();
  node *current = head;
  head = head->next;
  delete current;
  size_list--;
}

template <typename value_type> void list<value_type>::pop_back() {
  length_error();
  node *current = tail;
  tail = tail->prev;
  delete current;
  size_list--;
}
} // namespace s21
#endif // CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
