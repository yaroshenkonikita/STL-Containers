#include "s21_list.h"

int main() {
  s21::list<int>basic({1,2,3,4,5,6,7});
  std::list<std::string>stl({"hello", "213", "hello, world", "2123", "12323", "1","3"});
  std::list<std::string>stl2({"1", "2"});
  auto it_stl = stl.begin();
//  it_stl++;
//  it_stl++;
//  stl.sort();
//  for (auto it3= stl.begin(); it3 != stl.end();++it3) {
//    std::cout << *it3 << std::endl;
//  }
  stl.splice(it_stl, stl2);
  for (auto it3= stl.begin(); it3 != stl.end();++it3) {
    std::cout << *it3 << std::endl;
  }
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