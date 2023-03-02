#include <gtest/gtest.h>

#include "s21_list.h"

TEST(list_test, def_constructor) {
  list<int> basic;
  EXPECT_ANY_THROW(basic.front());
  EXPECT_ANY_THROW(basic.back());
  EXPECT_TRUE(basic.empty());
}

TEST(list_test, parametr_constructor) {
  list<int> basic(12);
  EXPECT_EQ(basic.front(), int());
  EXPECT_EQ(basic.back(), int());
  EXPECT_EQ(basic.size(), 12);
  EXPECT_FALSE(basic.empty());
}

TEST(list_test, parametr_constructor2) {
  list<std::string> basic(12);
  EXPECT_EQ(basic.front(), std::string());
  EXPECT_EQ(basic.back(), std::string());
  EXPECT_EQ(basic.size(), 12);
  EXPECT_FALSE(basic.empty());
}

TEST(list_test, initializer_list_constructor) {
  list<int> basic({1,2,3,4,5});
  EXPECT_EQ(basic.front(), 5);
  EXPECT_EQ(basic.back(), 1);
  EXPECT_EQ(basic.size(), 5);
  EXPECT_FALSE(basic.empty());
}

TEST(list_test, initializer_list_constructor2) {
  list<std::string> basic({"hello", "world"});
  EXPECT_TRUE(basic.size() == 2);
  EXPECT_EQ(basic.back(),"hello");
  EXPECT_EQ(basic.front(),"world");
}

TEST(list_test, initializer_list_constructor3) {
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  list<std::string> basic({element, element2,element3,element4});
  EXPECT_TRUE(basic.size() == 4);
  EXPECT_EQ(basic.back(),element);
  EXPECT_EQ(basic.front(),element4);
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