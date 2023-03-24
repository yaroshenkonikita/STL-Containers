#include <gtest/gtest.h>

#include <queue>

#include "../../ContainerAdaptor/s21_queue.h"

TEST(queue_tests, def_constructor) {
  s21::queue<int> basic;
  EXPECT_ANY_THROW(basic.front());
  EXPECT_ANY_THROW(basic.back());
  EXPECT_TRUE(basic.empty());
}

TEST(queue_tests, parametr_constructor) {
  s21::queue<int> basic(12);
  EXPECT_EQ(basic.front(), int());
  EXPECT_EQ(basic.back(), int());
  EXPECT_EQ(basic.size(), size_t(12));
  EXPECT_FALSE(basic.empty());
}

TEST(queue_tests, parametr_constructor2) {
  s21::queue<std::string> basic(12);
  EXPECT_EQ(basic.front(), std::string());
  EXPECT_EQ(basic.back(), std::string());
  EXPECT_EQ(basic.size(), size_t(12));
  EXPECT_FALSE(basic.empty());
}

TEST(queue_tests, initializer_list_constructor) {
  s21::queue<int> basic({1, 2, 3, 4, 5});
  EXPECT_EQ(basic.front(), 1);
  EXPECT_EQ(basic.back(), 5);
  EXPECT_EQ(basic.size(), size_t(5));
  EXPECT_FALSE(basic.empty());
}

TEST(queue_tests, initializer_list_constructor2) {
  s21::queue<std::string> basic({"hello", "world"});
  EXPECT_TRUE(basic.size() == 2);
  EXPECT_EQ(basic.back(), "world");
  EXPECT_EQ(basic.front(), "hello");
}

TEST(queue_tests, initializer_list_constructor3) {
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  s21::queue<std::string> basic({element, element2, element3, element4});
  EXPECT_TRUE(basic.size() == 4);
  EXPECT_EQ(basic.back(), element4);
  EXPECT_EQ(basic.front(), element);
}

TEST(queue_tests, copy_constructor) {
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  s21::queue<std::string> basic({element, element2, element3, element4});
  s21::queue<std::string> basic2(basic);
  EXPECT_TRUE(basic2.size() == 4);
  EXPECT_EQ(basic2.back(), element4);
  EXPECT_EQ(basic2.front(), element);
}

TEST(queue_tests, copy_constructor2) {
  s21::queue<std::string> basic;
  s21::queue<std::string> basic2(basic);
  EXPECT_TRUE(basic2.empty());
}

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
  s21::queue<int> basic;
  int element = 5;
  int element2 = 4;
  int element3 = 40;
  basic.push(element);
  basic.push(element2);
  basic.push(element3);
  basic.pop();
  EXPECT_EQ(basic.back(), element3);
  EXPECT_EQ(basic.front(), element2);
}

TEST(queue_tests, push_pop3) {
  s21::queue<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  basic.push(element);
  basic.push(element2);
  basic.push(element2);
  basic.pop();
  EXPECT_EQ(basic.back(), element2);
  EXPECT_EQ(basic.front(), element2);
}

TEST(queue_tests, emplace_back) {
  s21::queue<std::string> basic;
  basic.emplace_front("hello", "world", "hi", "ho");
  EXPECT_EQ(basic.front(), "hello");
  EXPECT_EQ(basic.back(), "ho");
}

TEST(queue_tests, swap) {
  s21::queue<std::string> basic({"hi", "ho"});
  EXPECT_TRUE(!basic.empty());
  s21::queue<std::string> basic2;
  basic.swap(basic2);
  EXPECT_EQ(basic2.back(), "ho");
  EXPECT_EQ(basic2.front(), "hi");
  EXPECT_TRUE(basic.empty());
}
