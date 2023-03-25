#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_SET_H_
#define CPP2_S21_CONTAINERS_0_SRC_S21_SET_H_

#include "../ContainersDependence/BinaryTree.h"

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

  set() : BinaryTree<Key>() {}

  set(const std::initializer_list<key_type> &items) {
    this->_begin = this->_root = this->_end = new node_type();
    this->_begin->_height = 0;
    for (value_type item : items) {
      insert(item);
    }
  }

  set(const set &s) : BinaryTree<Key>(s) {}

  set(set &&s) : BinaryTree<Key>(std::move(s)) {}

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
    } else if (!this->FindEqualNode(this->_root, value)) {
      this->_root = this->InsertFromRoot(this->_root, value);
      ++this->_size;
      tmp.second = true;
    }
    iterator current = this->lower_bound(value);
    return {current, tmp.second};
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

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;
    for (auto element : {std::forward<Args>(args)...}) {
      res.push_back(insert(element));
    }
    return res;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_S21_SET_H_
