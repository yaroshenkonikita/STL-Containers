#include "s21_list.h"

int main() {
  //  for (auto it3= basic.begin(); it3 != basic.end();++it3) {
  //    std::cout << *it3 << std::endl;
  //  }
  //  basic.sort();
  //  for (auto it3= basic.begin(); it3 != basic.end();++it3) {
  //    std::cout << *it3 << std::endl;
  //  }
  s21::list<int> basic({1, 2, 3, 4});
  s21::list<int> basic2({10, 20, 30});
  s21::list<int>::iterator it(basic.begin());
  it++;
  it++;
  it++;
  it++;
//  it++;
//  it++;
  basic.splice(it, basic2);
  for (auto it3 = basic.begin(); it3 != basic.end(); ++it3) {
    std::cout << *it3 << std::endl;
  }
//  for (auto it3 = basic2.begin(); it3 != basic2.end(); ++it3) {
//    std::cout << *it3 << std::endl;
//  }
  return 0;
}