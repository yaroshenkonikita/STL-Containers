#ifndef STL_CONTAINERS_SRC_BINARY_TREE_H_
#define STL_CONTAINERS_SRC_BINARY_TREE_H_ 1

#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename Key, typename Compare = std::less<Key> >
class BinaryTree {
 protected:
  class Node;
  class TreeIterator;

 public:
  using node_type = Node;
  using pointer = node_type *;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using iterator = TreeIterator;
  using const_iterator = const TreeIterator;

  BinaryTree() noexcept;
  BinaryTree(const std::initializer_list<value_type> &items);
  BinaryTree(const BinaryTree &other);
  BinaryTree(BinaryTree &&other) noexcept;
  virtual ~BinaryTree();
  BinaryTree &operator=(const BinaryTree &other) noexcept;
  BinaryTree &operator=(BinaryTree &&other) noexcept;

  iterator insert(const_reference value);
  void clear();
  bool contains(const_reference key) const noexcept;
  void erase(iterator pos);
  size_type count(const_reference key) const noexcept;
  iterator find(const_reference key) const noexcept;
  iterator lower_bound(const_reference key) const noexcept;
  iterator upper_bound(const_reference key) const noexcept;
  std::pair<iterator, iterator> equal_range(const_reference key) const noexcept;
  [[nodiscard]] size_type size() const noexcept;
  iterator begin() const noexcept;
  iterator end() const noexcept;
  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] constexpr size_type max_size() const noexcept;
  void swap(BinaryTree &other);
  void merge(BinaryTree &other);

 protected:
  void InsertFromNode(pointer current, pointer new_object);
  void DeleteNodeWithoutChild(pointer current);
  void DeleteNodeWithOneChild(pointer current);
  pointer CopyAllChild(pointer parent) const;
  virtual pointer FindEqualNode(const_reference key) const noexcept;
  size_type Height(pointer current_node) const;
  int BalanceDiff(pointer current_node) const;
  void FixHeight(pointer current_node);
  pointer LeftRotate(pointer current_node);
  pointer RightRotate(pointer current_node);
  pointer Balance(pointer current_node);
  void BalanceFromNode(pointer current_node);
  pointer GetMin() const;
  pointer GetMax() const;

  node_type _end;
  pointer _root, _begin;
  size_type _size;
  Compare _comparator;
};

template <typename Key, typename Compare>
BinaryTree<Key, Compare>::BinaryTree() noexcept : _end(), _root(&_end), _begin(&_end), _size(0), _comparator() {
  _end._height = 0;
}

template <typename Key, typename Compare>
BinaryTree<Key, Compare>::BinaryTree(const std::initializer_list<value_type> &items) : BinaryTree() {
  for (const_reference item : items) {
    insert(item);
  }
}

template <typename Key, typename Compare>
BinaryTree<Key, Compare>::BinaryTree(const BinaryTree &other) : BinaryTree() {
  if (other._root == &other._end) {
    return;
  }
  _size = other._size;
  pointer last_other = other._end._parent;
  last_other->_right = nullptr;
  _root = CopyAllChild(other._root);
  last_other->_right = const_cast<pointer>(&(other._end));
  _begin = GetMin();
  GetMax()->SetRightChild(&_end);
}

template <typename Key, typename Compare>
BinaryTree<Key, Compare>::BinaryTree(BinaryTree &&other) noexcept : BinaryTree() {
  if (other._root == &other._end) {
    return;
  }
  _size = std::exchange(other._size, 0);
  _root = std::exchange(other._root, &other._end);
  _begin = std::exchange(other._begin, &other._end);
  std::swap(_end._parent, other._end._parent);
  _end._parent->_right = &_end;
}

template <typename Key, typename Compare>
BinaryTree<Key, Compare>::~BinaryTree() {
  if (_end._parent == nullptr) {
    return;
  }
  _end._parent->_right = nullptr;
  delete _root;
}

template <typename Key, typename Compare>
BinaryTree<Key, Compare> &BinaryTree<Key, Compare>::operator=(const BinaryTree &other) noexcept {
  if (this == &other) {
    return *this;
  }
  clear();
  if (other._root != &other._end) {
    pointer last_other = other._end.parent;
    last_other->right = nullptr;
    _root = CopyAllChild(other._root);
    last_other->right = &other._end;
    _begin = GetMin();
    GetMax().SetRightChild(&_end);
  }
  return *this;
}

template <typename Key, typename Compare>
BinaryTree<Key, Compare> &BinaryTree<Key, Compare>::operator=(BinaryTree &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  clear();
  if (other._root != &other._end) {
    _size = std::exchange(other._size, 0);
    _root = std::exchange(other._root, &other._end);
    _begin = std::exchange(other._begin, &other._end);
    std::swap(_end._parent, other._end._parent);
    _end._parent->_right = &_end;
  }
  return *this;
}

