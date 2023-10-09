#ifndef STL_CONTAINERS_ARRAY_H_
#define STL_CONTAINERS_ARRAY_H_ 1

#include <algorithm>         // для std::swap
#include <cstddef>           // для std::size_t
#include <initializer_list>  // для std::initializer_list

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  //  Дефолтный конструктор
  array() = default;

  //  Конструктор списка инициализаторов
  array(std::initializer_list<value_type> const &items) {
    auto iter = items.begin();
    for (std::size_t i = 0; i < N && iter != items.end(); ++i, ++iter) {
      arr_[i] = *iter;
    }
  }

  //  Конструктор копирования
  array(const array &arr) {
    for (size_type i = 0; i < N; i++) arr_[i] = arr.arr_[i];
  }

  //  Конструктор перемещения
  array(array &&arr) noexcept { std::move(arr.begin(), arr.end(), begin()); }

  //  Деструктор
  ~array() = default;

  //  Перегрузка оператора для перемещения объекта
  array &operator=(array &&arr) noexcept {
    std::move(arr.begin(), arr.end(), begin());
    return *this;
  }

  //  Оператор доступа к элементу с проверкой границ
  reference at(size_type pos) {
    if (pos >= N) throw std::out_of_range("Index out of range");
    return arr_[pos];
  }

  //  Возвращает ссылку на элемент в указанном месте
  reference operator[](size_type pos) { return at(pos); }

  //  Константный оператор доступа к первому элементу
  const_reference front() { return arr_[0]; }

  //  Константный оператор доступа к последнему элементу
  const_reference back() { return arr_[N - 1]; }

  //  Возвращает указатель на базовый массив
  iterator data() noexcept { return arr_; }

  //  Итерирование
  iterator begin() noexcept { return &arr_[0]; }
  const_iterator cbegin() const noexcept { return &arr_[0]; }
  iterator end() noexcept { return &arr_[N]; }
  const_iterator cend() const noexcept { return &arr_[N]; }

  //  Проверяет, нет ли в контейнере элементов
  bool empty() const noexcept { return N == 0; }

  //  Возвращает количество элементов в контейнере
  size_type size() const noexcept { return N; }

  //  Возвращает максимальное количество элементов, которые может содержать
  //  контейнер
  size_type max_size() const noexcept { return N; }

  //  Меняет содержимое и вместимость контейнера с другими в выбранном диапазоне
  void swap(array &other) { std::swap_ranges(begin(), end(), other.begin()); }

  //  Присваивает заданное значение value всем элементам в контейнере
  void fill(const_reference value) {
    for (std::size_t i = 0; i < N; i++) arr_[i] = value;
  }

 private:
  value_type arr_[N]{};
};
}  // namespace s21

#endif  // STL_CONTAINERS_ARRAY_H_
