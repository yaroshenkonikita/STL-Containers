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
  EXPECT_EQ(basic.top(), 0);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}