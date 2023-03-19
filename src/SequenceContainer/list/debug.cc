#include "s21_list.h"

int main() {
  //  std::list<std::string> basic({"hello", "world", "lets", "go!"});
  //  basic.push_back("!!!");
  std::list<std::string> basic;
  basic.push_back("hello");
  basic.push_back("world");
  basic.pop_back();

//  auto it = basic.end();
//    ++it;
//  std::cout << *it;

  for (auto elem : basic) {
    std::cout << elem;
  }

  return 0;
}