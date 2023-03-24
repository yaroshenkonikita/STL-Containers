#ifndef STL_CONTAINERS_MAP_H_
#define STL_CONTAINERS_MAP_H_

#include "../BinaryTree.h"

namespace s21 {
template <class Key, class Value>
class map : public BinaryTree<std::pair<Key, Value>> {
  class MapIterator;
  class MapConstIterator;

 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<Key, Value>;
  using reference = value_type &;
  using const_reference = const value_type &;

  using size_type = std::size_t;
  using node_type = typename BinaryTree<std::pair<Key, Value>>::node_type;
  using pointer = node_type *;
  using iterator = typename BinaryTree<std::pair<Key, Value>>::iterator;
  using const_iterator =
      typename BinaryTree<std::pair<Key, Value>>::const_iterator;
  using Compare = std::less<Key>;

 private:
 public:
  iterator find(const key_type &key) {
    iterator current = lower_bound(key);
    if ((*current).first == key) {
      return current;
    }
    return this->CreateIterator(this->_end);
  }

  pointer FindEqualNode(pointer current_node, const key_type &key) {
    if (current_node == this->_end || current_node == nullptr) {
      return nullptr;
    }
    if (Compare{}(key, current_node->_value.first)) {
      return FindEqualNode(current_node->_left, key);
    } else if (current_node->_value.first == key) {
      return current_node;
    }
    return FindEqualNode(current_node->_right, key);
  }

  iterator lower_bound(const key_type &key) {
    pointer current_node = this->FindFirstEqualOrNearPointer(key);
    iterator iter = this->CreateIterator(current_node);
    while (iter != this->_end) {
      if ((*iter).first == key) {
        --iter;
      } else {
        break;
      }
    }
    return ++iter;
  }

  iterator upper_bound(const key_type &key) {
    pointer current_node = this->FindFirstEqualOrNearPointer(key);
    iterator iter = this->CreateIterator(current_node);
    while (iter != this->_end) {
      if ((*iter).first <= key) {
        ++iter;
      } else {
        break;
      }
    }
    return iter;
  }

  bool contains(const key_type &key) {
    pointer current = FindEqualNode(this->_root, key);
    return current;
  }

  pointer FindFirstEqualOrNearPointer(const key_type &key) const noexcept {
    pointer current_node = this->_root;
    while (current_node != this->_end) {
      if (Compare{}(key, current_node->_value.first)) {
        if (current_node->_left != nullptr) {
          current_node = current_node->_left;
        } else {
          break;
        }
      } else if (key == current_node->_value.first) {
        return current_node;
      } else if (current_node->_right != nullptr &&
                 current_node->_right != this->_end) {
        current_node = current_node->_right;
      } else {
        break;
      }
    }
    return current_node;
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
    } else if (!FindEqualNode(this->_root, value.first)) {
      this->_root = this->InsertFromRoot(this->_root, value);
      ++this->_size;
      tmp.second = true;
    }
    iterator current = this->lower_bound(value.first);
    return {current, tmp.second};
  }

  std::pair<iterator, bool> insert(Key key, Value value) {
    std::pair<pointer, bool> tmp{};
    value_type pair_value{key, value};
    if (this->max_size() == this->_size) {
      throw std::overflow_error(
          "Can't insert new element, because size will over max_size");
    }
    if (this->_begin == this->_end) {
      this->_end->_parent = this->_begin = this->_root =
          new node_type(pair_value);
      this->_begin->_right = this->_end;
      ++this->_size;
      tmp.second = true;
    } else if (!FindEqualNode(this->_root, key)) {
      this->_root = this->InsertFromRoot(this->_root, pair_value);
      ++this->_size;
      tmp.second = true;
    }
    iterator current = this->lower_bound(key);
    return {current, tmp.second};
  }

  std::pair<iterator, bool> insert_or_assign(Key key, Value value) {
    std::pair<pointer, bool> tmp{};
    value_type pair_value{key, value};
    if (this->max_size() == this->_size) {
      throw std::overflow_error(
          "Can't insert new element, because size will over max_size");
    }
    if (this->_begin == this->_end) {
      this->_end->_parent = this->_begin = this->_root =
          new node_type(pair_value);
      this->_begin->_right = this->_end;
      ++this->_size;
      tmp.second = true;
    }
    pointer tmp_current = FindEqualNode(this->_root, key);
    if (tmp_current) {
      tmp_current->_value.second = value;
    } else {
      this->_root = this->InsertFromRoot(this->_root, pair_value);
      ++this->_size;
      tmp.second = true;
    }
    iterator current = this->lower_bound(key);
    return {current, tmp.second};
  }

  map() : BinaryTree<std::pair<Key, Value>>() {}

  map(const std::initializer_list<value_type> &items) {
    this->_begin = this->_root = this->_end = new node_type();
    this->_begin->_height = 0;
    for (value_type item : items) {
      insert(item);
    }
  }

  map(const map &s) : BinaryTree<std::pair<Key, Value>>(s) {}

  map(map &&s) {
    this->_size = std::exchange(s._size, 0);
    this->_root = s._root;
    this->_begin = s._begin;
    this->_end = s._end;
    s._begin = s._end = s._root = new node_type();
  }

  ~map() = default;

  map &operator=(map &&ms) {
    delete this->_root;
    this->_begin = ms._begin;
    this->_end = ms._end;
    this->_root = ms._root;
    this->_size = ms._size;
    ms._begin = ms._end = ms._root = new node_type();
    ms._size = 0;
    return *this;
  }

  void swap(map &other) {
    map tmp = std::move(other);
    other = std::move(*this);
    *this = std::move(tmp);
  }

  void merge(map &other) {
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

  mapped_type &at(const Key &key) {
    pointer current = FindEqualNode(this->_root, key);
    if (!current) {
      throw std::invalid_argument("No contain element in map");
    }
    return current->_value.second;
  }

  mapped_type &operator[](const Key &key) {
    pointer current = FindEqualNode(this->_root, key);
    if (!current) {
      insert(key, 0);
    }
    return at(key);
  }
};

// template<Pair>
// BinaryTree<Pair>::value_type &BinaryTree<Pair>::TreeIterator::operator*() {
//     return
// }

}  // namespace s21

#endif  // STL_CONTAINERS_MAP_H_
