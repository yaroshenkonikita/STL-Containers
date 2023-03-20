#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H

#include <functional>

#include "initializer_list"
#include "iostream"
#include "limits"
#include "list"
#include "utility"

namespace s21 {

template <typename T>
class list {
 public:
  /*__________________________________________________________________*/
  /* List Member type*/
  /*__________________________________________________________________*/
  class ListIterator;
  using iterator = ListIterator;
  class ListConstIterator;
  using const_iterator = ListConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  /*__________________________________________________________________*/
  /* CONSTRUCTORS AND DESTRUCTOR */
  /*__________________________________________________________________*/
  list();
  explicit list(size_type size);
  list(std::initializer_list<value_type> const &items);
  list(const list<value_type> &other);
  list(list<value_type> &&other) noexcept;
  ~list();
  /*__________________________________________________________________*/
  list<value_type> &operator=(list<value_type> &&other) noexcept;
  /*__________________________________________________________________*/
  /* PUBLIC METHODS */
  /*__________________________________________________________________*/
  void push_back(const_reference data);
  void push_front(const_reference data);
  void pop_front();
  void pop_back();
  const_reference front() {
    length_error();
    return head_->data;
  }
  const_reference back() {
    length_error();
    return tail_->data;
  }
  size_type size() { return size_list_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(node) / 2;
  }
  bool empty() { return size_list_ == 0; }
  void swap(list &other);
  void reverse();
  void unique();
  void sort();
  /*__________________________________________________________________*/
  /* Part 3. Bonus. Implementation of the modified emplace methods */
  /*__________________________________________________________________*/

  template <typename... Args>
  void emplace_back(Args &&...args) {
    emplace(end(), std::forward<Args>(args)...);
  }

  template <typename... Args>
  void emplace_front(Args &&...args) {
    emplace(begin(), std::forward<Args>(args)...);
  }
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator it(pos);
    for (auto element : {std::forward<Args>(args)...}) {
      insert(it, element);
    }
    return it--;
  }
  /*__________________________________________________________________*/
  // private:
  class node {
   public:
    node *next;
    node *prev;
    value_type data;
    explicit node(const_reference data = value_type(), node *next = nullptr,
                  node *prev = nullptr) {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }
  };
  class ListIterator {
   public:
    node *current;
    ListIterator() : current(nullptr){};
    explicit ListIterator(node *other) : current(other){};

    iterator operator++() noexcept {
      current = current->next;
      return *this;
    }

    iterator operator++(int) noexcept {
      ++*this;
      return *this;
    }

    iterator &operator--() noexcept {
      current = current->prev;
      return *this;
    }

    iterator operator--(int) noexcept {
      --*this;
      return *this;
    }

    value_type &operator*() { return current->data; }

    bool operator==(const iterator &other) const noexcept {
      return current->next == other.current->next;
    }
    bool operator!=(const iterator &other) const noexcept {
      return current->next != other.current->next;
    }
  };
  class ListConstIterator : public iterator {
   public:
    ListConstIterator() : iterator(){};
    ListConstIterator(iterator &it) : iterator(it.current){};
    ListConstIterator(iterator &&it) noexcept : iterator(it.current){};
    explicit ListConstIterator(node *other) : iterator(other){};

    value_type operator*() const noexcept {
      return (value_type)this->current->data;
    }
  };

  iterator begin() noexcept { return iterator(head_); }
  iterator end() noexcept { return iterator(end_); }

  iterator insert(iterator pos, const_reference value) {
    iterator it(begin());
    if (pos.current == head_) {
      push_front(value);
      it = begin();
    } else if (pos.current == tail_->next) {
      push_back(value);
      it.current = tail_;
    } else {
      while (it.current != pos.current->prev) {
        ++it;
      }
      node *new_node = new node(value, pos.current, it.current);
      it.current->next = new_node;
      pos.current->prev = new_node;
      size_list_++;
    }
    return it;
  }
  void erase(iterator pos) {
    if (pos == begin()) {
      pop_front();
    } else if (pos == end() || pos.current == tail_) {
      pop_back();
    } else {
      node *previous = pos.current->prev;
      node *next = pos.current->next;
      delete pos.current;
      previous->next = next;
      next->prev = previous;
      size_list_--;
    }
  }
  void splice(const_iterator pos, list &other) {
    if (pos == begin()) {
      iterator tmp(pos);
      head_ = other.head_;
      other.tail_->next = tmp.current;
      tmp.current->prev = other.tail_;
    } else if (pos == end()) {
      tail_->next = other.head_;
      other.head_->prev = tail_;
      tail_ = other.tail_;
    } else {
      iterator tmp(pos);
      iterator prev(pos.current->prev);

      prev.current->next = other.head_;
      other.head_->prev = prev.current;

      tmp.current->prev = other.tail_;
      other.tail_->next = tmp.current;
    }
    size_list_ += other.size_list_;
    other.head_ = other.tail_ = other.end_ = new node;
    other.size_list_ = 0;
  }
  void merge(list &other) {
    if (!empty()) {
      if (this != &other || !other.empty()) {
        auto this_begin = begin();
        auto other_begin = other.begin();
        auto this_end = end();
        auto other_end = other.end();

        while (this_begin != this_end && other_begin != other_end) {
          if (*this_begin <= *other_begin) {
            ++this_begin;
          } else {
            insert(this_begin, *other_begin);
            other.erase(other_begin);
            other_begin = other.begin();
            ++size_list_;
            --other.size_list_;
          }
        }
        splice(end(), other);
      }
    } else {
      *this = std::move(other);
    }
  }

