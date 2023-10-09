#include <gtest/gtest.h>
#include <cmath>
#include <fstream>

#include "containers_boost.h"

TEST(matrix, default_constructor) {
  s21::matrix<double> basic;
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetColumns(), 0);
}

TEST(matrix, default_constructor_exception) {
  s21::matrix<double> basic(1, 0);
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetColumns(), 0);
}

TEST(matrix, parameterized_constructor) {
  s21::matrix<double> basic(2, 3);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(matrix, copy_constructor) {
  s21::matrix<double> basic(2, 3);
  s21::matrix<double> result(basic);
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetColumns(), 3);
  EXPECT_EQ(basic == result, true);
}

TEST(matrix, move_constructor) {
  s21::matrix<double> basic(2, 3);
  s21::matrix<double> result(std::move(basic));
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetColumns(), 3);
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetColumns(), 0);
}

TEST(matrix, set) {
  s21::matrix<double> basic(2, 3);
  basic(1, 1) = 2.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetColumns(), 3);
  basic.SetRows(4);
  basic(3, 2) = 1.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic(3, 2), 1.2);
  EXPECT_EQ(basic.GetRows(), 4);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(matrix, brakets) {
  s21::matrix<double> basic(2, 3);
  basic(1, 1) = 3;
  EXPECT_EQ(basic(1, 1), 3);
}

TEST(matrix, operator_quad_brakets) {
  s21::matrix<double> basic(2, 3);
  basic[1][1] = 3;
  EXPECT_EQ(basic(1, 1), 3);
}

TEST(matrix, brakets_exception) {
  s21::matrix<double> exception(2, 3);
  EXPECT_ANY_THROW(exception(1, 5));
}

TEST(matrix, braket_exception2) {
  s21::matrix<double> exception(1, 1);
  EXPECT_ANY_THROW(exception(5, 0) = 5);
}

TEST(matrix, set_zero_matrix) {
  s21::matrix<double> basic;
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetColumns(), 0);
}

TEST(matrix, iostreams) {
  s21::matrix<double> basic{3, 3};
  basic(2, 2) = 9.7;
  basic(1, 1) = 3.2;
  basic(0, 0) = 1.1;
  basic(0, 2) = 4.5;
  s21::matrix<double> basic2;
  const char path_matrix_stream[] = "matrix_stream_arrows.o";
  std::ofstream os{path_matrix_stream};
  os << basic;
  os.close();
  std::ifstream is{path_matrix_stream};
  is >> basic2;
  EXPECT_TRUE(basic == basic2);
  EXPECT_FALSE(basic != basic2);
}

TEST(matrix, serialize_deserialize_double) {
  s21::matrix<double> basic{3, 3};
  basic(2, 2) = 9.7;
  basic(1, 1) = 3.2;
  basic(0, 0) = 1.1;
  basic(0, 2) = 4.5;
  std::string serialize = basic.Serialize();
  std::cout << serialize << std::endl;
  s21::matrix<double> basic2;
  basic2.Deserialize(serialize);
  EXPECT_TRUE(basic == basic2);
  EXPECT_FALSE(basic != basic2);
}

TEST(matrix, serialize_deserialize_float) {
  s21::matrix<float> basic{3, 3};
  basic(2, 2) = 9.7;
  basic(1, 1) = 3.2;
  basic(0, 0) = 1.1;
  basic(0, 2) = 4.5;
  std::string serialize = basic.Serialize();
  std::cout << serialize << std::endl;
  s21::matrix<float> basic2;
  basic2.Deserialize(serialize);
  EXPECT_TRUE(basic == basic2);
  EXPECT_FALSE(basic != basic2);
}

TEST(matrix, serialize_deserialize_except_diff_type) {
  s21::matrix<double> basic{3, 3};
  basic(2, 2) = 9.7;
  basic(1, 1) = 3.2;
  basic(0, 0) = 1.1;
  basic(0, 2) = 4.5;
  std::string serialize = basic.Serialize();
  std::cout << serialize << std::endl;
  s21::matrix<float> basic2;
  EXPECT_ANY_THROW(basic2.Deserialize(serialize));
}

TEST(matrix, serialize_deserialize_except_diff_type2) {
  s21::matrix<float> basic{3, 3};
  basic(2, 2) = 9.7;
  basic(1, 1) = 3.2;
  basic(0, 0) = 1.1;
  basic(0, 2) = 4.5;
  std::string serialize = basic.Serialize();
  std::cout << serialize << std::endl;
  s21::matrix<double> basic2;
  EXPECT_ANY_THROW(basic2.Deserialize(serialize));
}

TEST(matrix, serialize_deserialize_except_empty) {
  std::string serialize;
  s21::matrix<double> basic;
  EXPECT_ANY_THROW(basic.Deserialize(serialize));
}

TEST(matrix, bad_minor) {
  s21::matrix<double> basic;
  EXPECT_ANY_THROW(basic.MinorMatrix(0, 0));
}

