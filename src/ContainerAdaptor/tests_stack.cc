#include <gtest/gtest.h>

#include "s21_stack.h"

TEST(stack_test, move_constructor) {
  Stack<int> basic({1, 2, 3, 4});
  Stack<int> basic2(std::move(basic));
  EXPECT_TRUE(basic.empty());
  EXPECT_EQ(basic.size(), size_t(0));
  EXPECT_EQ(basic2.top(), 4);
  EXPECT_EQ(basic2.size(), size_t(4));
}

// TEST(stack_test, move_constructor_operator) {
//   Stack<int> basic({1, 2, 3, 4});
//   Stack<int> basic2;
//   basic2 = basic;
//   EXPECT_TRUE(basic.empty());
//   EXPECT_EQ(basic.size(), size_t(0));
//   EXPECT_EQ(basic2.top(), 4);
//   EXPECT_EQ(basic2.size(), size_t(4));
// }

// TEST(stack_test, copy_constructor) {
//   Stack<int> basic({1, 2, 3, 4});
//   Stack<int> basic2(basic);
//   EXPECT_TRUE(basic.empty());
//   EXPECT_EQ(basic.size(), size_t(0));
//   EXPECT_EQ(basic2.top(), 4);
//   EXPECT_EQ(basic2.size(), size_t(4));
// }

TEST(stack_test, push1) {
  Stack<int> basic;
  int element = 5;
  basic.push(element);
  EXPECT_EQ(basic.top(), element);
}

TEST(stack_test, push2) {
  Stack<int> basic;
  int a = 5;
  int b = 10;
  int c = 100500;
  basic.push(a);
  basic.push(b);
  basic.push(c);
  EXPECT_EQ(basic.top(), c);
}

TEST(stack_test, push3) {
  Stack<int> basic;
  EXPECT_ANY_THROW(basic.top());
}

// TEST(stack_test, push4) {
////  Stack<std::stack<int>> basic;
//  std::stack<std::string> basic;
//  std::string element = "hello";
//  basic.push(element);
//  EXPECT_EQ(basic.top(), element);
//}

TEST(stack_test, push5) {
  Stack<std::string> basic;
  //  std::stack<std::string> basic;
  std::string element = "hello";
  basic.push(element);
  EXPECT_TRUE(!basic.empty());
}

TEST(stack_test, pop) {
  Stack<int> basic;
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
  Stack<int> basic;
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
  Stack<double> basic2;
  double element = 1.123123123;
  basic2.push(element);
  EXPECT_EQ(basic2.top(), element);
}

TEST(stack_test, typename_test2) {
  Stack<float> basic3;
  float element = 0.123;
  basic3.push(element);
  EXPECT_EQ(basic3.top(), element);
}

TEST(stack_test, size) {
  Stack<int> basic;
  int element = 100500;
  basic.push(element);
  EXPECT_EQ(basic.size(), size_t(1));
  EXPECT_EQ(basic.top(), element);
}

TEST(stack_test, size2) {
  Stack<int> basic;
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
  Stack<int> basic;
  int element = 0;
  for (; element < 100; ++element) {
    basic.push(element);
  }
  EXPECT_EQ(basic.size(), size_t(100));
  EXPECT_EQ(basic.top(), element - 1);
}

TEST(stack_test, initializer_list) {
  Stack<int> basic({1, 2, 3});
  EXPECT_EQ(basic.size(), size_t(3));
  EXPECT_EQ(basic.top(), 3);
}

TEST(stack_test, initializer_list2) {
  Stack<double> basic({1.123, 2.123, 12321.23, -3.000003123});
  EXPECT_EQ(basic.size(), size_t(4));
  EXPECT_EQ(basic.top(), -3.000003123);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}