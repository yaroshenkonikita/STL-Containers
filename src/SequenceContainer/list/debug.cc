#include "s21_list.h"

int main() {
  s21::list<int> basic({1, 20, -3, 4});
  s21::list<int> basic2({12,-2,10050,40,10, 20, 30, -11});
  basic.sort();
  for (auto var : basic) {
    std::cout << var << std::endl;
  }

  std::cout << "\n" << std::endl;
  basic2.sort();
  for (auto it3 = basic2.begin(); it3 != basic2.end(); ++it3) {
    std::cout << *it3 << std::endl;
  }
  std::cout << "\n" << std::endl;
  s21::list<int>::ListConstIterator it(basic.begin());
  s21::list<int>::ListIterator it2(basic.begin());
  basic.splice(it2, basic2);
  for (auto var : basic) {
    std::cout << var << std::endl;
  }
//  for (auto it3 = basic2.begin(); it3 != basic2.end(); ++it3) {
//    std::cout << *it3 << std::endl;
//  }
  return 0;
}