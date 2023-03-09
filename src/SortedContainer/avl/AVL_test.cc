#include "AVL.h"
#include <iostream>
#include <set>


int main() {
  std::set<int> a {1, 2, 3, 4, 1};
//    a.clear();
  auto it = a.begin(), end = a.end();
  a.clear();
  a.insert(3);
  a.insert(1);
  a.insert(-2);
//    auto it2 = a.begin();
//    it = it2;
  for (; it != end;) {
    std::cout << "value: " << *it << std::endl;
    ++it;
  }
  std::cout << "size " << *end;
  return 0;
}
