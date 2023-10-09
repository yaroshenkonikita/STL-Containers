#ifndef STL_CONTAINERS_MAP_H_
#define STL_CONTAINERS_MAP_H_ 1

#include "containers/set.h"

namespace s21 {

template <typename Key, typename Value, typename Compare = std::less<Key> >
struct ComparatorMap {
  bool operator()(const std::pair<Key, Value> &a, const std::pair<Key, Value> &b) const noexcept {
    return _compare(a.first, b.first);
  }
 private:
  Compare _compare;
};

template <typename Key, typename Value, typename Compare = std::less<Key> >
class map : public set<std::pair<Key, Value>, ComparatorMap<Key, Value, Compare> > {
  class MapIterator;
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<Key, Value>;
  using reference = value_type &;
  using const_reference = const value_type &;

  using size_type = std::size_t;
  using node_type = typename BinaryTree<std::pair<Key, Value>, ComparatorMap<Key, Value, Compare>>::node_type;
  using pointer = node_type *;
  using iterator = MapIterator;
  using const_iterator = const MapIterator;
  using set_typename = set<std::pair<Key, Value>, ComparatorMap<Key, Value, Compare> >;

  map() : set_typename() {}
  map(const std::initializer_list<value_type> &items) : set_typename(items) {}
  map(const map &other) : set_typename(other) {}
  map(map &&other) : set_typename(std::move(other)) {}
  ~map() = default;

  void erase(iterator pos);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  std::pair<iterator, iterator> equal_range(const key_type &key);
  iterator begin() const noexcept;
  iterator end() const noexcept;
  iterator find(const Key &key);
  std::pair<iterator, bool> insert(const Key &key, const Value &value);
  std::pair<iterator, bool> insert(const std::pair<Key, Value> &item);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const Value &value);
  bool contains(const Key &key);
  size_type count(const Key &key);
  mapped_type &at(const Key &key) const;
  mapped_type &operator[](const Key &key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool> > emplace(Args &&...args);
};

template <typename Key, typename Value, typename Compare>
class map<Key, Value, Compare>::MapIterator {
  friend class map<Key, Value, Compare>;
 public:
  MapIterator() noexcept = default;
  MapIterator(const MapIterator &other) noexcept
      : iterator(other.iterator) {}
  MapIterator(MapIterator &&other) noexcept
      : iterator(std::move(other.iterator)) {}
  MapIterator(const typename set_typename::iterator &other) noexcept
      : iterator(other.iterator) {}
  MapIterator(typename set_typename::iterator &&other) noexcept
      : iterator(std::move(other)) {}
  MapIterator& operator=(const MapIterator& other) noexcept {
    iterator = other.iterator;
    return *this;
  }
  MapIterator& operator=(MapIterator&& other) noexcept {
    iterator = std::exchange(other.iterator, typename set_typename::iterator{});
    return *this;
  }
  ~MapIterator() noexcept = default;

  std::pair<const Key&, Value&> operator*() noexcept {
    return std::make_pair(std::ref((*iterator).first),
                          std::ref(const_cast<Value&>((*iterator).second)));
  }

  std::pair<const Key&, const Value&> operator*() const noexcept {
    return std::make_pair(std::ref((*iterator).first),
                          std::ref((*iterator).second));
  }

  MapIterator operator++() const noexcept {
    ++iterator;
    return *this;
  }

  MapIterator operator++(int) const noexcept {
    map<Key, Value, Compare>::iterator it = *this;
    ++iterator;
    return it;
  }

  MapIterator operator--() const noexcept {
    --iterator;
    return *this;
  }

  MapIterator operator--(int) const noexcept {
    MapIterator it = *this;
    --iterator;
    return it;
  }

  bool operator!=(const MapIterator &other) const noexcept {
    return other.iterator != iterator;
  }