template <typename Key, typename Compare>
class BinaryTree<Key, Compare>::Node {
 public:
  Node() = default;
  explicit Node(Key value) : _value(value) {}
  Node(Key value, Node *node) : _value(value), _parent(node) {}
  ~Node() {
    delete _left;
    delete _right;
  }
  Key _value{};
  BinaryTree<Key, Compare>::pointer _left{}, _right{}, _parent{};
  uint8_t _height = 1;

  void SetNewParent(Node *parent) noexcept {
    _parent = parent;
  }

  void SetLeftChild(Node *child) noexcept {
    _left = child;
    if (child) {
      child->_parent = this;
    }
  }

  void SetRightChild(Node *child) noexcept {
    _right = child;
    if (child) {
      child->_parent = this;
    }
  }

  void SetAllNodes(Node *parent = nullptr, Node *left_child = nullptr,
                   Node *right_child = nullptr) noexcept {
    SetNewParent(parent);
    SetLeftChild(left_child);
    SetRightChild(right_child);
  }

  static pointer Next(const pointer current_node) noexcept {
    pointer next_node = current_node;
    pointer last_position{};
    while ((next_node->_right == nullptr) ||
           (next_node->_right == last_position)) {
      last_position = next_node;
      if (next_node->_parent == nullptr) {
        while (next_node->_left != nullptr) {
          next_node = next_node->_left;
        }
        return next_node;
      }
      next_node = next_node->_parent;
      if (next_node->_right != last_position) {
        return next_node;
      }
    }
    next_node = next_node->_right;
    while (next_node->_left != nullptr) {
      next_node = next_node->_left;
    }
    return next_node;
  }

  static pointer Prev(const pointer current_node) noexcept {
    pointer prev_node = current_node;
    if (!prev_node->_left) {
      pointer last_position{};
      while (prev_node->_left == last_position) {
        last_position = prev_node;
        if (prev_node->_parent == nullptr) {
          while (prev_node->_right) {
            prev_node = prev_node->_right;
          }
          return prev_node;
        }
        prev_node = prev_node->_parent;
      }
    } else {
      prev_node = prev_node->_left;
      while (prev_node->_right) {
        prev_node = prev_node->_right;
      }
    }
    return prev_node;
  }
};

// iterators ================================================================
template <typename Key, typename Compare>
class BinaryTree<Key, Compare>::TreeIterator {
  friend class BinaryTree<Key, Compare>;
 public:
  TreeIterator() noexcept = default;
  TreeIterator(const pointer &current) noexcept : current_node(current) {}
  TreeIterator(pointer &&current) noexcept : current_node(std::exchange(current, nullptr)) {}
  TreeIterator(const TreeIterator &other) noexcept
      : current_node(other.current_node) {}
  TreeIterator(TreeIterator &&other) noexcept
      : current_node(std::exchange(other.current_node, nullptr)) {}
  TreeIterator& operator=(const TreeIterator& other) {
    current_node = other.current_node;
    return *this;
  }
  TreeIterator& operator=(TreeIterator&& other) {
    current_node = std::exchange(other.current_node, nullptr);
    return *this;
  }
  ~TreeIterator() noexcept = default;

  const_reference operator*() const noexcept { return current_node->_value; }

  TreeIterator operator++() const noexcept {
    current_node = node_type::Next(current_node);
    return *this;
  }

  TreeIterator operator++(int) const noexcept {
    iterator it = *this;
    ++*this;
    return it;
  }

  TreeIterator operator--() const noexcept {
    current_node = current_node->Prev(current_node);
    return *this;
  }

  TreeIterator operator--(int) const noexcept {
    iterator it = *this;
    --*this;
    return it;
  }

  bool operator!=(const TreeIterator &other) const noexcept {
    return other.current_node != current_node;
  }

  bool operator==(const TreeIterator &other) const noexcept {
    return other.current_node == current_node;
  }

 protected:
  mutable pointer current_node{};
};

