#ifndef STL_CONTAINERS_SET_H
#define STL_CONTAINERS_SET_H

#include "../BinaryTree.h"

namespace s21 {

template <class Key>
class set : public BinaryTree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

  using size_type = std::size_t;
  using node_type = typename BinaryTree<Key>::node_type;
  using pointer = node_type *;
  using iterator = typename BinaryTree<Key>::iterator;
  using const_iterator = typename BinaryTree<Key>::const_iterator;
  using Compare = typename BinaryTree<Key>::Compare;

 private:
  pointer FindEqualNode(pointer current_node, const key_type &key) {
    if (current_node == this->_end || current_node == nullptr) {
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

 public:
  std::pair<iterator, bool> insert(const_reference value) {
    std::pair<pointer, bool> tmp{};
    if (this->max_size() == this->_size) {
      throw std::overflow_error(
          "Can't insert new element, because size will over max_size");
    }
    if (this->_begin == this->_end) {
      this->_end->_parent = this->_begin = this->_root = new node_type(value);
      this->_begin->_right = this->_end;
      ++this->_size;
      tmp.second = true;
    } else if (!FindEqualNode(this->_root, value)) {
      this->_root = this->InsertFromRoot(this->_root, value);
      ++this->_size;
      tmp.second = true;
    }
    iterator current = this->lower_bound(value);
    return {current, tmp.second};
  }

  set() : BinaryTree<Key>() {}

  set(const std::initializer_list<key_type> &items) {
    this->_begin = this->_root = this->_end = new node_type();
    this->_begin->_height = 0;
    for (value_type item : items) {
      insert(item);
    }
  }

  set(const set &s) : BinaryTree<Key>(s) {}

  set(set &&s) {
    this->_size = std::exchange(s._size, 0);
    this->_root = s._root;
    this->_begin = s._begin;
    this->_end = s._end;
    s._begin = s._end = s._root = new node_type();
  }

  ~set() = default;

  set &operator=(set &&ms) {
    delete this->_root;
    this->_begin = ms._begin;
    this->_end = ms._end;
    this->_root = ms._root;
    this->_size = ms._size;
    ms._begin = ms._end = ms._root = new node_type();
    ms._size = 0;
    return *this;
  }

  void swap(set &other) {
    set tmp = std::move(other);
    other = std::move(*this);
    *this = std::move(tmp);
  }

  void merge(set &other) {
    iterator begin = other.begin(), end = other.end();
    while (begin != end) {
      auto answer = insert(*begin);
      if (answer.second) {
        other.erase(begin++);
      } else {
        ++begin;
      }
    }
  }
};
}  // namespace s21

#endif  // STL_CONTAINERS_SET_H
