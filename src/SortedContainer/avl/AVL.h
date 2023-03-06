#include "iostream"

template<typename T>
class Vector {
 public:
  // структура для представления узлов дерева
  struct node {
    int key;
    unsigned char height;
    node *left;
    node *right;
    node(int k) {
      key = k;
      left = right = 0;
      height = 1;
    }
  };
  // работа с полем height
  unsigned char height(node *pointer) { return pointer ? pointer->height : 0; }
  // вычисляет balance factor заданного узла
  int bFactor(node *pointer) { return height(pointer->right) - height(pointer->left); }
  // устанавливает корректное значение поля height
  void fixHeight(node *pointer) {
    unsigned char heightLeft = height(pointer->left);
    unsigned char heightRight = height(pointer->right);
    pointer->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
  }
  // правый поворот вокруг pointer
  node *rotateRight(node *pointer) {
    node *q = pointer->left;
    pointer->left = q->right;
    q->right = pointer;
    fixHeight(pointer);
    fixHeight(q);
    return q;
  }
  // левый поворот вокруг q
  node *rotateLeft(node *q) {
    node *pointer = q->right;
    q->right = pointer->left;
    pointer->left = q;
    fixHeight(q);
    fixHeight(pointer);
    return pointer;
  }
  // балансировка узла pointer
  node *balance(node *pointer) {
    fixHeight(pointer);
    if (bFactor(pointer) == 2) {
      if (bFactor(pointer->right) < 0)
        pointer->right = rotateRight(pointer->right);
      return rotateLeft(pointer);
    }
    if (bFactor(pointer) == -2) {
      if (bFactor(pointer->left) > 0)
        pointer->left = rotateLeft(pointer->left);
      return rotateRight(pointer);
    }
    return pointer; // балансировка не нужна
  }
  // вставка ключа k в дерево с корнем pointer
  node *insert(node *pointer, int k) {
    if (!pointer) return new node(k);
    if (k < pointer->key)
      pointer->left = insert(pointer->left, k);
    else
      pointer->right = insert(pointer->right, k);
    return balance(pointer);
  }
  // поиск узла с минимальным ключом в дереве pointer
  node *findMin(node *pointer) {
    return pointer->left ? findMin(pointer->left) : pointer;
  }
  // удаление узла с минимальным ключом из дерева pointer
  node *removeMin(node *pointer) {
    if (pointer->left == 0)
      return pointer->right;
    pointer->left = removeMin(pointer->left);
    return balance(pointer);
  }
  // удаление ключа k из дерева pointer
  node *remove(node *pointer, int k) {
    if (!pointer) return 0;
    if (k < pointer->key) pointer->left = remove(pointer->left, k);
    else if (k > pointer->key) pointer->right = remove(pointer->right, k);
    else { //  k == pointer->key
      node *q = pointer->left;
      node *r = pointer->right;
      delete pointer;
      if (!r) return q;
      node *min = findMin(r);
      min->right = removeMin(r);
      min->left = q;
      return balance(min);
    }
    return balance(pointer);
  }
};