#ifndef BOOST_CONTAINERS_MATRIX_H_
#define BOOST_CONTAINERS_MATRIX_H_ 1

#include <algorithm>
#include <iostream>

namespace s21 {

template <class T>
class matrix {
  static_assert(std::is_arithmetic<T>(),
                "matrix template type must be arithmetic");

 public:
  using size_type = uint64_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;

  matrix();
  matrix(size_type rows, size_type columns);
  matrix(const matrix &other);
  matrix(matrix &&other);

  matrix &operator=(const matrix &other);
  matrix &operator=(matrix &&other);

  matrix &operator*=(T value);
  matrix &operator*=(const matrix &other);
  matrix &operator+=(const matrix &other);
  matrix &operator-=(const matrix &other);

  ~matrix();

  T &operator()(size_type rows, size_type columns) const;
  T* operator[](size_type rows) const;

  size_type GetColumns() const noexcept;
  size_type GetRows() const noexcept;
  size_type Size() const noexcept;

  void Set(size_type rows, size_type columns);
  void SetRows(size_type rows);
  void SetColumns(size_type columns);

  bool EqMatrix(const matrix &other) const;

  void SumMatrix(const matrix &other);
  void SubMatrix(const matrix &other);
  void MulNumber(T value);
  void MulMatrix(const matrix &other);

  matrix Transpose() const;
  matrix MinorMatrix(size_type discard_row, size_type discard_column) const;
  matrix CalcComplements() const;
  T Determinant() const;
  matrix InverseMatrix() const;

  std::string Serialize() const;
  void Deserialize(const std::string&);

 private:
  void CheckEqSize(const matrix &other) const;
  void AllocMemory();

  size_type rows_, columns_;
  T **matrix_;
};

template <class T>
matrix<T>::matrix() : rows_(0), columns_(0), matrix_(nullptr) {
}

template <class T>
matrix<T>::matrix(const size_type rows, const size_type columns)
    : rows_(rows), columns_(columns), matrix_(nullptr) {
  AllocMemory();
}

template <class T>
matrix<T>::matrix(const matrix<T> &other)
    : rows_(other.rows_), columns_(other.columns_) {
  AllocMemory();
  memcpy(matrix_[0], other.matrix_[0], Size() * sizeof(T));
}

template <class T>
matrix<T>::matrix(matrix<T> &&other)
    : rows_(std::exchange(other.rows_, 0)),
      columns_(std::exchange(other.columns_, 0)),
      matrix_(std::exchange(other.matrix_, nullptr)) {
}

template <class T>
matrix<T>::~matrix() {
  if (matrix_) {
    delete[] matrix_[0];
  }
  delete[] matrix_;
}

template <class T>
typename matrix<T>::size_type matrix<T>::GetColumns() const noexcept {
  return columns_;
}

template <class T>
typename matrix<T>::size_type matrix<T>::GetRows() const noexcept {
  return rows_;
}

template <class T>
typename matrix<T>::size_type matrix<T>::Size() const noexcept {
  return columns_ * rows_;
}

template <class T>
void matrix<T>::Set(const size_type rows, const size_type columns) {
  matrix<T> temp(rows, columns);
  for (size_type row = 0; row < std::min(rows_, rows); ++row) {
    for (size_type column = 0; column < std::min(columns_, columns);
         ++column) {
      temp.matrix_[row][column] = matrix_[row][column];
    }
  }
  *this = std::move(temp);
}

template <class T>
void matrix<T>::SetRows(const size_type rows) {
  Set(rows, columns_);
}

template <class T>
void matrix<T>::SetColumns(const size_type columns) {
  Set(rows_, columns);
}

template <class T>
T &matrix<T>::operator()(const size_type rows,
                         const size_type columns) const {
  if (rows >= rows_ || columns >= columns_) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[rows][columns];
}

template <class T>
T* matrix<T>::operator[](const size_type rows) const {
  return matrix_[rows];
}

template <class T>
matrix<T> &matrix<T>::operator+=(const matrix<T> &other) {
  return SumMatrix(other), *this;
}

template <class T>
matrix<T> &matrix<T>::operator*=(const matrix<T> &other) {
  return MulMatrix(other), *this;
}

template <class T>
matrix<T> &matrix<T>::operator*=(const T value) {
  return MulNumber(value), *this;
}

template <class T>
matrix<T> &matrix<T>::operator-=(const matrix<T> &other) {
  return SubMatrix(other), *this;
}

template <class T>
matrix<T> &matrix<T>::operator=(const matrix<T> &other) {
  if (this != &other) {
    matrix<T> temp(other);
    *this = std::move(temp);
  }
  return *this;
}

template <class T>
matrix<T> &matrix<T>::operator=(matrix<T> &&other) {
  if (this != &other) {
    this->~matrix();
    rows_ = std::exchange(other.rows_, 3);
    columns_ = std::exchange(other.columns_, 3);
    matrix_ = std::exchange(other.matrix_, nullptr);
    other.AllocMemory();
  }
  return *this;
}

template <class T>
bool matrix<T>::EqMatrix(const matrix<T> &other) const {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    return false;
  }
  for (typename matrix<T>::size_type i = 0, max_index = Size(); i < max_index; ++i) {
    if (matrix_[0][i] != other.matrix_[0][i]) {
      return false;
    }
  }
  return true;
}

