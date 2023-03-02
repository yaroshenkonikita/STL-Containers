#include <gtest/gtest.h>

#include "s21_list.h"

TEST(list_test, def_constructor) {
  list<int> basic;
  EXPECT_ANY_THROW(basic.front());
  EXPECT_ANY_THROW(basic.back());
  EXPECT_TRUE(basic.empty());
}

TEST(list_test, push_back) {
  list<int> basic;
  basic.push_back(1);
  EXPECT_TRUE(basic.getSize() == 1);
  EXPECT_EQ(basic.back(),1);
  EXPECT_EQ(basic.front(),1);
}

TEST(list_test, push_back2) {
  list<std::string> basic;
  std::string element = "hello";
  basic.push_back(element);
  EXPECT_TRUE(basic.size() == 1);
  EXPECT_EQ(basic.back(),element);
  EXPECT_EQ(basic.front(),element);
}

TEST(list_test, push_back3) {
  list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  basic.push_back(element);
  basic.push_back(element2);
  EXPECT_TRUE(basic.getSize() == 2);
//  EXPECT_EQ(basic.back(),element);
  EXPECT_EQ(basic.back(),element2);
  EXPECT_EQ(basic.front(),element);
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
  EXPECT_TRUE(basic.getSize() == 4);
  EXPECT_EQ(basic.back(),element4);
  EXPECT_EQ(basic.front(),element);
}

TEST(list_test, push_front) {
  list<int> basic;
  basic.push_front(1);
  EXPECT_TRUE(basic.getSize() == 1);
  EXPECT_EQ(basic.front(), 1);
}

TEST(list_test, push_front2) {
  list<std::string> basic;
  std::string element = "hello";
  basic.push_front(element);
  EXPECT_TRUE(basic.getSize() == 1);
  EXPECT_EQ(basic.back(),element);
  EXPECT_EQ(basic.front(),element);
}

TEST(list_test, push_front3) {
  list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  basic.push_front(element);
  basic.push_front(element2);
  EXPECT_TRUE(basic.getSize() == 2);
  //  EXPECT_EQ(basic.back(),element);
  EXPECT_EQ(basic.back(),element);
  EXPECT_EQ(basic.front(),element2);
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
  EXPECT_TRUE(basic.getSize() == 4);
  EXPECT_EQ(basic.back(),element);
  EXPECT_EQ(basic.front(),element4);
}

TEST(list_test, push_back_and_front) {
  list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_front(element2);
  basic.push_back(element);
  basic.push_front(element3);
  basic.push_back(element4);
  EXPECT_TRUE(basic.getSize() == 4);
  EXPECT_EQ(basic.back(),element4);
  EXPECT_EQ(basic.front(),element3);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}