TEST(matrix, move_const) {
  s21::matrix<double> basic(2, 3);
  s21::matrix<double> basic2 = std::move(basic);
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetColumns(), 0);
  EXPECT_EQ(basic2.GetRows(), 2);
  EXPECT_EQ(basic2.GetColumns(), 3);
}

TEST(matrix, copy) {
  s21::matrix<double> a(2, 2);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a = b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(matrix, plus) {
  s21::matrix<double> a(2, 2);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  s21::matrix<double> result = a + b;
  EXPECT_DOUBLE_EQ(result(1, 1), 3.3);
}

TEST(matrix, plus2) {
  s21::matrix<double> a(2, 2);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a += b;
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(matrix, plus3) {
  s21::matrix<double> a(2, 2);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(matrix, plus_exception) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(s21::matrix<double> result = a + b);
}

TEST(matrix, plus_exception2) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a += b);
}

TEST(matrix, plus_exception3) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(matrix, minus) {
  s21::matrix<double> a(2, 2);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  s21::matrix<double> result = a - b;
  EXPECT_DOUBLE_EQ(result(1, 1), -1.1);
}

TEST(matrix, minus2) {
  s21::matrix<double> a(2, 2);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(matrix, minus3) {
  s21::matrix<double> a(2, 2);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(matrix, minus_exception) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(s21::matrix<double> result = a + b);
}

TEST(matrix, minus_exception2) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a -= b);
}

TEST(matrix, minus_exception3) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(matrix, minus_exception4) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a - b);
}