template <class T>
void matrix<T>::SumMatrix(const matrix<T> &other) {
  CheckEqSize(other);
  for (typename matrix<T>::size_type i = 0, max_index = Size(); i < max_index; ++i) {
    if (matrix_[0][i] != matrix_[0][i] || other.matrix_[0][i] != other.matrix_[0][i]) {
      (void)2;
    }
    matrix_[0][i] += other.matrix_[0][i];
    if (matrix_[0][i] != matrix_[0][i] || other.matrix_[0][i] != other.matrix_[0][i]) {
      (void)2;
    }
  }
}

template <class T>
void matrix<T>::SubMatrix(const matrix<T> &other) {
  CheckEqSize(other);
  for (typename matrix<T>::size_type i = 0, max_index = Size(); i < max_index; ++i) {
    matrix_[0][i] -= other.matrix_[0][i];
  }
}

template <class T>
void matrix<T>::MulNumber(const T value) {
  for (typename matrix<T>::size_type i = 0, max_index = Size(); i < max_index; ++i) {
    matrix_[0][i] *= value;
  }
}

template <class T>
void matrix<T>::MulMatrix(const matrix<T> &other) {
  if (columns_ != other.rows_) {
    throw std::invalid_argument(
        "Wrong matrix, different Size first matrix "
        "columns and second matrix rows");
  }

  const size_type half = columns_ >> 1;
  std::vector<T> row_factor(rows_);
  std::vector<T> column_factor(other.columns_);
  for (size_type i = 0; i < rows_; ++i) {
    for (size_type j = 0; j < half; ++j) {
      const size_type shift = (j << 1);
      row_factor[i] += matrix_[i][shift] * matrix_[i][shift + 1];
    }
  }
  for (size_type i = 0; i < other.columns_; ++i) {
    for (size_type j = 0; j < half; ++j) {
      const size_type shift = (j << 1);
      column_factor[i] += other.matrix_[shift][i] * other.matrix_[shift + 1][i];
    }
  }

  matrix<T> result{rows_, other.columns_};

  for (size_type i = 0; i < rows_; ++i) {
    for (size_type j = 0; j < other.columns_; ++j) {
      result(i, j) = -row_factor[i] - column_factor[j];
      for (size_type k = 0; k < half; ++k) {
        const size_type shift = (k << 1);
        result.matrix_[i][j] += (matrix_[i][shift] + other.matrix_[shift + 1][j]) *
                                (matrix_[i][shift + 1] + other.matrix_[shift][j]);
      }
    }
  }

  if (columns_ % 2 == 1) {
    for (size_type i = 0; i < rows_; ++i) {
      for (size_type j = 0; j < other.columns_; ++j) {
        result.matrix_[i][j] +=
            matrix_[i][columns_ - 1] * other.matrix_[columns_ - 1][j];
      }
    }
  }

  *this = std::move(result);
}

