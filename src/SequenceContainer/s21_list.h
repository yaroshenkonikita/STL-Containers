//
// Created by 12355 on 23.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H

#include "iostream"
#include "list"

template <typename T> class list {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  //  using iterator = ListIterator<T>;
  //  using const_iterator = ListConstIterator<T>;

public:
  list();
  ~list();
  void push_back(const_reference data);
  void push_front(const_reference data);
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
  bool empty() { return size_list == 0;}

private: // switch private!
  class node {
  public:
    node *next;
    node *prev;
    T data;

    explicit node(T data = T(), node *next = nullptr, node *prev = nullptr) {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }
  };
  node *head;
  node *tail;
  int size_list;

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
  head = current;
  size_list++;
  if (tail == nullptr) {
    tail = current;
  }
}

template <typename value_type>
void list<value_type>::push_back(const_reference data) {
  node *current = new node(data);
  if (head == nullptr) {
    head = current;
  }
  if (tail != nullptr) {
    tail->next = current;
  }
  current->next = nullptr;
  current->prev = tail;
  tail = current;
  size_list++;
}

template <typename value_type> list<value_type>::list() {
  size_list = 0;
  head = nullptr;
  tail = nullptr;
}

template <typename value_type> list<value_type>::~list() {
  node *current = head;
  while (current != nullptr) {
    node *previous = current;
    current = current->next;
    delete previous;
  }
  head = tail = nullptr;
  size_list = 0;
}
#endif // CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
