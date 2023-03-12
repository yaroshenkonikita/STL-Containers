#include "s21_list.h"

int main() {
//  for (auto it3= basic.begin(); it3 != basic.end();++it3) {
//    std::cout << *it3 << std::endl;
//  }
//  basic.sort();
//  for (auto it3= basic.begin(); it3 != basic.end();++it3) {
//    std::cout << *it3 << std::endl;
//  }
  std::list<int> basic({-100,12321,123,-5124,13,0,-111,17,5125,41349394,-31423434,2});
  std::list<int> basic2({-100,12321,123,-5124,13,0,-111,17,5125,41349394,-31423434,2});
  basic.splice(basic.begin(),basic2);
  for (auto it3= basic.begin(); it3 != basic.end();++it3) {
    std::cout << *it3 << std::endl;
  }
  std::cout << "\n\n" << std::endl;
  for (auto it3= basic2.begin(); it3 != basic2.end();++it3) {
    std::cout << *it3 << std::endl;
  }
  return 0;
}