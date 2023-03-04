#include <gtest/gtest.h>

#include "s21_array.h"

TEST(constructors, defaultConstructor) {
  s21::array<double, 0> arr;
  EXPECT_EQ(0, arr.size());
}

TEST(constructors, initializer) {
  std::array<double, 4> array = {1, 2, 3, 4};
  s21::array<double, 4> std = {1, 2, 3, 4};
  for (size_t i = 0; i < array.size(); i++) {
    EXPECT_EQ(array[i], std[i]);
  }
  EXPECT_EQ(array.size(), std.size());
}

TEST(constructors, copyConstructor) {
  s21::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array(std);
  for (size_t i = 0; i < array.size(); ++i) {
    EXPECT_EQ(array.at(i), array.at(i));
  }
}

TEST(constructors, moveConstructor) {
  s21::array<int, 4> array = {1, 2, 3, 4};
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array1 = std::move(array);
  std::array<int, 4> test = std::move(std);
  EXPECT_EQ(array1.size(), test.size());
  for (size_t i = 0; i < array1.size(); ++i)
    EXPECT_EQ(array1.at(i), test.at(i));
}

TEST(constructors, moveOperator) {
  s21::array<int, 4> array = {1, 2, 3, 4};
  s21::array<int, 4> array1;
  std::array<int, 4> std_array = {1, 2, 3, 4};
  std::array<int, 4> std_array1;
  array1 = std::move(array);
  std_array1 = std::move(std_array);
  EXPECT_EQ(array1.size(), std_array1.size());
}

TEST(elementAccess, at) {
  std::array<int, 4> v1 = {1, 2, 3, 4};
  s21::array<int, 4> v2 = {1, 2, 3, 4};
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v2.at(i));
  }
  EXPECT_ANY_THROW(v2.at(5));
  EXPECT_ANY_THROW(v2.at(5));
}

TEST(elementAccess, frontAndBack) {
  s21::array<int, 4> array = {1, 2};
  std::array<int, 4> std = {1, 2};
  ASSERT_EQ(array.front(), std.front());
  ASSERT_EQ(array.back(), std.back());
}

TEST(elementAccess, data) {
  s21::array<int, 0> v;
  std::array<double, 4> array = {1.21, 2, 3, 4};
  s21::array<double, 4> std = {1.21, 2, 3, 4};
  EXPECT_EQ(*array.data(), *std.data());
  EXPECT_EQ(v.data(), nullptr);
}

TEST(iterators, begin) {
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array = {1, 2, 3, 4};
  EXPECT_EQ(*std.begin(), *array.begin());
}

TEST(iterators, cbegin) {
  std::array<int, 4> const std = {1, 2, 3, 4};
  s21::array<int, 4> const array = {1, 2, 3, 4};
  EXPECT_EQ(*std.cbegin(), *array.cbegin());
}

TEST(iterators, end) {
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array = {1, 2, 3, 4};
  EXPECT_EQ(*(std.end()), *(array.end()));
}

TEST(iterators, cend) {
  std::array<int, 4> const std = {1, 2, 3, 4};
  s21::array<int, 4> const array = {1, 2, 3, 4};
  EXPECT_EQ(*(std.cend()), *(array.cend()));
}

TEST(capacity, empty) {
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array = {1, 2, 3, 4};
  EXPECT_EQ(std.empty(), array.empty());
  std::array<int, 0> std1 = {};
  s21::array<int, 0> array1 = {};
  EXPECT_EQ(std1.empty(), array1.empty());
}

TEST(capacity, maxSize) {
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array = {1, 2, 3, 4};
  EXPECT_EQ(array.max_size(), std.max_size());
}

TEST(modifiers, swap) {
  std::array<int, 4> std1 = {4, 5, 6};
  std::array<int, 4> std2 = {1, 2, 3, 9};
  std1.swap(std2);
  s21::array<int, 4> array1 = {4, 5, 6};
  s21::array<int, 4> array2 = {1, 2, 3, 9};
  array1.swap(array2);

  for (size_t i = 0; i < 4; i++) {
    if (std1.size() > i) {
      EXPECT_EQ(std1.at(i), array1.at(i));
    }
    if (std2.size() > i) {
      EXPECT_EQ(std2.at(i), array2.at(i));
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}