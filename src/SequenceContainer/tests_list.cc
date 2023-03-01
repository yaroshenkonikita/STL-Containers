#include <gtest/gtest.h>

#include "s21_list.h"

TEST(list_test, def_constructor) {
  list<int> basic;
  EXPECT_TRUE(basic.head == nullptr);
  EXPECT_TRUE(basic.tail == nullptr);
  EXPECT_TRUE(basic.size == 0);
}

TEST(list_test, push_back) {
  list<int> basic;
  basic.push_back(1);
  EXPECT_TRUE(basic.size == 1);
}

TEST(list_test, push_back2) {
  list<std::string> basic;
  std::string element = "hello";
  basic.push_back(element);
  EXPECT_TRUE(basic.size == 1);
  EXPECT_EQ(basic.tail->data,element);
  EXPECT_EQ(basic.head->data,element);
}

TEST(list_test, push_back3) {
  list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  basic.push_back(element);
  basic.push_back(element2);
  EXPECT_TRUE(basic.size == 2);
//  EXPECT_EQ(basic.tail->data,element);
  EXPECT_EQ(basic.tail->data,element2);
  EXPECT_EQ(basic.head->data,element);
}

//TEST(list_test, push_back3) {
//  std::list<std::string> basic;
//  std::string element = "hello";
//  basic.push_back(element);
//  EXPECT_TRUE(basic.size() == 1);
//  EXPECT_EQ(basic.front(),element);
//}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}