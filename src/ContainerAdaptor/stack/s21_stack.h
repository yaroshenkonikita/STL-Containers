//
// Created by 12355 on 23.02.2023. Code designed by Polliver
//
#include "utility"
#include <cstddef>
#include <initializer_list>
#include <iosfwd>
#include <iostream>
#include <stack>

#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_stack_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_stack_H
namespace s21 {

template <typename T> class stack {
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
  node *upper_element;

public:
  // stack Member functions
  stack() : upper_element(nullptr) {}
  stack(std::initializer_list<value_type> const &items) {
    upper_element = nullptr;
    for (value_type element : items) {
      push(element);
    }
  }
  stack(const stack<value_type> &other) {
    upper_element = nullptr;
    node *temp = other.upper_element;
    stack<value_type> buf;
    while (temp != nullptr) {
      buf.push(temp->value);
      temp = temp->next;
    }
    while (!buf.empty()) {
      push(buf.top());
      buf.pop();
    }
  }
  stack(stack &&other) noexcept {
    upper_element = other.upper_element;
    other.upper_element = nullptr;
  }
  ~stack() {
    while (!empty()) {
      pop();
    }
  }

  stack &operator=(stack &&other) noexcept {
    if (this != &other) {
      while (!empty()) {
        pop();
      }
      upper_element = other.upper_element;
      other.upper_element = nullptr;
    }
    return *this;
  }

  // stack Element access
  const_reference top() {
    if (empty()) {
      throw std::length_error("stack is empty");
    }
    return upper_element->value;
  }

  // stack Capacity
  bool empty() const { return upper_element == nullptr; }
  size_type size() {
    node *new_node = upper_element;
    size_type result = 0;
    while (!empty()) {
      upper_element = upper_element->next;
      result++;
    }
    upper_element = new_node;
    new_node = nullptr;
    delete[] new_node;
    return result;
  }

  // stack Modifiers
  void push(const_reference value) {
    node *new_node = new node(value, upper_element);
    upper_element = new_node;
  }
  void pop() {
    if (empty()) {
      throw std::length_error("stack is empty");
    }
    node *del_node = upper_element;
    upper_element = upper_element->next;
    delete del_node;
  }
  void swap(stack &other) { std::swap(upper_element, other.upper_element); }
};
} // namespace s21
#endif // CPP2_S21_CONTAINERS_0_SRC_S21_stack_H