TEST(matrix, mult_matrix) {
  s21::matrix<double> a(3, 2);
  s21::matrix<double> b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  s21::matrix<double> result = a * b;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(matrix, mult_matrix2) {
  s21::matrix<double> a(3, 2);
  s21::matrix<double> b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(matrix, mult_matrix3) {
  s21::matrix<double> a(3, 2);
  s21::matrix<double> b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a.MulMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(matrix, mult_matrixTotal) {
  s21::matrix<double> a(3, 2);
  s21::matrix<double> b(2, 4);
  s21::matrix<double> res(3, 4);
  double value = 0;
  for (std::size_t i = 0; i < a.GetRows(); i++)
    for (std::size_t j = 0; j < a.GetColumns(); j++) a(i, j) = value++;
  value = 0;
  for (std::size_t i = 0; i < b.GetRows(); i++)
    for (std::size_t j = 0; j < b.GetColumns(); j++) b(i, j) = value++;

  res(0, 0) = 4, res(0, 1) = 5, res(0, 2) = 6, res(0, 3) = 7;
  res(1, 0) = 12, res(1, 1) = 17, res(1, 2) = 22, res(1, 3) = 27;
  res(2, 0) = 20, res(2, 1) = 29, res(2, 2) = 38, res(2, 3) = 47;

  s21::matrix<double> answer = a * b;
  EXPECT_TRUE(res == answer);
}

TEST(matrix, mult_matrix_exception) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(s21::matrix<double> result = a * b);
}

TEST(matrix, mult_matrix_exception2) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

TEST(matrix, mult_matrix_exception3) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(matrix, mult_matrixNum) {
  s21::matrix<double> a(3, 2);
  a(1, 1) = 1.1;
  s21::matrix<double> result = a * 2.;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(matrix, mult_matrixNum2) {
  s21::matrix<double> a(3, 2);
  a(1, 1) = 1.1;
  a *= 2;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(matrix, mult_matrixNum3) {
  s21::matrix<double> a(3, 2);
  a(1, 1) = 1.1;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(matrix, mult_matrixNum4) {
  s21::matrix<double> a(3, 2);
  a.MulNumber(NAN);
  EXPECT_TRUE(std::isnan(a(1, 1)));
  EXPECT_TRUE(std::isnan(a(2, 1)));
  EXPECT_TRUE(std::isnan(a(1, 0)));
}

TEST(matrix, equal) {
  s21::matrix<double> a(2, 3);
  s21::matrix<double> b(2, 2);
  EXPECT_EQ(a == b, false);
  b.SetColumns(3);
  a(1, 1) = 1.3;
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
  b(1, 2) = 1.3;
  EXPECT_EQ(a == b, false);
}

TEST(matrix, equal2) {
  s21::matrix<double> a(2, 2);
  s21::matrix<double> b(2, 2);
  EXPECT_EQ(a == b, true);
  a(1, 1) = 1.3;
  EXPECT_EQ(a == b, false);
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
}

TEST(matrix, determinant) {
  s21::matrix<double> basic(4, 4);
  basic(0, 0) = 9;
  basic(0, 1) = 2;
  basic(0, 2) = 2;
  basic(0, 3) = 4;

  basic(1, 0) = 3;
  basic(1, 1) = 4;
  basic(1, 2) = 4;
  basic(1, 3) = 4;

  basic(2, 0) = 4;
  basic(2, 1) = 4;
  basic(2, 2) = 9;
  basic(2, 3) = 9;

  basic(3, 0) = 1;
  basic(3, 1) = 1;
  basic(3, 2) = 5;
  basic(3, 3) = 1;
  EXPECT_DOUBLE_EQ(basic.Determinant(), -578);
}

TEST(matrix, determinant2) {
  s21::matrix<double> basic(1, 1);
  basic(0, 0) = 10;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 10);
}

TEST(matrix, determinant3) {
  s21::matrix<double> basic(2, 2);
  basic(0, 0) = 1.1;
  basic(0, 1) = 3.5;

  basic(1, 0) = -2;
  basic(1, 1) = 4;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 11.4);
}

TEST(matrix, determinantexception) {
  s21::matrix<double> exception(4, 3);
  EXPECT_ANY_THROW(exception.Determinant());
}

TEST(matrix, inverse_matrix) {
  s21::matrix<double> basic(3, 3);

  basic(0, 0) = 4;
  basic(0, 1) = -2;
  basic(0, 2) = 1;

  basic(1, 0) = 1;
  basic(1, 1) = 6;
  basic(1, 2) = -2;

  basic(2, 0) = 1;
  basic(2, 1) = 0;
  basic(2, 2) = 0;

  basic = basic.InverseMatrix();

  EXPECT_EQ(basic(0, 1), 0);
  EXPECT_EQ(basic(0, 2), 1);

  EXPECT_EQ(basic(1, 0), 1);
  EXPECT_EQ(basic(2, 0), 3);

  EXPECT_EQ(basic(2, 1), 1);
  EXPECT_EQ(basic(2, 2), -13);
}

TEST(matrix, inverse_matrix2) {
  s21::matrix<double> basic(3, 3);

  basic(0, 0) = 2;
  basic(0, 1) = 2;
  basic(0, 2) = 123;

  basic(1, 0) = 12;
  basic(1, 1) = 6;
  basic(1, 2) = 5;

  basic(2, 0) = 1;
  basic(2, 1) = 2;
  basic(2, 2) = 8;

  basic = basic.InverseMatrix();

  EXPECT_DOUBLE_EQ(basic(0, 1), 0.10910815939278938);
  EXPECT_DOUBLE_EQ(basic(0, 2), -0.34535104364326374);

  EXPECT_DOUBLE_EQ(basic(1, 0), -0.043168880455407968);
  EXPECT_DOUBLE_EQ(basic(2, 0), 0.0085388994307400382);

  EXPECT_DOUBLE_EQ(basic(2, 1), -0.00094876660341555979);
  EXPECT_DOUBLE_EQ(basic(2, 2), -0.0056925996204933585);
}

TEST(matrix, inverse_matrixexception) {
  s21::matrix<double> exception(3, 3);

  //  determ = 0
  exception(0, 0) = 1;
  exception(0, 1) = 1;
  exception(0, 2) = 3;
  exception(1, 0) = 4;
  exception(1, 1) = 4;
  exception(1, 2) = 6;
  exception(2, 0) = 4;
  exception(2, 1) = 4;
  exception(2, 2) = 9;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(matrix, inverse_matrixexception2) {
  s21::matrix<double> exception(3, 3);

  exception(0, 0) = 1;
  exception(0, 1) = 4;
  exception(0, 2) = 1;
  exception(1, 0) = 3;
  exception(1, 1) = 7;
  exception(1, 2) = 2;
  exception(2, 0) = 3;
  exception(2, 1) = 2;
  exception(2, 2) = 1;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(matrix, inverse_matrixexception3) {
  s21::matrix<double> exception(3, 2);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(matrix, transpose) {
  s21::matrix<double> result(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;
  result = result.Transpose();

  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 3);
}

TEST(matrix, calc_complements) {
  s21::matrix<double> result(2, 2);
  s21::matrix<double> another(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;

  another(0, 0) = 1;
  another(0, 1) = 2;
  another(1, 0) = 13;
  another(1, 1) = 7;

  result -= another * result;
  result = result.CalcComplements();

  EXPECT_EQ(result(0, 0), -44);
  EXPECT_EQ(result(0, 1), 37);
  EXPECT_EQ(result(1, 0), 6);
  EXPECT_EQ(result(1, 1), -8);
}

TEST(matrix, calc_complementsexception) {
  s21::matrix<double> exception(4, 3);
  EXPECT_ANY_THROW(exception.CalcComplements().GetRows());
}

TEST(matrix, operators_over) {
  s21::matrix<double> m1(1, 1);
  m1(0, 0) = 2;
  double num = 2;
  s21::matrix<double> res = num * m1;
  s21::matrix<double> res2 = m1 * num;
  s21::matrix<double> res3 = res * res2;
  EXPECT_EQ(res(0, 0), 4);
  EXPECT_EQ(res2(0, 0), 4);
  EXPECT_EQ(res3(0, 0), 16);
}