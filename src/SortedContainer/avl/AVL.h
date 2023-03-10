#include "iostream"

namespace s21 {
template<typename Key>
class AVL {
 public:
  using size_type = std::size_t;
  using key_type = Key;
  using reference = key_type&;
  using const_reference = const key_type&;
 protected:
  class Node {
   public:
    Node() = default;
    explicit Node(key_type key) : key_(key) {}
    Node(key_type value, Node *node) : key_(value), _parent(node) {}
    ~Node() { delete _left; delete _right; }
    key_type key_{};
    Node* _left{}, _right{}, _parent{};
  };

 public:
  using node_type = Node;
  using pointer = node_type*;

  AVL() : root(new Node()) {}

  AVL(std::initializer_list<key_type> const &items) {
    root = new Node();
    for (key_type item : items) {
      insert(item);
    }
  }

  // работа с полем height
  unsigned char upper(Node *pointer) { return pointer ? pointer->height : 0; }

  // вычисляет разницу высот правого и левого поддеревьев
  int heightDifference(Node *pointer) { return upper(pointer->right) - upper(pointer->left); }

  // устанавливает корректное значение поля height
  void fixHeight(Node *pointer) {
    unsigned char heightLeft = upper(pointer->left);
    unsigned char heightRight = upper(pointer->right);
    pointer->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
  }

  // правый поворот вокруг pointer
  Node *rotateRight(Node *pointer) {
    Node * q = pointer->left;
    pointer->left = q->right;
    q->right = pointer;
    fixHeight(pointer);
    fixHeight(q);
    return q;
  }

  // левый поворот вокруг q
  Node *rotateLeft(Node *q) {
    Node * pointer = q->right;
    q->right = pointer->left;
    pointer->left = q;
    fixHeight(q);
    fixHeight(pointer);
    return pointer;
  }

  // балансировка узла pointer
  Node *balance(Node *pointer) {
    fixHeight(pointer);
    if (heightDifference(pointer) == 2) {
      if (heightDifference(pointer->right) < 0)
        pointer->right = rotateRight(pointer->right);
      return rotateLeft(pointer);
    }
    if (heightDifference(pointer) == -2) {
      if (heightDifference(pointer->left) > 0)
        pointer->left = rotateLeft(pointer->left);
      return rotateRight(pointer);
    }
    return pointer; // балансировка не нужна
  }

  // вставка ключа k в дерево с корнем pointer
  Node *insert(Node *pointer, int k) {
    if (!pointer) return new Node(k);
    if (k < pointer->key) pointer->left = insert(pointer->left, k);
    else pointer->right = insert(pointer->right, k);
    return balance(pointer);
  }

  // поиск узла с минимальным ключом в дереве pointer
  Node *findMin(Node *pointer) {
    return pointer->left ? findMin(pointer->left) : pointer;
  }

  // удаление узла с минимальным ключом из дерева pointer
  Node *removeMin(Node *pointer) {
    if (pointer->left == 0)
      return pointer->right;
    pointer->left = removeMin(pointer->left);
    return balance(pointer);
  }

  // удаление ключа k из дерева pointer
  Node *remove(Node *pointer, int k) {
    if (!pointer) return 0;
    if (k < pointer->key) pointer->left = remove(pointer->left, k);
    else if (k > pointer->key) pointer->right = remove(pointer->right, k);
    else { //  k == pointer->key
      Node * q = pointer->left;
      Node * r = pointer->right;
      delete pointer;
      if (!r) return q;
      Node * min = findMin(r);
      min->right = removeMin(r);
      min->left = q;
      return balance(min);
    }
    return balance(pointer);
  }

 private:
  // структура для представления узлов дерева
  Node *root;
  size_type size{};
};
}
