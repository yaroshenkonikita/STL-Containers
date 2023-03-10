//
// Created by 12355 on 23.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_QUEUE_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_QUEUE_H

#include "utility"
#include <cstddef>
#include <initializer_list>
#include <iosfwd>
#include <iostream>
#include <queue>

namespace s21 {

template <typename T> class queue {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

private:
  struct node {
    value_type value;
    node *next;
    node(value_type data = value_type(), node *next = nullptr) {
      this->value = data;
      this->next = next;
    }
  };
  node *head;
  node *tail;

public:
  // queue Member functions
  queue() : head(nullptr), tail(nullptr) {}
  queue(std::initializer_list<value_type> const &items)
      : head(nullptr), tail(nullptr) {
    for (value_type element : items) {
      push(element);
    }
  }
  queue(const queue<value_type> &other) {
    head = tail = nullptr;
    node *temp = other.tail;
    queue<value_type> buf;
    while (temp != nullptr) {
      buf.push(temp->value);
      temp = temp->next;
    }
    while (!buf.empty()) {
      push(buf.top());
      buf.pop();
    }
  }
  queue(queue &&other) noexcept {
    head = std::exchange(other.head, nullptr);
    tail = std::exchange(other.tail, nullptr);
  }
  ~queue() {
    while (!empty()) {
      pop();
    }
  }

  queue &operator=(queue &&other) noexcept {
    if (this != &other) {
      while (!empty()) {
        pop();
      }
      head = std::exchange(other.head, nullptr);
      tail = std::exchange(other.tail, nullptr);
    }
    return *this;
  }

  // queue Element access
  const_reference front() {
    if (empty()) {
      throw std::length_error("queue is empty front");
    }
    return head->value;
  }

  const_reference back() {
    if (empty()) {
      throw std::length_error("queue is empty back");
    }
    return tail->value;
  }

  // queue Capacity
  bool empty() const { return head == nullptr; }
  size_type size() {
    node *new_node = head;
    size_type result = 0;
    while (!empty()) {
      head = head->next;
      result++;
    }
    head = new_node;
    new_node = nullptr;
    delete new_node;
    return result;
  }

  // queue Modifiers
  void push(const_reference value) {
    node *new_node = new node(value, tail);
    tail = new_node;
    if (!head) {
      head = new_node;
    } else if (!head->next && head) {
      head->next = new_node;
    }
  }
  void pop() {
    if (empty()) {
      throw std::length_error("queue is empty pop");
    }
    node *del_node = head;
    head = head->next;
    delete del_node;
  }
  void swap(queue &other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
  }
};
} // namespace s21

#endif // CPP2_S21_CONTAINERS_0_SRC_S21_QUEUE_H
