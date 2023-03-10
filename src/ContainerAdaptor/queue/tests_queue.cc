#include <gtest/gtest.h>

#include "s21_queue.h"

TEST(queue_tests, push1) {
  s21::queue<int> basic;
  int element = 5;
  int element2 = 4;
  basic.push(element);
  basic.push(element2);
  basic.push(element2);
  EXPECT_EQ(basic.back(), element2);
  EXPECT_EQ(basic.front(), element);
}

TEST(queue_tests, push_pop) {
  s21::queue<int> basic;
  int element = 5;
  int element2 = 4;
  basic.push(element);
  basic.push(element2);
  basic.push(element2);
  basic.pop();
  EXPECT_EQ(basic.back(), element2);
  EXPECT_EQ(basic.front(), element2);
}

TEST(queue_tests, push_pop2) {
  std::queue<int> basic;
  int element = 5;
  int element2 = 4;
  basic.push(element);
  basic.push(element2);
  basic.push(element2);
  basic.pop();
  EXPECT_EQ(basic.back(), element2);
  EXPECT_EQ(basic.front(), element2);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}