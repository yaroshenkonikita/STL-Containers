#ifndef STL_CONTAINERS_MULTISET_H_
#define STL_CONTAINERS_MULTISET_H_ 1

#include "containers_dependence/binary_tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key> >
class multiset : public BinaryTree<Key, Compare> {
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

  multiset() : BinaryTree<Key>() {}
  multiset(const std::initializer_list<key_type> &items)
      : BinaryTree<Key>(items) {}
  multiset(const multiset &other) : BinaryTree<Key>(other) {}
  multiset(multiset &&other) : BinaryTree<Key>(std::move(other)) {}
  ~multiset() = default;

  template <typename... Args>
  std::vector<std::pair<iterator, bool> > emplace(Args &&...args) {
    std::vector<std::pair<iterator, bool> > res;
    for (auto element : {std::forward<Args>(args)...}) {
      res.push_back(std::make_pair(this->insert(element), true));
    }
    return res;
  }
};

}  // namespace s21

#endif  // STL_CONTAINERS_MULTISET_H_
