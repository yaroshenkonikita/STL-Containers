#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

template <class T>
class List {
 public:
  using value_type = T;

 private:
  value_type value;
  List* next_;
  List* prev_;
  }; 

#endif //CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
