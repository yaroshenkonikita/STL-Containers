#include <gtest/gtest.h>

#include <vector>
#include "s21_vector.h"

TEST(constructors, defaultConstructor) {
  s21::vector<double> vector;
  EXPECT_EQ(0, vector.size());
}

TEST(constructors, parametrizedConstructor) {
  s21::vector<int> vector(4);
  vector.at(2) = 2;
  EXPECT_EQ(vector.at(2), 2);
  EXPECT_EQ(4, vector.size());
  EXPECT_EQ(4, vector.capacity());
  EXPECT_ANY_THROW(s21::vector<int> std(-4));
}

TEST(constructors, initializer) {
  std::vector<double> vector = {1, 2, 3, 4};
  s21::vector<double> std = {1, 2, 3, 4};
  for (size_t i = 0; i < vector.size(); i++) {
    EXPECT_EQ(vector[i], std[i]);
  }
  EXPECT_EQ(vector.size(), std.size());
//  EXPECT_EQ(vector.capacity(), std.capacity());
}

TEST(constructors, copyConstructor) {
  s21::vector<int> std = {1, 2, 3, 4};
  s21::vector<int> vector(std);
  for (size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ(vector.at(i), vector.at(i));
  }
}

TEST(constructors, moveConstructor) {
  s21::vector<int> vector = {1, 2, 3, 4};
  std::vector<int> std = {1, 2, 3, 4};
  s21::vector<int> vector1 = std::move(vector);
  std::vector<int> test = std::move(std);
  EXPECT_EQ(vector1.size(), test.size());
  for (size_t i = 0; i < vector1.size(); ++i)
    EXPECT_EQ(vector1.at(i), test.at(i));
}

TEST(constructors, moveOperator) {
  s21::vector<int> vector = {1, 2, 3, 4};
  s21::vector<int> vector1;
  std::vector<int> std_vector = {1, 2, 3, 4};
  std::vector<int> std_vector1;
  vector1 = std::move(vector);
  std_vector1 = std::move(std_vector);
  EXPECT_EQ(vector1.size(), std_vector1.size());
  EXPECT_EQ(vector1.capacity(), std_vector1.capacity());
}

TEST(elementAccess, at) {
  std::vector<int> v1 = {1, 2, 3, 4};
  s21::vector<int> v2 = {1, 2, 3, 4};
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v2.at(i));
  }
  EXPECT_ANY_THROW(v2.at(5));
  EXPECT_ANY_THROW(v2.at(5));
}

TEST(elementAccess, frontAndBack) {
  s21::vector<int> vector = {1, 2};
  std::vector<int> std = {1, 2};
  ASSERT_EQ(vector.front(), std.front());
  ASSERT_EQ(vector.back(), std.back());
}

TEST(elementAccess, data) {
  s21::vector<int> v;
  std::vector<double> vector = {1.21, 2, 3, 4};
  s21::vector<double> std = {1.21, 2, 3, 4};
  EXPECT_EQ(*vector.data(), *std.data());
  EXPECT_EQ(v.data(), nullptr);
}

TEST(iterators, begin) {
  std::vector<int> std = {1, 2, 3, 4};
  s21::vector<int> vector = {1, 2, 3, 4};
  EXPECT_EQ(*std.begin(), *vector.begin());
}

TEST(iterators, end) {
  std::vector<int> v1 = {1, 2, 3, 4};
  s21::vector<int> v2 = {1, 2, 3, 4};
  auto iter1 = v1.end();
  auto iter2 = v2.end();

  EXPECT_EQ(*(iter1 - 1), *(iter2 - 1));
}

TEST(capacity, empty) {
  std::vector<int> std = {1, 2, 3, 4};
  s21::vector<int> vector = {1, 2, 3, 4};
  EXPECT_EQ(std.empty(), vector.empty());
  std::vector<int> std1 = {};
  s21::vector<int> vector1 = {};
  EXPECT_EQ(std1.empty(), vector1.empty());
}

TEST(capacity, maxSize) {
  std::vector<int> v1 = {1, 2, 3, 4};
  s21::vector<int> v2 = {1, 2, 3, 4};
  EXPECT_EQ(v1.max_size(), v2.max_size());
}

TEST(capacity, reserve) {
  s21::vector<int> vector = {1, 2, 3, 4};
  std::vector<int> std = {1, 2, 3, 4};
  vector.reserve(10);
  std.reserve(10);
  ASSERT_EQ(vector.size(), std.size());
  ASSERT_EQ(vector.capacity(), std.capacity());
}

TEST(capacity, shrink_to_fit_test) {
  std::vector<int> std = {1, 2, 3, 4};
  s21::vector<int> vector = {1, 2, 3, 4};
  vector.shrink_to_fit();
  std.shrink_to_fit();
  EXPECT_EQ(vector.capacity(), std.capacity());
  EXPECT_EQ(vector.size(), std.size());
}

TEST(modifiers, clear) {
  s21::vector<int> vector = {1, 2, 3, 4};
  std::vector<int> std = {1, 2, 3, 4};
  vector.clear();
  std.clear();
  EXPECT_EQ(vector.capacity(), std.capacity());
  EXPECT_EQ(vector.size(), std.size());
}

TEST(modifiers, insert) {
  s21::vector<int> vector = {1, 2, 3, 4};
  std::vector<int> std = {1, 2, 3, 4};
  auto iter1 = vector.begin();
  auto iter2 = std.begin();
  vector.insert(iter1, 1);
  std.insert(iter2, 1);
  EXPECT_EQ(vector[4], std[4]);
  EXPECT_EQ(vector.capacity(), std.capacity());
  EXPECT_EQ(vector.size(), std.size());
}

TEST(modifiers, erase) {
  s21::vector<int> vector = {1, 2, 3, 4};
  std::vector<int> std = {1, 2, 3, 4};
  vector.erase(vector.begin());
  std.erase(std.begin());
  EXPECT_EQ(vector.capacity(), std.capacity());
  EXPECT_EQ(vector.size(), std.size());
}

TEST(modifiers, pop_back) {
  s21::vector<int> vector = {1, 2, 3, 4};
  std::vector<int> std = {1, 2, 3, 4};
  vector.pop_back();
  std.pop_back();
  EXPECT_EQ(vector.capacity(), std.capacity());
  EXPECT_EQ(vector.size(), std.size());
}

TEST(modifiers, swap) {
  std::vector<int> std1 = {4, 5, 6};
  std::vector<int> std2 = {1, 2, 3, 9};
  std1.swap(std2);
  s21::vector<int> vector1 = {4, 5, 6};
  s21::vector<int> vector2 = {1, 2, 3, 9};
  vector1.swap(vector2);

  for (size_t i = 0; i < 4; i++) {
    if (std1.size() > i) {
      EXPECT_EQ(std1.at(i), vector1.at(i));
    }
    if (std2.size() > i) {
      EXPECT_EQ(std2.at(i), vector2.at(i));
    }
  }
}

TEST(modifiers, push_back) {
  s21::vector<int> vector = {1, 2, 3, 4};
  std::vector<int> std = {1, 2, 3, 4};
  vector.push_back(5);
  std.push_back(5);
  EXPECT_EQ(vector.capacity(), std.capacity());
  EXPECT_EQ(vector.size(), std.size());
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}