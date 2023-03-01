//
// Created by 12355 on 23.02.2023. Code designed by Polliver
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-declarations"
#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_STACK_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_STACK_H

#include "utility"
#include <cstddef>
#include <initializer_list>
#include <iosfwd>
#include <iostream>
#include <stack>

template <typename T> class Stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

private:
  struct node {
    value_type value;
    node *next;
  };
  node *upper_element;

public:
  // Stack Member functions
  Stack() : upper_element(nullptr) {
    std::cout << "Вызвался конструктор" << this;
  }

  Stack(std::initializer_list<value_type> const &items) {
    upper_element = nullptr;
    for (value_type element : items) {
      push(element);
    }
  }
  Stack(const Stack<value_type> &other) {
    //    size_type
    node *new_node = other.upper_element;
    std::initializer_list<value_type> list;
    while (!other.empty()) {
      list.append({other.upper_element->value});
      other.upper_element = other.upper_element->next;
    }
    other.upper_element = new_node;
    new_node = nullptr;
    delete[] new_node;
    Stack({list});
  }

  Stack(Stack &&other) noexcept {
    upper_element = other.upper_element;
    other.upper_element = nullptr;
  }

  ~Stack() {
    std::cout << "Вызвался деструктор" << this;
    while (!empty())
      pop();
  }
  Stack &operator=(Stack &&other) noexcept {
    if (this != &other) {
      ~Stack();
      upper_element = other.upper_element;
      other.upper_element = nullptr;
    }
    return *this;
  }

  // Stack Element access
  const_reference top() {
    if (empty()) {
      throw std::length_error("stack is empty");
    }
    return upper_element->value;
  }

  // Stack Capacity
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

  // Stack Modifiers
  void push(const_reference value) {
    node *new_node = new node;
    new_node->value = value;
    new_node->next = upper_element;
    upper_element = new_node;
  }

  void pop() {
    if (empty()) {
      throw std::length_error("stack is empty");
    }
    node *del_node = upper_element;
    upper_element = upper_element->next;
    delete[] del_node;
  }
  //  void swap(Stack &other);
};

#endif // CPP2_S21_CONTAINERS_0_SRC_S21_STACK_H

#pragma clang diagnostic pop