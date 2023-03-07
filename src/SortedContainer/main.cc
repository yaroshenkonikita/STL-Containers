//
// Created by 12355 on 05.03.2023.
//

#include <set>
#include "BinaryTree.h"

int main() {

    s21::BinaryTree<int> a {1, 2, 3, 4};
    auto it = a.begin(), end = a.end();
    for (; it != end;) {
        std::cout << *it << std::endl;
        ++it;
    }
    return 0;
}
