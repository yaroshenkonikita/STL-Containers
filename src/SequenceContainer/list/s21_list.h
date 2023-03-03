//
// Created by 12355 on 23.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H

#include "initializer_list"
#include "iostream"
#include "list"
#include "utility"

template <typename T> class list {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  //  using iterator = ListIterator<T>;
  //  using const_iterator = ListConstIterator<T>;

public:
  /*__________________________________________________________________*/
  /* CONSTRUCTORS AND DESTRUCTOR */
  /*__________________________________________________________________*/
  list();
  explicit list(size_type size); // explicit ???
  list(std::initializer_list<value_type> const &items);
  //  list(const list<value_type> &other);
  list(list<value_type> &&other) noexcept;
  ~list();
  /*__________________________________________________________________*/
  void push_back(const_reference data);
  void push_front(const_reference data);
  void pop_front();
  void pop_back();
  int getSize() { return size_list; }
  const_reference front() {
    length_error();
    return head->data;
  }
  const_reference back() {
    length_error();
    return tail->data;
  }
  size_type size() { return (size_type)size_list; }
  bool empty() { return size_list == 0; }

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

  void length_error() {
    if (head == nullptr) {
      throw std::length_error("list is empty");
    }
  }
};

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
    push_front(element);
  }
}

template <typename value_type>
list<value_type>::list(list<value_type> &&other) noexcept {
  size_list = std::exchange(other.size_list, 0);
  head = std::exchange(other.head, nullptr);
  tail = std::exchange(other.tail, nullptr);
}

// template <typename value_type>
// list<value_type>::list(const list<value_type> &other) {
//   head = tail = nullptr;
//   size_list = 0;
//   for (size_type i = 0; i < other.size; i++) {
//     push_front(value_type());
//   }
//
// }

template <typename value_type> list<value_type>::~list() {
  while (!empty()) {
    pop_front();
  }
}

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

#endif // CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
