//
// Created by 12355 on 23.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H

#include "iostream"
#include "list"

template <typename T> class list {
public:
  list();
  ~list();
  void push_back(const T &);

public: // switch private!
  class node {
  public:
    node *next;
    node *prev;
    T data;

    node(T data = T(), node *next = nullptr, node *prev = nullptr) {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }
  };
  node *head;
  node *tail;
  int size;
};

template <typename T> void list<T>::push_back(const T &data) {
  node *current = new node(data);
  if (tail == nullptr && head == nullptr) {
    tail = current;
    head = tail;
  }
  if (tail != nullptr) {
    tail->next = current;
  }
  current->next = nullptr;
  current->prev = tail;
  tail = current;
  size++;
}

template <typename T> list<T>::list() {
  size = 0;
  head = nullptr;
  tail = nullptr;
}

template <typename T> list<T>::~list() = default;
#endif // CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
