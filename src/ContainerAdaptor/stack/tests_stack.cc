#include <gtest/gtest.h>

#include "s21_stack.h"

TEST(stack_test, move_constructor) {
  s21::stack<int> basic({1, 2, 3, 4});
  s21::stack<int> basic2(std::move(basic));
  EXPECT_TRUE(basic.empty());
  EXPECT_EQ(basic.size(), size_t(0));
  EXPECT_EQ(basic2.top(), 4);
  EXPECT_EQ(basic2.size(), size_t(4));
}

 TEST(stack_test, move_constructor_operator) {
   s21::stack<int> basic({1, 2, 3, 4});
   s21::stack<int> basic2;
   basic2 = std::move(basic);
   EXPECT_TRUE(basic.empty());
   EXPECT_EQ(basic2.top(), 4);
   EXPECT_EQ(basic2.size(), size_t(4));
 }

 TEST(stack_test, move_constructor_operator2) {
   s21::stack<std::string> basic({"hello","world"});
   s21::stack<std::string> basic2;
   basic2 = std::move(basic);
   EXPECT_TRUE(basic.empty());
   EXPECT_EQ(basic2.top(), "world");
   EXPECT_EQ(basic2.size(), size_t(2));
 }

 TEST(stack_test, move_constructor_operator3) {
   s21::stack<std::string> basic({"2","1"});
   s21::stack<std::string> basic2({"hello","world"});
   basic2 = std::move(basic);
   EXPECT_TRUE(basic.empty());
   EXPECT_EQ(basic2.top(), "1");
   EXPECT_EQ(basic2.size(), size_t(2));
 }

 TEST(stack_test, copy_constructor) {
   s21::stack<int> basic({1, 2, 3, 4});
   s21::stack<int> basic2(basic);
   EXPECT_EQ(basic2.top(), 4);
   EXPECT_EQ(basic2.size(), size_t(4));
 }
//
 TEST(stack_test, copy_constructor2) {
   s21::stack<std::string> basic({"hello"});
   s21::stack<std::string> basic2(basic);
   EXPECT_EQ(basic2.top(), "hello");
   EXPECT_EQ(basic2.size(), size_t(1));
 }

TEST(stack_test, push1) {
  s21::stack<int> basic;
  int element = 5;
  basic.push(element);
  EXPECT_EQ(basic.top(), element);
}

TEST(stack_test, push2) {
  s21::stack<int> basic;
  int a = 5;
  int b = 10;
  int c = 100500;
  basic.push(a);
  basic.push(b);
  basic.push(c);
  EXPECT_EQ(basic.top(), c);
}

TEST(stack_test, push3) {
  s21::stack<int> basic;
  EXPECT_ANY_THROW(basic.top());
}

TEST(stack_test, push5) {
  s21::stack<std::string> basic;
  std::string element = "hello";
  basic.push(element);
  EXPECT_TRUE(!basic.empty());
}

TEST(stack_test, pop) {
  s21::stack<int> basic;
  int a = 5;
  int b = 10;
  int c = 100500;
  basic.push(a);
  basic.push(b);
  basic.push(c);
  basic.pop();
  EXPECT_EQ(basic.top(), b);
}

TEST(stack_test, pop2) {
  s21::stack<int> basic;
  int a = 5;
  int b = 10;
  int c = 100500;
  basic.push(a);
  basic.push(b);
  basic.push(c);
  basic.pop();
  basic.pop();
  EXPECT_EQ(basic.top(), a);
}

TEST(stack_test, typename_test1) {
  s21::stack<double> basic2;
  double element = 1.123123123;
  basic2.push(element);
  EXPECT_EQ(basic2.top(), element);
}

TEST(stack_test, typename_test2) {
  s21::stack<float> basic3;
  float element = 0.123;
  basic3.push(element);
  EXPECT_EQ(basic3.top(), element);
}

TEST(stack_test, size) {
  s21::stack<int> basic;
  int element = 100500;
  basic.push(element);
  EXPECT_EQ(basic.size(), size_t(1));
  EXPECT_EQ(basic.top(), element);
}

TEST(stack_test, size2) {
  s21::stack<int> basic;
  int element = 100500;
  int element2 = -100500;
  int element3 = -100500;
  basic.push(element);
  basic.push(element2);
  basic.push(element3);
  EXPECT_EQ(basic.size(), size_t(3));
  EXPECT_EQ(basic.top(), element3);
}

TEST(stack_test, size3) {
  s21::stack<int> basic;
  int element = 0;
  for (; element < 100; ++element) {
    basic.push(element);
  }
  EXPECT_EQ(basic.size(), size_t(100));
  EXPECT_EQ(basic.top(), element - 1);
}

TEST(stack_test, initializer_list) {
  s21::stack<int> basic({1, 2, 3});
  EXPECT_EQ(basic.size(), size_t(3));
  EXPECT_EQ(basic.top(), 3);
}

TEST(stack_test, initializer_list2) {
  s21::stack<double> basic({1.123, 2.123, 12321.23, -3.000003123});
  EXPECT_EQ(basic.size(), size_t(4));
  EXPECT_EQ(basic.top(), -3.000003123);
}

TEST(stack_test, swap) {
  s21::stack<double> basic({1.123, 2.123, 12321.23, -3.000003123});
  s21::stack<double> basic2({1, 2, 3});
  basic.swap(basic2);
  EXPECT_EQ(basic.size(), size_t(3));
  EXPECT_EQ(basic.top(), 3);
  EXPECT_EQ(basic2.size(), size_t(4));
  EXPECT_EQ(basic2.top(), -3.000003123);
}

TEST(stack_test, swap2) {
  s21::stack<double> basic({1.123, 2.123, 12321.23, -3.000003123});
  s21::stack<double> basic2;
  basic.swap(basic2);
  EXPECT_EQ(basic.size(), size_t(0));
  EXPECT_ANY_THROW(basic.top());
  EXPECT_EQ(basic2.size(), size_t(4));
  EXPECT_EQ(basic2.top(), -3.000003123);
}

TEST(stack_test, swap3) {
  s21::stack<double> basic;
  s21::stack<double> basic2({1.123, 2.123, 12321.23, -3.000003123});
  basic.swap(basic2);
  EXPECT_EQ(basic.size(), size_t(4));
  EXPECT_ANY_THROW(basic2.top());
  EXPECT_EQ(basic2.size(), size_t(0));
  EXPECT_EQ(basic.top(), -3.000003123);
}

TEST(stack_test, swap4) {
  s21::stack<double> basic;
  s21::stack<double> basic2;
  basic.swap(basic2);
  EXPECT_EQ(basic.size(), size_t(0));
  EXPECT_ANY_THROW(basic2.top());
  EXPECT_ANY_THROW(basic.top());
  EXPECT_EQ(basic2.size(), size_t(0));
}

TEST(stack_test, swap5) {
  s21::stack<std::string> basic;
  s21::stack<std::string> basic2;
  std::string element = "hello";
  basic.push(element);
  basic.swap(basic2);
  EXPECT_EQ(basic.size(), size_t(0));
  EXPECT_EQ(basic2.top(), element);
  EXPECT_ANY_THROW(basic.top());
  EXPECT_EQ(basic2.size(), size_t(1));
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}