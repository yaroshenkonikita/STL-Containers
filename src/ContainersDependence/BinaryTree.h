#ifndef CPP2_S21_CONTAINERS_0_SRC_BINARYTREE_H_
#define CPP2_S21_CONTAINERS_0_SRC_BINARYTREE_H_

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <class Key>
class BinaryTree {
 protected:
  class Node;
  class TreeIterator;
  class TreeConstIterator;
  using Compare = std::less<Key>;

 public:
  using node_type = Node;
  using pointer = node_type *;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using iterator = TreeIterator;
  using const_iterator = TreeConstIterator;

  BinaryTree();
  BinaryTree(const std::initializer_list<value_type> &items);
  BinaryTree(const BinaryTree &other);
  BinaryTree(BinaryTree &&other) noexcept;
  ~BinaryTree();
  BinaryTree &operator=(BinaryTree &&other);

  iterator insert(const_reference value);
  void clear();
  virtual bool contains(const key_type &key);
  void erase(iterator pos);
  size_type count(const key_type &key);
  virtual iterator find(const key_type &key);
  virtual iterator lower_bound(const key_type &key);
  virtual iterator upper_bound(const key_type &key);
  std::pair<iterator, iterator> equal_range(const key_type &key);
  [[nodiscard]] size_type size() const noexcept;
  iterator begin() noexcept;
  iterator end() noexcept;
  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_type max_size() const noexcept;
  void swap(BinaryTree &other);
  void merge(BinaryTree &other);

 protected:
  pointer FindNodeFromIterator(iterator pos);
  pointer FindEqualNode(pointer current_node, const key_type &key);
  void DeleteNodeWithoutChild(pointer current);
  void DeleteNodeWithOneChild(pointer current);
  pointer CopyAllChild(pointer parent) const;
  virtual pointer FindFirstEqualOrNearPointer(
      const key_type &key) const noexcept;
  size_type Height(pointer current_node) const;
  int BalanceDiff(pointer current_node) const;
  void FixHeight(pointer current_node);
  pointer LeftRotate(pointer current_node);
  pointer RightRotate(pointer current_node);
  pointer Balance(pointer current_node);
  pointer InsertFromRoot(pointer current_node, const_reference value);
  pointer GetMin() const;
  pointer GetMax() const;

  pointer _root{}, _begin{}, _end{};
  size_type _size{};
};

template <class Key>
BinaryTree<Key>::BinaryTree() {
  _begin = _root = _end = new Node();
  _begin->_height = 0;
}

template <class Key>
BinaryTree<Key>::BinaryTree(const std::initializer_list<value_type> &items) {
  _begin = _root = _end = new Node();
  _begin->_height = 0;
  for (value_type item : items) {
    insert(item);
  }
}

template <class Key>
BinaryTree<Key>::BinaryTree(const BinaryTree &other) : _size(other._size) {
  _root = CopyAllChild(other._root);
  _begin = GetMin();
  _end = GetMax();
}

template <class Key>
BinaryTree<Key>::BinaryTree(BinaryTree &&other) noexcept {
  _size = std::exchange(other._size, 0);
  _root = other._root;
  _begin = other._begin;
  _end = other._end;
  other._begin = other._end = other._root = new Node();
}

template <class Key>
BinaryTree<Key>::~BinaryTree() {
  delete _root;
}

template <class Key>
BinaryTree<Key> &BinaryTree<Key>::operator=(BinaryTree &&other) {
  delete this->_root;
  this->_begin = other._begin;
  this->_end = other._end;
  this->_root = other._root;
  this->_size = other._size;
  other._begin = other._end = other._root = new node_type();
  other._size = 0;
  return *this;
}

template <class Key>
class BinaryTree<Key>::Node {
 public:
  Node() = default;
  explicit Node(Key value) : _value(value) {}
  Node(Key value, Node *node) : _value(value), _parent(node) {}
  virtual ~Node() {
    delete _left;
    delete _right;
  }
  Key _value{};
  Node *_left{}, *_right{}, *_parent{};
  std::size_t _height = 1;

  void SetNewParent(Node *parent) { _parent = parent; }

  void SetLeftChild(Node *child) {
    _left = child;
    if (child) {
      child->_parent = this;
    }
  }

  void SetRightChild(Node *child) {
    _right = child;
    if (child) {
      child->_parent = this;
    }
  }

