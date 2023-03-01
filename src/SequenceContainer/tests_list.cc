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

TEST(list_test, push_back4) {
  list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_back(element);
  basic.push_back(element2);
  basic.push_back(element3);
  basic.push_back(element4);
  EXPECT_TRUE(basic.size == 4);
  EXPECT_EQ(basic.tail->data,element4);
  EXPECT_EQ(basic.head->data,element);
}

TEST(list_test, push_front) {
  list<int> basic;
  basic.push_front(1);
  EXPECT_TRUE(basic.size == 1);
  EXPECT_EQ(basic.head->data, 1);
}

TEST(list_test, push_front2) {
  list<std::string> basic;
  std::string element = "hello";
  basic.push_front(element);
  EXPECT_TRUE(basic.size == 1);
  EXPECT_EQ(basic.tail->data,element);
  EXPECT_EQ(basic.head->data,element);
}

TEST(list_test, push_front3) {
  list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  basic.push_front(element);
  basic.push_front(element2);
  EXPECT_TRUE(basic.size == 2);
  //  EXPECT_EQ(basic.tail->data,element);
  EXPECT_EQ(basic.tail->data,element);
  EXPECT_EQ(basic.head->data,element2);
}

TEST(list_test, push_front4) {
  list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_front(element);
  basic.push_front(element2);
  basic.push_front(element3);
  basic.push_front(element4);
  EXPECT_TRUE(basic.size == 4);
  EXPECT_EQ(basic.tail->data,element);
  EXPECT_EQ(basic.head->data,element4);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}