#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(set, default_constructor) {
  s21::set<int> basic;
  basic.insert(5);
  basic.insert(20);
  basic.insert(2);
  int s[3] = {2, 5, 20};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(set, initializator_oper_constructor_int) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(set, initializator_constructor_int) {
  s21::set<int> basic{6, 4, 2, 8, 0, -228};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(set, initializator_constructor_double) {
  s21::set<double> basic = {999, 6, 3, 2, 90, 0, -1};
  double s[7] = {-1, 0, 2, 3, 6, 90, 999};
  double *a = s;
  for (const double &item : basic) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
}

TEST(set, initializator_constructor_char) {
  s21::set<char> basic = {'c', 'd', 'a', 'b'};
  char s[4] = {'a', 'b', 'c', 'd'};
  char *a = s;
  for (const char &item : basic) {
    EXPECT_TRUE(item == *a++);
  }
}

TEST(set, copy_constructor_int) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  EXPECT_EQ(basic.size(), 6);
  s21::set<int> copy{basic};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : copy) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic.size(), 6);
  EXPECT_EQ(basic.size(), copy.size());
}

TEST(set, move_constructor_int) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  s21::set<int> move{std::move(basic)};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : move) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic.size(), 0);
  EXPECT_EQ(move.size(), 6);
}

TEST(set, move_operator_int) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  s21::set<int> move = std::move(basic);
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : move) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic.size(), 0);
  EXPECT_EQ(move.size(), 6);
}

TEST(set, iterator_begin_end) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  auto iter = basic.begin();
  auto iter_end = basic.end();
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  while (iter != iter_end) {
    EXPECT_EQ(*iter++, *a++);
  }
  EXPECT_EQ(basic.size(), 6);
}

TEST(set, empty_size) {
  s21::set<int> basic;
  EXPECT_TRUE(basic.empty());
  EXPECT_EQ(basic.size(), 0);
  basic.insert(4);
  EXPECT_EQ(basic.size(), 1);
  EXPECT_FALSE(basic.empty());
}

TEST(set, empty_erase) {
  s21::set<int> basic;
  EXPECT_TRUE(basic.empty());
  basic.insert(4);
  EXPECT_FALSE(basic.empty());
  basic.erase(basic.find(4));
  EXPECT_TRUE(basic.empty());
}

TEST(set, insert) {
  s21::set<int> basic;
  std::pair<s21::set<int>::iterator, bool> pair = basic.insert(5);
  EXPECT_EQ(*pair.first, 5);
  EXPECT_TRUE(pair.second);
  std::pair<s21::set<int>::iterator, bool> pair2 = basic.insert(5);
  EXPECT_EQ(*pair2.first, 5);
  EXPECT_FALSE(pair2.second);
  basic.insert(20);
  basic.insert(2);
  int s[3] = {2, 5, 20};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(set, empty_clear) {
  s21::set<int> basic;
  EXPECT_TRUE(basic.empty());
  basic.insert(4);
  EXPECT_FALSE(basic.empty());
  basic.clear();
  EXPECT_TRUE(basic.empty());
}

TEST(set, size_clear) {
  s21::set<int> basic{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(basic.size(), 6);
  basic.insert(4);
  basic.insert(7);
  EXPECT_EQ(basic.size(), 7);
  basic.clear();
  EXPECT_EQ(basic.size(), 0);
}

TEST(set, max_size) {
  s21::set<double> basic1{1, 2, 3};
  s21::set<__int128> basic2{1, 2, 3, 4};
  s21::set<char> basic3;
  EXPECT_EQ(basic1.max_size(), 230584300921369395);
  EXPECT_EQ(basic2.max_size(), 192153584101141162);
  EXPECT_EQ(basic3.max_size(), 230584300921369395);
}

TEST(set, swap_int) {
  s21::set<int> basic1{1, 2, 3};
  s21::set<int> basic2{1, 2, 3, 4};
  EXPECT_EQ(basic1.size(), 3);
  EXPECT_EQ(basic2.size(), 4);
  int s1[3] = {1, 2, 3};
  int s2[4] = {1, 2, 3, 4};
  int *a = s1;
  for (const int &item : basic1) {
    EXPECT_EQ(item, *a++);
  }
  a = s2;
  for (const int &item : basic2) {
    EXPECT_EQ(item, *a++);
  }
  basic1.swap(basic2);
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 3);
  a = s1;
  for (const int &item : basic2) {
    EXPECT_EQ(item, *a++);
  }
  a = s2;
  for (const int &item : basic1) {
    EXPECT_EQ(item, *a++);
  }
}
TEST(set, swap_double) {
  s21::set<double> basic1{78, 23, -9};
  s21::set<double> basic2{55, 22, -8, -0.5};
  EXPECT_EQ(basic1.size(), 3);
  EXPECT_EQ(basic2.size(), 4);
  double s1[3] = {-9, 23, 78};
  double s2[4] = {-8, -0.5, 22, 55};
  double *a = s1;
  for (const double &item : basic1) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  a = s2;
  for (const double &item : basic2) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  basic1.swap(basic2);
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 3);
  a = s1;
  for (const double &item : basic2) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  a = s2;
  for (const double &item : basic1) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
}

