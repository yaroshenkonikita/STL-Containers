#ifndef STL_CONTAINERS_SET_H_
#define STL_CONTAINERS_SET_H_ 1

#include "containers_dependence/binary_tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key> >
class set : public BinaryTree<Key, Compare> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

  using size_type = std::size_t;
  using node_type = typename BinaryTree<Key, Compare>::node_type;
  using pointer = node_type *;
  using iterator = typename BinaryTree<Key, Compare>::iterator;
  using const_iterator = typename BinaryTree<Key, Compare>::const_iterator;

  set() : BinaryTree<Key, Compare>() {}

  set(const std::initializer_list<key_type> &items) {
    for (value_type item : items) {
      insert(item);
    }
  }

  set(const set &other) : BinaryTree<Key, Compare>(other) {}

  set(set &&other) : BinaryTree<Key, Compare>(std::move(other)) {}

  ~set() = default;

  std::pair<iterator, bool> insert(const_reference value) {
    pointer equal = this->FindEqualNode(value);
    if (equal != &this->_end) {
      return std::make_pair(iterator{equal}, false);
    }
    return std::make_pair(this->BinaryTree<Key, Compare>::insert(value), true);
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
  std::vector<std::pair<iterator, bool> > emplace(Args &&...args) {
    std::vector<std::pair<iterator, bool> > res;
    for (auto element : {std::forward<Args>(args)...}) {
      res.push_back(insert(element));
    }
    return res;
  }
};
}  // namespace s21

#endif  // STL_CONTAINERS_SET_H_
