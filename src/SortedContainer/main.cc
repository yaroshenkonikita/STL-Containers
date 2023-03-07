//
// Created by 12355 on 05.03.2023.
//

#include "BinaryTree.h"

int main() {
    s21::BinaryTree<int> asd{1, 2, 3, 4};
    auto it = asd.begin();
    while ( it != asd.end()) {
        std::cout << *it++ << std::endl;
    }
    return 0;
}
