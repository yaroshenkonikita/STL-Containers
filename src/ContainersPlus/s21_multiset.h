#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_0_SRC_S21_MULTISET_H_

#include "../BinaryTree/BinaryTree.h"

namespace s21 {

template <class Key>
class multiset : public BinaryTree<Key> {
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

  iterator insert(const_reference value) {
    if (this->max_size() == this->_size) {
      throw std::overflow_error(
          "Can't insert new element, because size will over max_size");
    }
    if (this->_begin == this->_end) {
      this->_end->_parent = this->_begin = this->_root = new node_type(value);
      this->_begin->_right = this->_end;
    } else {
      this->_root = this->InsertFromRoot(this->_root, value);
    }
    ++this->_size;
    iterator current = this->lower_bound(value);
    return --current;
  }

  multiset() : BinaryTree<Key>() {}
  multiset(const std::initializer_list<key_type> &items)
      : BinaryTree<Key>(items) {}
  multiset(const multiset &ms) : BinaryTree<Key>(ms) {}
  multiset(multiset &&ms) : BinaryTree<Key>(std::move(ms)) {
    //    this->_size = std::exchange(ms._size, 0);
    //    this->_root = ms._root;
    //    this->_begin = ms._begin;
    //    this->_end = ms._end;
    //    ms._begin = ms._end = ms._root = new node_type();
  }
  ~multiset() = default;

  multiset &operator=(multiset &&ms) {
    delete this->_root;
    this->_begin = ms._begin;
    this->_end = ms._end;
    this->_root = ms._root;
    this->_size = ms._size;
    ms._begin = ms._end = ms._root = new node_type();
    ms._size = 0;
    return *this;
  }

  void swap(multiset &other) {
    multiset tmp = std::move(other);
    other = std::move(*this);
    *this = std::move(tmp);
  }

  void merge(multiset &other) {
    for (value_type item : other) {
      this->insert(item);
    }
    other.clear();
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
      std::vector<std::pair<iterator, bool>> res;
      for (auto element : {std::forward<Args>(args)...}) {
          res.push_back(std::make_pair(insert(element), true));
      }
    return res;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_S21_MULTISET_H_
