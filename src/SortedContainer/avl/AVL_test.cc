#include "AVL.h"
#include <iostream>

// указатели целочисленных узлов дерева
s21::TreeNode<int> *root, *lchild, *rchild;
s21::TreeNode<int> *p;

int main() {
// создать листья, содержащие
// 20 и 30 в качестве данных
  lchild = new s21::TreeNode<int>(20, 0, 0);
  rchild = new s21::TreeNode<int>(30, 0, 0);
// создать корень, содержащий число
// 10 и двух сыновей
  root = new s21::TreeNode<int>(10, lchild, rchild);
  root->data = 50; // присвоить корню 50
}