template <typename Key, typename Compare>
void BinaryTree<Key, Compare>::InsertFromNode(pointer current_node, pointer new_object) {
  bool isLeft;
  for (;;) {
    isLeft = _comparator(new_object->_value, current_node->_value);
    pointer next_node;
    if (isLeft) {
      next_node = current_node->_left;
    } else {
      next_node = current_node->_right;
    }
    if ((next_node == nullptr) || (next_node == &_end)) {
      break;
    }
    current_node = next_node;
  }
  if (isLeft) {
    current_node->SetLeftChild(new_object);
    if (current_node == _begin) {
      _begin = new_object;
    }
  } else {
    if (current_node->_right == &_end) {
      new_object->SetRightChild(&_end);
    }
    current_node->SetRightChild(new_object);
  }
  BalanceFromNode(new_object);
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::iterator BinaryTree<Key, Compare>::insert(
    const_reference value) {
  if (max_size() == _size) {
    throw std::overflow_error(
        "Can't insert new element, because size will over max_size");
  }
  pointer new_object = new node_type(value);
  if (_root == &_end) {
    _end._parent = _begin = _root = new_object;
    _root->_right = &_end;
  } else {
    InsertFromNode(_root, new_object);
  }
  ++_size;
  return iterator{new_object};
}

template <typename Key, typename Compare>
void BinaryTree<Key, Compare>::clear() {
  if (_end._parent == nullptr) {
    return;
  }
  _end._parent->_right = nullptr;
  delete _root;
  _end._parent = nullptr;
  _size = 0;
  _begin = _root = &_end;
}

template <typename Key, typename Compare>
bool BinaryTree<Key, Compare>::contains(const_reference key) const noexcept {
  return FindEqualNode(key) != &_end;
}

template <typename Key, typename Compare>
void BinaryTree<Key, Compare>::erase(iterator pos) {
  pointer current_node = pos.current_node;
  if (current_node->_left == nullptr && current_node->_right == nullptr) {
    DeleteNodeWithoutChild(current_node);
  } else if (current_node->_left == nullptr || current_node->_right == nullptr) {
    DeleteNodeWithOneChild(current_node);
  } else {
    pointer prev_node = node_type::Prev(current_node);
    current_node->_value = std::move(prev_node->_value);
    return erase(iterator{prev_node});
  }
  --_size;
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::size_type BinaryTree<Key, Compare>::count(
    const_reference key) const noexcept {
  pointer equal_node = FindEqualNode(key);
  if (equal_node == &_end) {
    return 0;
  }
  size_type size = 0;
  pointer to_left = equal_node;
  if (to_left != _begin) {
    while (to_left != _begin) {
      to_left = node_type::Prev(to_left);
      const bool isLeft = _comparator(key, to_left->_value);
      const bool isRight = _comparator(to_left->_value, key);
      if (!isLeft && !isRight) {
        ++size;
      } else {
        break;
      }
    }
  }
  for (; equal_node != &_end; equal_node = node_type::Next(equal_node)) {
    const bool isLeft = _comparator(key, equal_node->_value);
    const bool isRight = _comparator(equal_node->_value, key);
    if (!isLeft && !isRight) {
      ++size;
    } else {
      break;
    }
  }
  return size;
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::iterator BinaryTree<Key, Compare>::find(const_reference key) const noexcept {
  return iterator{FindEqualNode(key)};
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::iterator BinaryTree<Key, Compare>::lower_bound(
    const_reference &key) const noexcept {
  if (_root == &_end) {
    return end();
  }
  pointer current_node = _root, next_node = current_node;
  while (next_node != nullptr) {
    current_node = next_node;
    if (current_node == &_end) {
      return end();
    }
    if (_comparator(current_node->_value, key)) {
      next_node = current_node->_right;
    } else {
      next_node = current_node->_left;
    }
  }
  if (_comparator(current_node->_value, key)) {
    current_node = node_type::Next(current_node);
  }
  return iterator{current_node};
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::iterator BinaryTree<Key, Compare>::upper_bound(
    const_reference key) const noexcept {
  if (_root == &_end) {
    return end();
  }
  pointer current_node = _root, next_node = current_node;
  while (next_node != nullptr) {
    current_node = next_node;
    if (current_node == &_end) {
      return end();
    }
    if (!_comparator(key, current_node->_value)) {
      next_node = current_node->_right;
    } else {
      next_node = current_node->_left;
    }
  }
  if (!_comparator(key, current_node->_value)) {
    current_node = node_type::Next(current_node);
  }
  return iterator{current_node};
}

template <typename Key, typename Compare>
std::pair<typename BinaryTree<Key, Compare>::iterator,
          typename BinaryTree<Key, Compare>::iterator>
BinaryTree<Key, Compare>::equal_range(const_reference key) const noexcept {
  return std::pair<iterator, iterator>{lower_bound(key), upper_bound(key)};
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::size_type BinaryTree<Key, Compare>::size() const noexcept {
  return _size;
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::iterator BinaryTree<Key, Compare>::begin() const noexcept {
  return TreeIterator(_begin);
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::iterator BinaryTree<Key, Compare>::end() const noexcept {
  return TreeIterator(const_cast<const pointer>(&_end));
}

template <typename Key, typename Compare>
bool BinaryTree<Key, Compare>::empty() const noexcept {
  return _size == 0;
}

template <typename Key, typename Compare>
constexpr typename BinaryTree<Key, Compare>::size_type BinaryTree<Key, Compare>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(node_type) / 2;
}

template <typename Key, typename Compare>
void BinaryTree<Key, Compare>::swap(BinaryTree &other) {
  BinaryTree tmp = std::move(other);
  other = std::move(*this);
  *this = std::move(tmp);
}

template <typename Key, typename Compare>
void BinaryTree<Key, Compare>::merge(BinaryTree &other) {
  for (value_type item : other) {
    this->insert(item);
  }
  other.clear();
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::pointer BinaryTree<Key, Compare>::FindEqualNode(
    const_reference key) const noexcept {
  pointer current_node = _root;
  for (;;) {
    const bool isLeft = _comparator(key, current_node->_value);
    const bool isRight = _comparator(current_node->_value, key);
    if (!isLeft && !isRight) {
      return current_node;
    }
    if (isLeft) {
      current_node = current_node->_left;
    } else {
      current_node = current_node->_right;
    }
    if (current_node == nullptr) {
      return const_cast<pointer>(&_end);
    }
  }
}

template <typename Key, typename Compare>
void BinaryTree<Key, Compare>::DeleteNodeWithoutChild(pointer current) {
  pointer parent = current->_parent;
  if (parent->_left == current) {
    parent->_left = nullptr;
  } else {
    parent->_right = nullptr;
  }
  delete current;
  BalanceFromNode(parent);
}

template <typename Key, typename Compare>
void BinaryTree<Key, Compare>::DeleteNodeWithOneChild(pointer current) {
  pointer parent = current->_parent,
          child = current->_left ? current->_left : current->_right;
  current->_left = current->_right = nullptr;
  child->_parent = parent;
  if (!parent) {
    _root = child;
    delete current;
  } else {
    if (parent->_left == current) {
      parent->_left = child;
    } else {
      parent->_right = child;
    }
    delete current;
    BalanceFromNode(child);
  }
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::size_type BinaryTree<Key, Compare>::Height(
    pointer current_node) const {
  return current_node ? current_node->_height : 0;
}

template <typename Key, typename Compare>
int BinaryTree<Key, Compare>::BalanceDiff(pointer current_node) const {
  return Height(current_node->_right) - Height(current_node->_left);
}

template <typename Key, typename Compare>
void BinaryTree<Key, Compare>::FixHeight(pointer current_node) {
  current_node->_height =
      std::max(Height(current_node->_left), Height(current_node->_right)) + 1;
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::pointer BinaryTree<Key, Compare>::LeftRotate(
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

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::pointer BinaryTree<Key, Compare>::RightRotate(
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

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::pointer BinaryTree<Key, Compare>::Balance(
    pointer current_node) {
  FixHeight(current_node);
  if (BalanceDiff(current_node) == 2) {
    if (BalanceDiff(current_node->_right) < 0) {
      RightRotate(current_node->_right);
    }
    return LeftRotate(current_node);
  } else if (BalanceDiff(current_node) == -2) {
    if (BalanceDiff(current_node->_left) > 0) {
      LeftRotate(current_node->_left);
    }
    return RightRotate(current_node);
  }
  return current_node;
}

template <typename Key, typename Compare>
void BinaryTree<Key, Compare>::BalanceFromNode(pointer current_node) {
  for (pointer to_root = current_node; to_root != nullptr; to_root = to_root->_parent) {
    _root = Balance(to_root);
  }
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::pointer BinaryTree<Key, Compare>::CopyAllChild(
    pointer current_node) const {
  pointer childLeft{}, childRight{};
  if (current_node->_left) {
    childLeft = CopyAllChild(current_node->_left);
  }
  if (current_node->_right) {
    childRight = CopyAllChild(current_node->_right);
  }
  pointer tmp_node = new Node(current_node->_value);
  tmp_node->_height = current_node->_height;
  tmp_node->SetAllNodes(nullptr, childLeft, childRight);
  return tmp_node;
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::pointer BinaryTree<Key, Compare>::GetMin() const {
  pointer tmp_node = _root;
  while (tmp_node->_left) {
    tmp_node = tmp_node->_left;
  }
  return tmp_node;
}

template <typename Key, typename Compare>
typename BinaryTree<Key, Compare>::pointer BinaryTree<Key, Compare>::GetMax() const {
  pointer tmp_node = _root;
  while (tmp_node->_right) {
    tmp_node = tmp_node->_right;
  }
  return tmp_node;
}

}  // namespace s21

#endif  // STL_CONTAINERS_SRC_BINARYTREE_H_
