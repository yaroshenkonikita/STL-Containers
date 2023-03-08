#include "iostream"

namespace s21 {
template <class T>
class BinSTree;

template <class T>
class TreeNode {
 private:
  TreeNode *left;
  TreeNode *right;

 public:
  T data;

  // Конструктор инициализирует поля данных и указателей значение NULL соответствует пустому поддереву
  TreeNode(const T& item, TreeNode<T> *leftChild, TreeNode<T> *rightChild) : data(item), left(leftChild), right(rightChild) {}

  // Методы доступа к полям указателей
  TreeNode* Left(void) const;
  TreeNode* Right(void) const;

  // Создать объект TreeNode с указательными полями leftChild и rightChild. По умолчанию указатели содержат NULL.
  TreeNode *GetTreeNode(T item, TreeNode<T> *leftChild = NULL, TreeNode<T> *rightChild = NULL) {
    TreeNode<T> *p;
    // вызвать new для создания нового узла, передать туда параметры leftChild и rightChild
    p = new TreeNode<T> (item, leftChild, rightChild);
    // если памяти недостаточно, завершить программу
    if (p == NULL) exit(1);
    // вернуть указатель на выделенную системой память
    return p;
  }

  // освободить динамическую память, занимаемую данным узлом
  void FreeTreeNode(TreeNode<T> *p) { delete p; }

  // симметричное рекурсивное прохождение узлов дерева
  void Inorder (TreeNode<T> *child, void visit(T& item)) {
    if (child != NULL) {
      // спуститься по левому поддереву
      Inorder(child->Left(), visit);
      // посетить узел
      visit(child->data);
      // спуститься по правому поддереву
      Inorder(child->Right(), visit);
    }
  }

  // обратное рекурсивное прохождение узлов дерева
  void Postorder (TreeNode<T> *child, void visit (T& item))
  {
    if (child != NULL) {
      // спуститься по левому поддереву
      Postorder(child->Left(), visit);
      // спуститься по правому поддереву
      Postorder(child->Right(), visit);
      // посетить узел
      visit(child->data);

    }
  }

  // проходит дерево с целью подсчета его листьев
  void CountLeaf (TreeNode<T> *child, int& count) {
    // Использовать обратный метод прохождения
    if (child != NULL) {
      CountLeaf(child->Left(), count);  // пройти левое поддерево
      CountLeaf(child->Right(), count); // пройти правое поддерево
      // Проверить, является ли данный узел листом.
      // Если да, то произвести приращение переменной count
      if (child->Left() == NULL && child->Right() == NULL) count++;
    }
  }

  // Вычисляется глубина левого и правого поддеревьев
  int Depth (TreeNode<T> *child) {
    int depthLeft, depthRight, depthval;
    if (child == NULL) depthval = -1;
    else {
      depthLeft = Depth(child->Left());
      depthRight = Depth(child->Right());
      depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
    return depthval;
  }

  // возвращает указатель на вновь созданный узел
  TreeNode *CopyTree(TreeNode<T> *child) {
    TreeNode *newLeftChild, *newRightChild, *newNode;
    // остановить рекурсивное прохождение при достижении пустого дерева
    if (child == NULL) return NULL;
    // CopyTree строит новое дерево в процессе прохождения
    // узлов дерева child. в каждом узле это-го дерева функция
    // CopyTree проверяет наличие левого сына. если он есть,
    // создается его копия. в противном случае возвращается
    // NULL. CopyTree создает копию узла с помощью GetTreeNode
    // и подвешивает к нему копии сыно-вей.
    if (child->Left() != NULL) newLeftChild = CopyTree(child->Left());
    else newLeftChild = NULL;
    if (child->Right() != NULL) newRightChild = CopyTree(child->Right());
    else newRightChild = NULL;
    newNode = GetTreeNode(child->data, newLeftChild, newRightChild);
    // вернуть указатель на вновь создан-ное дерево
    return newNode;
  }

  // удалить каждый узел при его посещении
  void DeleteTree(TreeNode *child) {
    if(child != NULL) {
      DeleteTree(child->Left());
      DeleteTree(child->Right());
      FreeTreeNode(child);
    }
  }

  // friend для доступа к полям left и right
  friend class BinSTree<T>;
};

}