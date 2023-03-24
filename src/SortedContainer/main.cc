#include <iostream>

#include "BinaryTree.h"

int main() {
  s21::BinaryTree<int> a;
  a.insert(4);
  a.insert(6);
  a.insert(1);
  a.insert(0);
  a.insert(2);
  a.insert(3);
  a.insert(2);
  a.insert(2);
  a.insert(0);
  a.insert(0);
  a.insert(3);
  a.insert(3);
  auto it = a.begin(), end = a.end();
  auto b = a.equal_range(2);
  auto n = a.begin();
  while (n != end) {
    std::cout << "erase: " << *n << std::endl;
    a.erase(n++);
  }
  std::cout << "size: " << a.size() << std::endl;
  return 0;
}