TEST(set, merge_double) {
  s21::set<double> basic1{78, 23, -9, -8, -0.5};
  s21::set<double> basic2{55, 22, -8, -0.5};
  EXPECT_EQ(basic1.size(), 5);
  EXPECT_EQ(basic2.size(), 4);
  basic1.merge(basic2);
  double s1[7] = {-9, -8, -0.5, 22, 23, 55, 78};
  double *a = s1;
  for (const double &item : basic1) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic2.size(), 2);
}

TEST(set, merge_char) {
  s21::set<char> basic1{78, 23, -9, -8};
  s21::set<char> basic2{55, 22, -8, 0};
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 4);
  basic1.merge(basic2);
  char s1[7] = {-9, -8, 0, 22, 23, 55, 78};
  char *a = s1;
  for (const char &item : basic1) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic2.size(), 1);
}

TEST(set, iterator_find) {
  s21::set<double> basic1{78, 23, -9, 22, 22, 22, 23};
  EXPECT_EQ(basic1.size(), 4);
  auto iter_22 = basic1.find(22);
  EXPECT_DOUBLE_EQ(*iter_22, 22);
  EXPECT_DOUBLE_EQ(*++iter_22, 23);
  EXPECT_DOUBLE_EQ(*++iter_22, 78);
}

TEST(set, iterator_find2) {
  s21::set<double> basic1{78, 7.75, -9, -999, -8, 0.5, 2.88};
  EXPECT_EQ(basic1.size(), 7);
  auto iter_22 = basic1.find(-9);
  EXPECT_DOUBLE_EQ(*iter_22, -9);
  EXPECT_DOUBLE_EQ(*++iter_22, -8);
  EXPECT_DOUBLE_EQ(*++iter_22, 0.5);
  EXPECT_DOUBLE_EQ(*++iter_22, 2.88);
  EXPECT_DOUBLE_EQ(*++iter_22, 7.75);
}

TEST(set, contains_int) {
  s21::set<int> basic1{78, 7, -9, -999, -8, 0, 2};
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_TRUE(basic1.contains(-9));
  EXPECT_TRUE(basic1.contains(-999));
  EXPECT_TRUE(basic1.contains(0));
  EXPECT_FALSE(basic1.contains(-33));
  EXPECT_FALSE(basic1.contains(77));
  EXPECT_FALSE(basic1.contains(-98));
}

TEST(set, lower_bound_and_upper_bound) {
  s21::set<int> basic1{782, 7, -9, -999, -8, 7, 2, 32};
  EXPECT_EQ(basic1.size(), 7);
  std::pair<s21::set<int>::iterator, s21::set<int>::iterator> pair = {
      basic1.lower_bound(-9), basic1.upper_bound(32)};
  char s1[5] = {-9, -8, 2, 7, 32};
  char *a = s1;
  int size = 0;
  while (pair.first != pair.second) {
    ++size;
    EXPECT_EQ(*pair.first, *a++);
    ++pair.first;
  }
  EXPECT_EQ(size, 5);
  EXPECT_EQ(basic1.size(), 7);
}

TEST(set, lower_bound_and_upper_bound2) {
  s21::set<int> basic1{782, 7, -9, -999, -8, 7, 2, 32};
  EXPECT_EQ(basic1.size(), 7);
  std::pair<s21::set<int>::iterator, s21::set<int>::iterator> pair = {
      basic1.lower_bound(-9), basic1.upper_bound(6)};
  char s1[3] = {-9, -8, 2};
  char *a = s1;
  int size = 0;
  while (pair.first != pair.second) {
    ++size;
    EXPECT_EQ(*pair.first, *a++);
    ++pair.first;
  }
  EXPECT_EQ(size, 3);
  EXPECT_EQ(basic1.size(), 7);
}

TEST(set, emplace_basic) {
  s21::set<int> basic;
  basic.emplace(1, 3, 4, 4);
  EXPECT_TRUE(basic.contains(1));
  EXPECT_TRUE(basic.contains(3));
}

TEST(set, clear2) {
  s21::set<int> set = {1, 2, 3, 4};
  set.clear();
  set.clear();
  s21::set<int> set2;
  set2.clear();
  set2.clear();
}