  void SetAllNodes(Node *parent = nullptr, Node *left_child = nullptr,
                   Node *right_child = nullptr) {
    SetNewParent(parent);
    SetLeftChild(left_child);
    SetRightChild(right_child);
  }

  static pointer Next(pointer current_node) {
    pointer last_position{};
    while (current_node->_right == nullptr ||
           current_node->_right == last_position) {
      last_position = current_node;
      if (!current_node->_parent) {
        while (current_node->_left) {
          current_node = current_node->_left;
        }
        return current_node;
      }
      current_node = current_node->_parent;
      if (current_node->_right != last_position) {
        return current_node;
      }
    }
    current_node = current_node->_right;
    while (current_node->_left != nullptr) {
      current_node = current_node->_left;
    }
    return current_node;
  }

  static pointer Prev(pointer current_node) {
    if (!current_node->_left) {
      pointer last_position{};
      while (current_node->_left == last_position) {
        last_position = current_node;
        if (!current_node->_parent) {
          while (current_node->_right) {
            current_node = current_node->_right;
          }
          return current_node;
        }
        current_node = current_node->_parent;
      }
    } else {
      current_node = current_node->_left;
      while (current_node->_right) {
        current_node = current_node->_right;
      }
    }
    return current_node;
  }
};

// iterators ================================================================
template <class Key>
class BinaryTree<Key>::TreeIterator {
 public:
  TreeIterator() = default;
  TreeIterator(pointer current) noexcept : current_node(current) {}
  TreeIterator(TreeIterator &other) noexcept
      : current_node(other.current_node) {}
  TreeIterator(TreeIterator &&other) noexcept
      : current_node(other.current_node) {}
  virtual ~TreeIterator() = default;

  virtual value_type operator*() { return current_node->_value; }

  TreeIterator operator++() {
    current_node = current_node->Next(current_node);
    return *this;
  }

  TreeIterator operator++(int) {
    iterator it = *this;
    ++*this;
    return it;
  }

  TreeIterator operator--() {
    current_node = current_node->Prev(current_node);
    return *this;
  }

  TreeIterator operator--(int) {
    iterator it = *this;
    --*this;
    return it;
  }

  bool operator!=(const TreeIterator other) const noexcept {
    return other.current_node != current_node;
  }

  bool operator==(const TreeIterator other) const noexcept {
    return other.current_node == current_node;
  }

  friend bool operator==(const TreeIterator &first, const pointer &second) {
    return first.current_node == second;
  }

  friend bool operator!=(const TreeIterator &first, const pointer &second) {
    return first.current_node != second;
  }

  friend bool operator==(const pointer &second, const TreeIterator &first) {
    return first.current_node == second;
  }

  friend bool operator!=(const pointer &second, const TreeIterator &first) {
    return first.current_node != second;
  }

 protected:
  pointer current_node{};
};

template <class Key>
class BinaryTree<Key>::TreeConstIterator
    : public BinaryTree<Key>::TreeIterator {
 public:
  TreeConstIterator() = default;
  TreeConstIterator(pointer current) noexcept
      : BinaryTree<Key>::TreeIterator(current) {}
  TreeConstIterator(TreeConstIterator &other) noexcept {
    this->current_node = other.current_node;
  }
  TreeConstIterator(TreeConstIterator &&other) noexcept {
    this->current_node = other.current_node;
  }
  ~TreeConstIterator() = default;
};

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::insert(
    const_reference value) {
  if (max_size() == _size) {
    throw std::overflow_error(
        "Can't insert new element, because size will over max_size");
  }
  if (_begin == _end) {
    _end->_parent = _begin = _root = new node_type(value);
    _begin->_right = _end;
  } else {
    _root = InsertFromRoot(_root, value);
  }
  ++_size;
  iterator current = lower_bound(value);
  return --current;
}

template <class Key>
void BinaryTree<Key>::clear() {
  _end->_parent = _end->_parent->_right = nullptr;
  delete _root;
  _begin = _root = _end;
  _size = 0;
}

template <class Key>
bool BinaryTree<Key>::contains(const key_type &key) {
  pointer current = FindFirstEqualOrNearPointer(key);
  return key == (current->_value);
}

