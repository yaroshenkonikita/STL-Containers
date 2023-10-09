#ifndef STL_CONTAINERS_VECTOR_H_
#define STL_CONTAINERS_VECTOR_H_ 1

#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;
  using pointer = value_type *;

  //  Дефолтный конструктор
  vector() : arr_(nullptr), size_(0), capacity_(0) {}

  //  Конструктор с размером
  explicit vector(size_type size)
      : arr_(new value_type[size]), size_(size), capacity_(size) {}

  //  Конструктор списка инициализаторов
  vector(std::initializer_list<value_type> const &items)
      : arr_(nullptr), size_(0), capacity_(0) {
    reserve(items.size());
    for (value_type item : items) push_back(item);
  }

  //  Конструктор копирования
  vector(const vector &vector) : arr_(nullptr), size_(0), capacity_(0) {
    reserve(vector.capacity_);
    size_ = vector.size_;
    for (size_type i = 0; i < size_; i++) arr_[i] = vector.arr_[i];
  }

  //  Конструктор перемещения
  vector(vector &&vector) noexcept
      : arr_(vector.arr_), size_(vector.size_), capacity_(vector.capacity_) {
    vector.arr_ = nullptr;
    vector.size_ = 0;
    vector.capacity_ = 0;
  }

  //  Деструктор
  ~vector() { delete[] arr_; }

  //  Перегрузка оператора для перемещения объекта
  vector &operator=(vector &&vector) noexcept {
    if (this != &vector) {
      delete[] arr_;
      arr_ = vector.arr_;
      capacity_ = vector.capacity_;
      size_ = vector.size_;
      vector.arr_ = nullptr;
      vector.capacity_ = 0;
      vector.size_ = 0;
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
  iterator end() noexcept { return arr_ + size_; }

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
    size_++;
  }

  //  Удаляет последний элемент контейнера
  void pop_back() { --size_; }

  //  Меняет содержимое и вместимость контейнера с другими
  void swap(vector<value_type> &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    size_type current_pos = pos - arr_;
    for (auto element : {std::forward<Args>(args)...}) {
      iterator current = arr_ + current_pos++;
      insert(current++, element);
    }
    return arr_ + --current_pos;
  }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    emplace(end(), std::forward<Args>(args)...);
  }

 private:
  pointer arr_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif  // STL_CONTAINERS_VECTOR_H_