template <class T>
[[nodiscard]] matrix<T> matrix<T>::Transpose() const {
  matrix<T> result(columns_, rows_);
  for (size_type i = 0; i < rows_; ++i) {
    for (size_type j = 0; j < columns_; ++j) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

template <class T>
[[nodiscard]] matrix<T> matrix<T>::MinorMatrix(
    const size_type discard_row, const size_type discard_column) const {
  if (rows_ <= 1 || columns_ <= 1 || discard_row >= rows_ ||
      discard_column >= columns_) {
    throw std::invalid_argument("Invalid argument, impossible minor matrix");
  }
  matrix<T> result(rows_ - 1, columns_ - 1);
  for (size_type i = 0, index_row = 0; i < rows_; ++i) {
    for (size_type j = 0, index_column = 0; j < columns_; ++j) {
      if (i == discard_row || j == discard_column) continue;
      result(index_row, index_column++) = matrix_[i][j];
    }
    if (i != discard_row) {
      index_row++;
    }
  }
  return result;
}

template <class T>
[[nodiscard]] matrix<T> matrix<T>::CalcComplements() const {
  if (rows_ != columns_ || rows_ < 2) {
    throw std::invalid_argument(
        "Impossible calc complements, matrix is not square");
  }
  matrix<T> result(rows_, columns_);
  for (size_type i = 0; i < rows_; ++i) {
    for (size_type j = 0; j < columns_; ++j) {
      result.matrix_[i][j] =
          MinorMatrix(i, j).Determinant() * (((i + j) % 2) == 0 ? 1 : -1);
    }
  }
  return result;
}

template <class T>
T matrix<T>::Determinant() const {
  if (rows_ != columns_) {
    throw std::invalid_argument(
        "Impossible determinant matrix, matrix is not square");
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  } else if (rows_ == 2) {
    return matrix_[0][0] * matrix_[0][3] - matrix_[0][1] * matrix_[0][2];
  }
  T determinant = 0.0;
  for (size_type j = 0; j < rows_; ++j) {
    determinant += matrix_[0][j] * MinorMatrix(0, j).Determinant() *
                   ((j % 2) == 0 ? 1 : -1);
  }
  return determinant;
}

template <class T>
[[nodiscard]] matrix<T> matrix<T>::InverseMatrix() const {
  T det = Determinant();
  if (fabs(det) < 1e-6) {
    throw std::invalid_argument("Impossible inverse matrix, determinant is 0");
  }
  matrix<T> temp = CalcComplements().Transpose();
  return temp *= 1. / det;
}

template <class T>
void matrix<T>::CheckEqSize(const matrix &other) const {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    throw std::invalid_argument("Wrong matrix, different Size");
  }
}

template <class T>
void matrix<T>::AllocMemory() {
  if ((rows_ == 0) || (columns_ == 0)) {
    rows_ = columns_ = 0, matrix_ = nullptr;
    return;
  }
  matrix_ = new T *[rows_];
  matrix_[0] = new T[Size()]{};
  for (size_type index = 1; index < rows_; ++index) {
    matrix_[index] = matrix_[index - 1] + columns_;
  }
}

template <class T>
std::string matrix<T>::Serialize() const {
  std::string data;
  data.reserve((Size() * sizeof(T)) + (sizeof(size_type) * 2));
  data.resize(data.capacity());
  *reinterpret_cast<size_type*>(data.data()) = rows_;
  *reinterpret_cast<size_type*>(data.data() + sizeof(size_type)) = columns_;
  memcpy(data.data() + (sizeof(size_type) * 2), matrix_[0], Size() * sizeof(T));
  return data;
}

template <class T>
void matrix<T>::Deserialize(const std::string &data) {
  if (data.size() < (sizeof(size_type) * 2)) {
    throw std::invalid_argument("matrix: Deserialize: String too short for matrix size.");
  }
  rows_ = *reinterpret_cast<const size_type*>(data.data());
  columns_ = *reinterpret_cast<const size_type*>(data.data() + sizeof(size_type));
  const size_type pull_without_size = data.size() - (sizeof(size_type) * 2);
  const bool is_mod = (pull_without_size % sizeof(T)) != 0;
  if (is_mod || ((pull_without_size / sizeof(T)) != Size())) {
    throw std::invalid_argument("matrix: Deserialize: Bad format string.");
  }
  AllocMemory();
  memcpy(matrix_[0], data.data() + (sizeof(size_type) * 2), Size() * sizeof(T));
}

template <class T>
[[nodiscard]] matrix<T> operator-(matrix<T> lhs, const matrix<T> &rhs) {
  return lhs -= rhs;
}

template <class T>
[[nodiscard]] matrix<T> operator+(matrix<T> lhs, const matrix<T> &rhs) {
  return lhs += rhs;
}

template <class T>
matrix<T> operator*(const T value, matrix<T> src) {
  return src *= value;
}

template <class T>
matrix<T> operator*(matrix<T> src, const T value) {
  return src *= value;
}

template <class T>
[[nodiscard]] matrix<T> operator*(matrix<T> lhs, const matrix<T> &rhs) {
  return lhs *= rhs;
}

template <class T>
bool operator==(const matrix<T> &lhs, const matrix<T> &rhs) {
  return lhs.EqMatrix(rhs);
}

template <class T>
bool operator!=(const matrix<T> &lhs, const matrix<T> &rhs) {
  return !lhs.EqMatrix(rhs);
}

template <class T>
std::ostream &operator<<(std::ostream &out, const matrix<T> matrix) {
  if (out.bad()) {
    return out;
  }
  out << matrix.GetRows() << ' ' << matrix.GetColumns() << '\n';
  for (typename ::s21::matrix<T>::size_type i = 0; i < matrix.GetRows(); ++i) {
    for (typename ::s21::matrix<T>::size_type j = 0; j < matrix.GetColumns(); ++j) {
      out << matrix[i][j] << ' ';
    }
    out << '\n';
  }
  return out;
}

template <class T>
std::istream &operator>>(std::istream &in, matrix<T> &matrix) {
  if (in.bad()) {
    return in;
  }
  typename ::s21::matrix<T>::size_type rows, cols;
  in >> rows >> cols;
  if (in.bad()) {
    return in;
  }
  ::s21::matrix<T> tmp{rows, cols};
  for (typename ::s21::matrix<T>::size_type i = 0; i < rows; ++i) {
    for (typename ::s21::matrix<T>::size_type j = 0; j < cols; ++j) {
      in >> tmp[i][j];
      if (in.bad()) {
        return in;
      }
    }
  }
  matrix = std::move(tmp);
  return in;
}

}  // namespace s21

#endif  // BOOST_CONTAINERS_MATRIX_H_