 private:
  node *head_;
  node *tail_;
  node *end_;
  size_type size_list_;
  void length_error() {
    if (!size_list_) {
      throw std::length_error("list is empty");
    }
  }
  void clear();
};

template <typename value_type>
list<value_type> &list<value_type>::operator=(
    list<value_type> &&other) noexcept {
  if (this != &other) {
    clear();
    size_list_ = std::exchange(other.size_list_, 0);
    head_ = std::exchange(other.head_, nullptr);
    tail_ = std::exchange(other.tail_, nullptr);
    end_ = std::exchange(other.end_, nullptr);
    other.head_ = other.tail_ = other.end_ = new node();
  }
  return *this;
}

template <typename value_type>
list<value_type>::list(const list<value_type> &other) {
  size_list_ = 0;
  head_ = tail_ = end_ = new node();
  node *current_other = other.head_;
  while (current_other != other.end_) {
    push_back(current_other->data);
    current_other = current_other->next;
  }
}

template <typename value_type>
void list<value_type>::swap(list &other) {
  std::swap(size_list_, other.size_list_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(end_, other.end_);
}

template <typename value_type>
void list<value_type>::clear() {
  while (!empty()) {
    pop_front();
  }
  delete end_;
}

template <typename value_type>
void list<value_type>::push_front(const_reference data) {
  if (!size_list_) {
    node *current = new node(data, tail_, head_);
    tail_ = head_ = current;
    end_->next = head_;
    end_->prev = tail_;
  } else {
    node *current = new node(data, head_, end_);
    end_->next = current;
    head_->prev = current;
    head_ = current;
  }
  size_list_++;
}

template <typename value_type>
void list<value_type>::push_back(const_reference data) {
  if (!size_list_) {
    node *current = new node(data, tail_, head_);
    tail_ = head_ = current;
    end_->next = head_;
    end_->prev = tail_;
  } else {
    node *current = new node(data, end_, tail_);
    tail_->next = current;
    end_->prev = current;
    tail_ = current;
  }
  size_list_++;
}

template <typename value_type>
list<value_type>::list() {
  size_list_ = 0;
  head_ = tail_ = end_ = new node();
}

template <typename value_type>
list<value_type>::list(size_type size) {
  head_ = tail_ = end_ = new node();
  size_list_ = 0;
  if (size >= max_size()) {
    throw std::out_of_range("Limit of the container is exceeded");
  }
  for (size_type i = 0; i < size; i++) {
    push_front(value_type());
  }
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) {
  head_ = tail_ = end_ = new node();
  size_list_ = 0;
  for (value_type element : items) {
    push_back(element);
  }
}

template <typename value_type>
list<value_type>::list(list<value_type> &&other) noexcept {
  size_list_ = std::exchange(other.size_list_, 0);
  head_ = std::exchange(other.head_, nullptr);
  tail_ = std::exchange(other.tail_, nullptr);
  end_ = std::exchange(other.end_, nullptr);
  other.head_ = other.tail_ = other.end_ = new node();
}

template <typename value_type>
list<value_type>::~list() {
  clear();
}

template <typename value_type>
void list<value_type>::pop_front() {
  length_error();
  node *current = head_;
  head_ = head_->next;
  delete current;
  size_list_--;
  head_->prev = end_;
  end_->next = head_;
}

template <typename value_type>
void list<value_type>::pop_back() {
  length_error();
  node *current = tail_;
  tail_ = tail_->prev;
  delete current;
  size_list_--;
  tail_->next = end_;
  end_->prev = tail_;
}

template <typename value_type>
void list<value_type>::reverse() {
  auto current = head_;
  while (current != end_) {
    auto next_node = current->next;
    std::swap(current->next, current->prev);
    current = next_node;
  }
  std::swap(head_, tail_);
  head_->prev = end_;
  tail_->next = end_;
  end_->next = head_;
  end_->prev = tail_;
}

template <typename value_type>
void list<value_type>::unique() {
  iterator current = begin();
  iterator next(head_->next);
  while (next != end()) {
    if (*current == *next) {
      auto del = current;
      current++;
      next++;
      erase(del);
    } else {
      current++;
      next++;
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  if (!empty()) {
    for (iterator i(head_->next); i != end(); ++i) {
      iterator j(i.current->prev);
      iterator k(i.current);
      while (j.current->data > k.current->data) {
        std::swap(j.current->data, k.current->data);
        if (j == begin()) {
          break;
        } else {
          --k;
          --j;
        }
      }
    }
  }
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
