#include "s21_list.h"

int main() {
  s21::list<int>basic({2,3,1,0,12,3});
  for (auto it3= basic.begin(); it3 != basic.end();++it3) {
    std::cout << *it3 << std::endl;
  }
  basic.reverse();
  for (auto it3= basic.begin(); it3 != basic.end();++it3) {
    std::cout << *it3 << std::endl;
  }
//  std::list<int>basic2({1,2,3,4,5,6,7,100,123});
//    basic2.reverse();
//  for (auto it3= basic2.end(); it3 != basic2.begin();--it3) {
//    std::cout << *it3 << std::endl;
//  }
//  basic.reverse();
//  for (auto it3= basic.begin(); it3 != basic.end();++it3) {
//    std::cout << *it3 << std::endl;
//  }
//  auto it3= basic.end();
//  --it3;
//  for (; it3 != basic.begin();--it3) {
//    std::cout << *it3 << std::endl;
//  }
  return 0;
}