template <class Key>
void BinaryTree<Key>::erase(iterator pos) {
  if (pos == end()) {
    throw std::invalid_argument("Invalid pointer: Cannot remove end pointer");
  }
  pointer current_node = FindNodeFromIterator(pos);
  if (current_node->_left && current_node->_right) {
    pointer tmp_current_node = current_node;
    current_node = Node::Prev(current_node);
    tmp_current_node->_value = current_node->_value;
  }
  if (!current_node->_left && !current_node->_right) {
    DeleteNodeWithoutChild(current_node);
  } else {
    DeleteNodeWithOneChild(current_node);
  }
  _begin = _root;
  while (_begin->_left) {
    _begin = _begin->_left;
  }
  --_size;
}

template <class Key>
typename BinaryTree<Key>::size_type BinaryTree<Key>::count(
    const key_type &key) {
  std::pair<iterator, iterator> iter = equal_range(key);
  size_type size{};
  while (iter.first != iter.second) {
    ++iter.first, ++size;
  }
  return size;
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::find(const key_type &key) {
  iterator current = lower_bound(key);
  if ((*current) == key) {
    return current;
  }
  return TreeIterator(_end);
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::lower_bound(
    const key_type &key) {
  pointer current_node = FindFirstEqualOrNearPointer(key);
  iterator iter = TreeIterator(current_node);
  while (iter != end()) {
    if ((*iter) == key) {
      --iter;
    } else {
      break;
    }
  }
  return ++iter;
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::upper_bound(
    const key_type &key) {
  pointer current_node = FindFirstEqualOrNearPointer(key);
  iterator iter = TreeIterator(current_node);
  while (iter != _end) {
    if ((*iter) <= key) {
      ++iter;
    } else {
      break;
    }
  }
  return iter;
}

template <class Key>
std::pair<typename BinaryTree<Key>::iterator,
          typename BinaryTree<Key>::iterator>
BinaryTree<Key>::equal_range(const key_type &key) {
  return std::pair<iterator, iterator>{lower_bound(key), upper_bound(key)};
}

template <class Key>
typename BinaryTree<Key>::size_type BinaryTree<Key>::size() const noexcept {
  return _size;
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::begin() noexcept {
  return TreeIterator(_begin);
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::end() noexcept {
  return TreeIterator(_end);
}

template <class Key>
bool BinaryTree<Key>::empty() const noexcept {
  return _size == 0;
}

template <class Key>
typename BinaryTree<Key>::size_type BinaryTree<Key>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(node_type) / 2;
}

template <class Key>
void BinaryTree<Key>::swap(BinaryTree &other) {
  BinaryTree tmp = std::move(other);
  other = std::move(*this);
  *this = std::move(tmp);
}

template <class Key>
void BinaryTree<Key>::merge(BinaryTree &other) {
  for (value_type item : other) {
    this->insert(item);
  }
  other.clear();
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::InsertFromRoot(
    pointer current_node, const_reference &value) {
  if (!current_node) return new Node(value);
  if (Compare{}(value, current_node->_value)) {
    current_node->_left = InsertFromRoot(current_node->_left, value);
    current_node->_left->_parent = current_node;
    if (current_node == _begin && current_node->_left) {
      _begin = current_node->_left;
    }
  } else {
    if (current_node->_right == _end) {
      _end->_parent = current_node->_right = new Node(value, current_node);
      current_node->_right->_right = _end;
    } else {
      current_node->_right = InsertFromRoot(current_node->_right, value);
      current_node->_right->_parent = current_node;
    }
  }
  return Balance(current_node);
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::FindNodeFromIterator(
    iterator pos) {
  pointer current_node = FindFirstEqualOrNearPointer((*pos)),
          tmp_node = current_node;
  while ((current_node->_value) == (*pos)) {
    if (current_node == pos) {
      return current_node;
    }
    current_node = Node::Prev(current_node);
  }
  while ((tmp_node->_value) == (*pos)) {
    if (tmp_node == pos) {
      return tmp_node;
    }
    tmp_node = Node::Next(tmp_node);
  }
  throw std::logic_error("Haven't node in tree");
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::FindFirstEqualOrNearPointer(
    const key_type &key) const noexcept {
  pointer current_node = _root;
  while (current_node != _end) {
    if (Compare{}(key, current_node->_value)) {
      if (current_node->_left != nullptr) {
        current_node = current_node->_left;
      } else {
        break;
      }
    } else if (key == current_node->_value) {
      return current_node;
    } else if (current_node->_right != nullptr &&
               current_node->_right != _end) {
      current_node = current_node->_right;
    } else {
      break;
    }
  }
  return current_node;
}

template <class Key>
void BinaryTree<Key>::DeleteNodeWithoutChild(pointer current) {
  pointer parent = current->_parent, last_position{};
  if (parent->_left == current) {
    parent->_left = nullptr;
  } else {
    parent->_right = nullptr;
  }
  delete current;
  do {
    Balance(parent);
    last_position = parent;
    parent = parent->_parent;
  } while (parent != nullptr);
  _root = last_position;
}

template <class Key>
void BinaryTree<Key>::DeleteNodeWithOneChild(pointer current) {
  pointer parent = current->_parent,
          child = current->_left ? current->_left : current->_right,
          last_position{};
  current->_left = current->_right = nullptr;
  child->_parent = parent;
  if (!parent) {
    _root = child;
    _root->_parent = nullptr;
    delete current;
  } else {
    if (parent->_left == current) {
      parent->_left = child;
    } else {
      parent->_right = child;
    }
    delete current;
    do {
      Balance(parent);
      last_position = parent;
      parent = parent->_parent;
    } while (parent != nullptr);
    _root = last_position;
  }
}

template <class Key>
typename BinaryTree<Key>::size_type BinaryTree<Key>::Height(
    pointer current_node) const {
  return current_node ? current_node->_height : 0;
}

template <class Key>
int BinaryTree<Key>::BalanceDiff(pointer current_node) const {
  return Height(current_node->_right) - Height(current_node->_left);
}

template <class Key>
void BinaryTree<Key>::FixHeight(pointer current_node) {
  current_node->_height =
      std::max(Height(current_node->_left), Height(current_node->_right)) + 1;
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::LeftRotate(
    pointer current_node) {
  pointer second_node = current_node->_right,
          min_second_node = second_node->_left;
  second_node->SetAllNodes(current_node->_parent, current_node,
                           second_node->_right);
  current_node->SetAllNodes(second_node, current_node->_left, min_second_node);
  if (second_node->_parent) {
    if (second_node->_parent->_left == current_node) {
      second_node->_parent->_left = second_node;
    } else {
      second_node->_parent->_right = second_node;
    }
  }
  FixHeight(current_node);
  FixHeight(second_node);
  return second_node;
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::RightRotate(
    pointer current_node) {
  pointer second_node = current_node->_left,
          max_second_node = second_node->_right;
  second_node->SetAllNodes(current_node->_parent, second_node->_left,
                           current_node);
  current_node->SetAllNodes(second_node, max_second_node, current_node->_right);
  if (second_node->_parent) {
    if (second_node->_parent->_left == current_node) {
      second_node->_parent->_left = second_node;
    } else {
      second_node->_parent->_right = second_node;
    }
  }
  FixHeight(current_node);
  FixHeight(second_node);
  return second_node;
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::Balance(
    pointer current_node) {
  FixHeight(current_node);
  if (BalanceDiff(current_node) == 2) {
    if (BalanceDiff(current_node->_right) < 0)
      RightRotate(current_node->_right);
    return LeftRotate(current_node);
  } else if (BalanceDiff(current_node) == -2) {
    if (BalanceDiff(current_node->_left) > 0) LeftRotate(current_node->_left);
    return RightRotate(current_node);
  }
  return current_node;
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::CopyAllChild(
    pointer parent) const {
  pointer childLeft{}, childRight{};
  if (parent->_left) childLeft = CopyAllChild(parent->_left);
  if (parent->_right) childRight = CopyAllChild(parent->_right);
  pointer tmp_parent;
  tmp_parent = new Node(parent->_value);
  tmp_parent->_height = parent->_height;
  tmp_parent->SetAllNodes(nullptr, childLeft, childRight);
  return tmp_parent;
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::FindEqualNode(
    pointer current_node, const key_type &key) {
  if (current_node == _end || current_node == nullptr) {
    return nullptr;
  }
  if (Compare{}(key, current_node->_value)) {
    return FindEqualNode(current_node->_left, key);
  } else if (current_node->_value == key) {
    return current_node;
  } else {
    return FindEqualNode(current_node->_right, key);
  }
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::GetMin() const {
  pointer tmp_node = _root;
  while (tmp_node->_left) {
    tmp_node = tmp_node->_left;
  }
  return tmp_node;
}

template <class Key>
typename BinaryTree<Key>::pointer BinaryTree<Key>::GetMax() const {
  pointer tmp_node = _root;
  while (tmp_node->_right) {
    tmp_node = tmp_node->_right;
  }
  return tmp_node->_parent;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_BINARYTREE_H_
