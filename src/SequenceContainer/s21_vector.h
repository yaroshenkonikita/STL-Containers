#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H


#include <cmath>
#include <list>
#include <iostream>
namespace s21 {
  template<typename V>
  class vector {
   public:
    using value_type = V;
    using reference = V;
    using const_reference = V;
    using iterator = V;
    using const_iterator = V;
    using size_type = V;
  
    vector() {

    }

    vector(size_type n) {

    }

    vector(std::initializer_list<value_type> const& items) {}

    vector(const vector &v) {}

    vector(vector && v) {}

    ~vector() {}

    vector &operator=(vector &&v) {}

    void push_front(V value_type) {}

    void pop_front() {}

    void reverse() {}

   private:
    value_type value;
    vector *next;
    vector *prev;
  };
}


#endif //CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H
