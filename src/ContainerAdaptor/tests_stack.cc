#include <gtest/gtest.h>

#include "s21_stack.h"

TEST(stack_test, push1) {
  Stack<int> basic;
  int a = 5;
  basic.push(a);
  EXPECT_EQ(basic.top(), a);
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
  double b = 1.123123123;
  basic2.push(b);
  EXPECT_EQ(basic2.top(), b);
}

TEST(stack_test, typename_test2) {
  Stack<float> basic3;
  float c = 0.123;
  basic3.push(c);
  EXPECT_EQ(basic3.top(), c);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}