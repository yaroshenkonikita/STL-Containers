#ifndef CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H

#include "iostream"
#include "limits"

namespace s21 {
template <typename V>
class vector {
 public:
  using value_type = V;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = V *;
  using const_iterator = const V *;
  using size_type = size_t;
  using pointer = value_type *;

  //  Дефолтный конструктор
  vector() : arr_(nullptr), size_(0), capacity_(0) {}

  //  Параметризованный конструктор
  vector(size_type n) : arr_(nullptr), size_(0), capacity_(0) {
    reserve(n);
    size_ = n;
  }

  //  Конструктор списка инициализаторов
  vector(std::initializer_list<value_type> const &items)
      : arr_(nullptr), size_(0), capacity_(0) {
    reserve(items.size());
    for (value_type item : items) push_back(item);
  }

  //  Конструктор копирования
  vector(const vector &v) : arr_(nullptr), size_(0), capacity_(0) {
    reserve(v.capacity_);
    size_ = v.size_;
    for (size_type i = 0; i < size_; i++) arr_[i] = v.arr_[i];
  }

  //  Конструктор перемещения
  vector(vector &&v) noexcept
      : arr_(v.arr_), size_(v.size_), capacity_(v.capacity_) {
    v.arr_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

  //  Деструктор
  ~vector() { delete[] arr_; }

  //  Перегрузка оператора для перемещения объекта
  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] arr_;
      arr_ = v.arr_;
      capacity_ = v.capacity_;
      size_ = v.size_;
      v.arr_ = nullptr;
      v.capacity_ = 0;
      v.size_ = 0;
    }
    return *this;
  }

  //  Возвращает ссылку на элемент в указанном месте pos с проверкой границ
  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Out of range");
    return arr_[pos];
  }
  //  Возвращает ссылку на элемент в указанном месте
  reference operator[](size_type pos) { return at(pos); }

  //  Возвращает ссылку на первый элемент в контейнере
  reference front() { return arr_[0]; }

  //  Возвращает ссылку на последний элемент в контейнере
  reference back() { return arr_[size_ - 1]; }

  //  Возвращает указатель на базовый массив
  pointer data() noexcept { return arr_; }

  // Итерирование
  iterator begin() noexcept { return arr_; }
  const_iterator cbegin() const noexcept { return arr_; }
  iterator end() noexcept { return arr_ + size_; }
  const_iterator cend() const noexcept { return arr_ + size_; }

  //  Проверяет, нет ли в контейнере элементов
  bool empty() const noexcept { return size_ == 0; }

  //  Возвращает количество элементов в контейнере
  size_type size() const noexcept { return size_; }

  //  Возвращает максимальное количество элементов, которые может содержать
  //  контейнер
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  //  Увеличиваем емкость вектора до значения, которое больше или равно size
  void reserve(size_type size) {
    if (size > max_size()) throw std::length_error("Out of memory");
    if (size > capacity_) {
      value_type *new_data = new value_type[size];
      std::copy(arr_, arr_ + size_, new_data);
      delete[] arr_;
      arr_ = new_data;
      capacity_ = size;
    }
  }

  //  Возвращает количество элементов, для которых в данный момент выделено
  //  место в контейнере
  size_type capacity() const noexcept { return capacity_; }

  //  Запрашивает удаление неиспользуемой емкости
  void shrink_to_fit() {
    if (capacity_ > size_) {
      value_type *new_data = new value_type[size_];
      std::copy(arr_, arr_ + size_, new_data);
      delete[] arr_;
      arr_ = new_data;
      capacity_ = size_;
    }
  }

  //  Удаляет все элементы из контейнера
  void clear() noexcept { size_ = 0; }

  //  Вставляет элементы в указанное место в контейнере
  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - arr_;
    if (size_ == capacity_) {
      reserve(capacity_ * 2);
    }
    for (size_type i = size_; i > index; --i) {
      arr_[i] = arr_[i - 1];
    }
    arr_[index] = value;
    ++size_;
    return arr_ + index;
  }

  //  Удаляет указанные элементы из контейнера.
  void erase(iterator pos) {
    size_type index = pos - arr_;
    for (size_type i = index; i < size_ - 1; ++i) {
      arr_[i] = arr_[i + 1];
    }
    --size_;
  }

  //  Добавляет заданное значение элемента в конец контейнера
  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ * 2);
    }
    arr_[size_] = value;
    ++size_;
  }

  //  Удаляет последний элемент контейнера
  void pop_back() { --size_; }

  //  Меняет содержимое и вместимость контейнера с другими
  void swap(vector<value_type> &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

 private:
  pointer arr_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_S21_VECTOR_H