  bool operator==(const MapIterator &other) const noexcept {
    return other.iterator == iterator;
  }
 protected:
  typename set_typename::iterator iterator;
};

template <typename Key, typename Value, typename Compare>
void map<Key, Value, Compare>::erase(iterator pos) {
  set_typename::erase(pos.iterator);
}

template <typename Key, typename Value, typename Compare>
typename map<Key, Value, Compare>::iterator map<Key, Value, Compare>::lower_bound(const key_type &key) {
  return set_typename::lower_bound(std::make_pair(key, Value()));
}

template <typename Key, typename Value, typename Compare>
typename map<Key, Value, Compare>::iterator map<Key, Value, Compare>::upper_bound(const key_type &key) {
  return set_typename::upper_bound(std::make_pair(key, Value()));
}

template <typename Key, typename Value, typename Compare>
std::pair<typename map<Key, Value, Compare>::iterator, typename map<Key, Value, Compare>::iterator> map<Key, Value, Compare>::equal_range(const key_type &key) {
  return set_typename::equal_range(std::make_pair(key, Value()));
}

template <typename Key, typename Value, typename Compare>
typename map<Key, Value, Compare>::iterator map<Key, Value, Compare>::begin() const noexcept {
  return set_typename::begin();
}

template <typename Key, typename Value, typename Compare>
typename map<Key, Value, Compare>::iterator map<Key, Value, Compare>::end() const noexcept {
  return set_typename::end();
}

template <typename Key, typename Value, typename Compare>
typename map<Key, Value, Compare>::iterator map<Key, Value, Compare>::find(const Key &key) {
  return set_typename::find(std::make_pair(key, Value()));
}

template <typename Key, typename Value, typename Compare>
std::pair<typename map<Key, Value, Compare>::iterator, bool> map<Key, Value, Compare>::insert(const Key &key, const Value &value) {
  std::pair<iterator, bool> insert = set_typename::insert(std::make_pair(key, value));
  return std::make_pair(std::move(MapIterator(insert.first)), insert.second);
}

template <typename Key, typename Value, typename Compare>
std::pair<typename map<Key, Value, Compare>::iterator, bool> map<Key, Value, Compare>::insert(const std::pair<Key, Value> &item) {
  std::pair<iterator, bool> insrt = set_typename::insert(item);
  return std::make_pair(std::move(MapIterator(insrt.first)), insrt.second);
}

template <typename Key, typename Value, typename Compare>
std::pair<typename map<Key, Value, Compare>::iterator, bool> map<Key, Value, Compare>::insert_or_assign(const Key &key, const Value &value) {
  std::pair<iterator, bool> insrt = insert(key, value);
  if (!insrt.second) {
    (*insrt.first).second = value;
  }
  return insrt;
}

template <typename Key, typename Value, typename Compare>
bool map<Key, Value, Compare>::contains(const Key &key) {
  return set_typename::contains(std::make_pair(key, Value()));
}
  
template <typename Key, typename Value, typename Compare>
typename map<Key, Value, Compare>::size_type map<Key, Value, Compare>::count(const Key &key) {
  return set_typename::count(std::make_pair(key, Value()));
}

template <typename Key, typename Value, typename Compare>
typename map<Key, Value, Compare>::mapped_type &map<Key, Value, Compare>::at(const Key &key) const {
  typename set_typename::iterator current = set_typename::find(std::make_pair(key, Value()));
  if (current == end().iterator) {
    throw std::invalid_argument("Map: at: No contain element.");
  }
  return const_cast<Value&>((*current).second);
}

template <typename Key, typename Value, typename Compare>
typename map<Key, Value, Compare>::mapped_type &map<Key, Value, Compare>::operator[](const Key &key) {
  iterator iterator = find(key);
  if (iterator == end()) {
    iterator = insert(key, Value()).first;
  }
  return const_cast<Value&>((*iterator).second);
}

template <typename Key, typename Value, typename Compare>
template <typename... Args>
std::vector<std::pair<typename map<Key, Value, Compare>::iterator, bool> > map<Key, Value, Compare>::emplace(Args &&...args) {
  std::vector<std::pair<iterator, bool> > res;
  for (auto element : {std::forward<Args>(args)...}) {
    res.push_back(insert(element));
  }
  return res;
}

}  // namespace s21

#endif  // STL_CONTAINERS_MAP_H_
