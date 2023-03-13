#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H

#include "initializer_list"
#include "iostream"
#include "limits"
#include "list"
#include "utility"
#include <functional>

namespace s21 {

template <typename T> class list {
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
  explicit list(size_type size); // explicit ???
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

  // private:
  class node {
  public:
    node *next;
    node *prev;
    value_type data;

    explicit node(value_type data = value_type(), node *next = nullptr,
                  node *prev = nullptr) { // explicit ???
      this->data = data;
      this->next = next;
      this->prev = prev;
    }
    explicit node(size_t data = size_t(), node *next = nullptr,
                  node *prev = nullptr) { // explicit ???
      this->data = data;
      this->next = next;
      this->prev = prev;
    }
    //    explicit node(const_reference value = const_reference(), node *next =
    //    nullptr,
    //                  node *prev = nullptr) { // explicit ???
    //      this->data = value;
    //      this->next = next;
    //      this->prev = prev;
    //    }
  };
  //  node *head_;
  //  node *tail_;
  //  size_type size_list_;
  class ListIterator {
  public:
    node *current;
    iterator operator++() noexcept {
      current = current->next;
      return *this;
    }

    // Postfix ++ overload
    iterator operator++(int) noexcept {
      iterator ListIterator = *this;
      ++*this;
      return ListIterator;
    }

    iterator &operator--() noexcept {
      if (current)
        current = current->prev;
      return *this;
    }

    iterator operator--(int) noexcept {
      iterator ListIterator = *this;
      --*this;
      return ListIterator;
    }

    value_type &operator*() const noexcept { return current->data; }

    bool operator==(const iterator &other) const noexcept {
      return current->next == other.current->next;
    }
    bool operator!=(const iterator &other) const noexcept {
      return current->next != other.current->next;
    }
    ListIterator() { current = this->head_; }
    explicit ListIterator(node *other) { current = other; }
  };
  //  class ListConstIterator {
  //  public:
  //    const node *current;
  //    const_iterator &operator++() noexcept {
  //      if (current)
  //        current = current->next;
  //      return *this;
  //    }
  //
  //    const_iterator operator++(int) noexcept {
  //      const_iterator ListIterator = *this;
  //      ++*this;
  //      return ListIterator;
  //    }
  //
  //    const_iterator &operator--() noexcept {
  //      if (current)
  //        current = current->prev;
  //      return *this;
  //    }
  //
  //    const_iterator operator--(int) noexcept {
  //      const_iterator ListIterator = *this;
  //      --*this;
  //      return ListIterator;
  //    }
  //
  //    const_reference operator*() const noexcept { return current->data; }
  //
  //    bool operator==(const const_iterator &other) const noexcept {
  //      return current->next == other.current->next;
  //    }
  //    bool operator!=(const const_iterator &other) const noexcept {
  //      return current->next != other.current->next;
  //    }
  //
  //    ListConstIterator() : current(nullptr){};
  //    ListConstIterator(ListIterator &it) : current(it.current){};
  //    ListConstIterator(ListIterator &&it) : current(it.current){};
  //    explicit ListConstIterator(const node *other) : current(other){};
  //  };
  iterator begin() noexcept { return iterator(head_); }
  const_iterator begin() const noexcept { return const_iterator(head_); }
  iterator end() noexcept {
    node *end_node = new node(size_list_, head_, tail_);
    tail_->next = end_node;
    head_->prev = end_node;
    return iterator(end_node);
  }

  iterator insert_iter(iterator pos, const_reference value) {
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
      // возможно тут есть ошибка, надо перепроверить
      node *new_node = new node(value, pos.current, it.current);
      it.current->next = new_node;
      pos.current->prev = new_node;
      size_list_++;
    }
    return it;
  }
  // если после использования, воспользоваться итератором - будет сега. В
  // оригинале также//
  void erase(iterator pos) {
    if (pos.current == head_) {
      pop_front();
    } else if (pos.current == tail_->next) {
      pop_back();
    } else {
      // возможно тут есть ошибка, надо перепроверить
      node *previous = pos.current->prev;
      node *to_delete = previous->next;
      previous->next = to_delete->next;
      pos.current->prev = to_delete->prev;
      size_list_--;
    }
  }
  void splice(iterator pos, list &other) {
    if (pos == begin()) {
      head_ = other.head_;

      other.tail_->next = pos.current;
      pos.current->prev = other.tail_;
    } else if (pos == end()) {
      tail_->next = other.head_;
      other.head_->prev = tail_;
      tail_ = other.tail_;
    } else {
      iterator prev(pos.current->prev);

      prev.current->next = other.head_;
      other.head_->prev = prev.current;

      pos.current->prev = other.tail_;
      other.tail_->next = pos.current;
    }
    size_list_ += other.size_list_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_list_ = 0;
  }
  //  void merge(list& other) {
  //
  //  }
  // мерж можно сделать через сплайс+сорт

private:
  node *head_;
  node *tail_;
  size_type size_list_;
  void length_error() {
    if (head_ == nullptr) {
      throw std::length_error("list is empty");
    }
  }
  void clear();
};

