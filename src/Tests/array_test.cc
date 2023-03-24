#include <gtest/gtest.h>

#include "../ContainersPlus/s21_array.h"

TEST(array, defaultConstructor) {
  s21::array<double, 0> arr;
  EXPECT_EQ(0, arr.size());
}

TEST(array, initializer) {
  std::array<double, 4> std = {1, 2, 3, 4};
  s21::array<double, 4> array = {1, 2, 3, 4};
  for (size_t i = 0; i < array.size(); i++) {
    EXPECT_EQ(array[i], std[i]);
  }
  EXPECT_EQ(array.size(), std.size());
}

TEST(array, copyConstructor) {
  s21::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array(std);
  for (size_t i = 0; i < array.size(); ++i) {
    EXPECT_EQ(array.at(i), array.at(i));
  }
}

TEST(array, moveConstructor) {
  s21::array<int, 4> array = {1, 2, 3, 4};
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array1 = std::move(array);
  std::array<int, 4> test = std::move(std);
  EXPECT_EQ(array1.size(), test.size());
  for (size_t i = 0; i < array1.size(); ++i)
    EXPECT_EQ(array1.at(i), test.at(i));
}

TEST(array, moveOperator) {
  s21::array<int, 4> array = {1, 2, 3, 4};
  s21::array<int, 4> array1;
  std::array<int, 4> std_array = {1, 2, 3, 4};
  std::array<int, 4> std_array1;
  array1 = std::move(array);
  std_array1 = std::move(std_array);
  EXPECT_EQ(array1.size(), std_array1.size());
}

TEST(array, at) {
  s21::array<int, 4> array = {1, 2, 3, 4};
  std::array<int, 4> std = {1, 2, 3, 4};
  for (size_t i = 0; i < array.size(); ++i) {
    EXPECT_EQ(array.at(i), std.at(i));
  }
  EXPECT_ANY_THROW(std.at(5));
  EXPECT_ANY_THROW(std.at(5));
}

TEST(array, frontAndBack) {
  s21::array<int, 4> array = {1, 2, 3, 4};
  std::array<int, 4> std = {1, 2, 3, 4};
  ASSERT_EQ(array.front(), std.front());
  ASSERT_EQ(array.back(), std.back());
}

TEST(array, data) {
  std::array<int, 4> array = {1, 2, 3, 4};
  s21::array<int, 4> std = {1, 2, 3, 4};
  EXPECT_EQ(*array.data(), *std.data());
}

TEST(array, begin) {
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array = {1, 2, 3, 4};
  EXPECT_EQ(*std.begin(), *array.begin());
}

TEST(array, cbegin) {
  std::array<int, 4> const std = {1, 2, 3, 4};
  s21::array<int, 4> const array = {1, 2, 3, 4};
  EXPECT_EQ(*std.cbegin(), *array.cbegin());
}

TEST(array, end) {
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array = {1, 2, 3, 4};
  auto it1 = std.end();
  auto it2 = array.end();
  it1--;
  it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST(array, cend) {
  std::array<int, 4> const std = {1, 2, 3, 4};
  s21::array<int, 4> const array = {1, 2, 3, 4};
  auto it1 = std.cend();
  auto it2 = array.cend();
  it1--;
  it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST(array, empty) {
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array = {1, 2, 3, 4};
  EXPECT_EQ(std.empty(), array.empty());
  std::array<int, 0> std1 = {};
  s21::array<int, 0> array1 = {};
  EXPECT_EQ(std1.empty(), array1.empty());
}

TEST(array, maxSize) {
  std::array<int, 4> std = {1, 2, 3, 4};
  s21::array<int, 4> array = {1, 2, 3, 4};
  EXPECT_EQ(array.max_size(), std.max_size());
}

TEST(array, swap) {
  s21::array<int, 4> array1 = {4, 5, 6};
  s21::array<int, 4> array2 = {1, 2, 3, 9};
  array1.swap(array2);
  std::array<int, 4> std1 = {4, 5, 6};
  std::array<int, 4> std2 = {1, 2, 3, 9};
  std1.swap(std2);
  for (size_t i = 0; i != array1.size(); ++i) {
    ASSERT_EQ(array1[i], std1[i]);
    ASSERT_EQ(array2[i], std2[i]);
  }
}

TEST(array, fill) {
  s21::array<int, 4> array;
  s21::array<int, 4> std;
  array.fill(1);
  std.fill(1);
  for (size_t i = 0; i != array.size(); ++i) {
    ASSERT_EQ(array[i], std[i]);
  }
}
