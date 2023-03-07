#include "s21_list.h"

int main() {
  s21::list<int>basic({1,2,3,4,5,6,7});
//  basic.push_back(1);
//  basic.push_front(1);
  s21::list<int>::ListIterator it(basic.begin());
//  ++it;
//  ++it;
//  ++it;
//  ++it;
//  ++it;
//  ++it;
//  ++it;
  s21::list<int>::ListIterator result = basic.insert_iter(it,100);
  for (s21::list<int>::ListIterator it2(basic.begin()); it2 != basic.end();++it2) {
    std::cout << *it2 << std::endl;
  }
  std::cout << *result << std::endl;
  std::cout << basic.size() << std::endl;
  return 0;
}