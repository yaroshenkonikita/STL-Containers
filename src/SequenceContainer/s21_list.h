#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H

#include <cmath>
#include <list>
#include <iostream>

template <typename L>
class List {
 public:
  using value_type = L;
  using reference = L;
  using const_reference = L;
  using iterator = L;
  using const_iterator = L;
  using size_type = L;

  List() {

  }
  List(size_type n) {

  }
  List(std::initializer_list<value_type> const& items) {

  }
  List(const List& l) {

  }
  List(List&& l) {

  }
  ~List() {

  }

  List& operator=(List &&l) {
    
  }

  void push_front(L value_type) {

  }
  
  void pop_front() {
    
  }
  
  void reverse() {
    
  }

 private:
  value_type value;
  List* next;
  List* prev;
  };

#endif //CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