template <typename value_type>
list<value_type> &
list<value_type>::operator=(list<value_type> &&other) noexcept {
  if (this != &other) {
    clear();
    size_list_ = std::exchange(other.size_list_, 0);
    head_ = std::exchange(other.head_, nullptr);
    tail_ = std::exchange(other.tail_, nullptr);
  }
  return *this;
}
template <typename T> list<T>::list(const list<value_type> &other) {
  size_list_ = 0;
  head_ = tail_ = nullptr;
  node *current_other = other.head_;
  while (current_other != nullptr) {
    push_back(current_other->data);
    current_other = current_other->next;
  }
}

template <typename T> void list<T>::swap(list &other) {
  std::swap(size_list_, other.size_list_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

template <typename T> void list<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <typename value_type>
void list<value_type>::push_front(const_reference data) {
  node *current = new node(data);
  current->next = head_;
  current->prev = nullptr;
  if (head_ != nullptr) {
    head_->prev = current;
  }
  if (tail_ == nullptr) {
    tail_ = current;
  }
  head_ = current;
  size_list_++;
}

template <typename value_type>
void list<value_type>::push_back(const_reference data) {
  node *current = new node(data);
  if (tail_ != nullptr) {
    tail_->next = current;
  }
  current->next = nullptr;
  current->prev = tail_;
  if (head_ == nullptr) {
    head_ = current;
  }
  tail_ = current;
  size_list_++;
}

template <typename value_type> list<value_type>::list() {
  size_list_ = 0;
  head_ = tail_ = nullptr;
}

template <typename value_type> list<value_type>::list(size_type size) {
  head_ = tail_ = nullptr;
  size_list_ = 0;
  for (size_type i = 0; i < size; i++) {
    push_front(value_type());
  }
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) {
  head_ = tail_ = nullptr;
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
}

template <typename value_type> list<value_type>::~list() { clear(); }

template <typename value_type> void list<value_type>::pop_front() {
  length_error();
  node *current = head_;
  head_ = head_->next;
  delete current;
  size_list_--;
}

template <typename value_type> void list<value_type>::pop_back() {
  length_error();
  node *current = tail_;
  tail_ = tail_->prev;
  delete current;
  size_list_--;
}

template <typename T> void list<T>::reverse() {
  auto current = head_;
  while (current != nullptr) {
    auto next_node = current->next;
    std::swap(current->next, current->prev);
    current = next_node;
  }
  std::swap(head_, tail_);
}

template <typename T> void list<T>::unique() {
  auto current = begin();
  iterator next(head_->next);
  while (next != end()) {
    if (*current == *next) {
      auto del = current;
      current++;
      erase(del);
      next++;
    } else {
      current++;
      next++;
    }
  }
}

template <typename T> void list<T>::sort() {
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
} // namespace s21
#endif // CPP2_S21_CONTAINERS_0_SRC_S21_LIST_H
