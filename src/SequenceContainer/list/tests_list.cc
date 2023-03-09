#include <gtest/gtest.h>

#include "s21_list.h"

TEST(list_test, def_constructor) {
  s21::list<int> basic;
  EXPECT_ANY_THROW(basic.front());
  EXPECT_ANY_THROW(basic.back());
  EXPECT_TRUE(basic.empty());
}

TEST(list_test, clear) {
  s21::list<int> basic({1, 2, 3, 4, 5, 6, 12345});
  EXPECT_TRUE(!basic.empty());
  basic.clear();
  EXPECT_TRUE(basic.empty());
}

TEST(list_test, parametr_constructor) {
  s21::list<int> basic(12);
  EXPECT_EQ(basic.front(), int());
  EXPECT_EQ(basic.back(), int());
  EXPECT_EQ(basic.size(), size_t(12));
  EXPECT_FALSE(basic.empty());
}

TEST(list_test, parametr_constructor2) {
  s21::list<std::string> basic(12);
  EXPECT_EQ(basic.front(), std::string());
  EXPECT_EQ(basic.back(), std::string());
  EXPECT_EQ(basic.size(), size_t(12));
  EXPECT_FALSE(basic.empty());
}

TEST(list_test, initializer_list_constructor) {
  s21::list<int> basic({1, 2, 3, 4, 5});
  EXPECT_EQ(basic.front(), 1);
  EXPECT_EQ(basic.back(), 5);
  EXPECT_EQ(basic.size(), size_t(5));
  EXPECT_FALSE(basic.empty());
}

TEST(list_test, initializer_list_constructor2) {
  s21::list<std::string> basic({"hello", "world"});
  EXPECT_TRUE(basic.size() == 2);
  EXPECT_EQ(basic.back(), "world");
  EXPECT_EQ(basic.front(), "hello");
}

TEST(list_test, initializer_list_constructor3) {
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  s21::list<std::string> basic({element, element2, element3, element4});
  EXPECT_TRUE(basic.size() == 4);
  EXPECT_EQ(basic.back(), element4);
  EXPECT_EQ(basic.front(), element);
}

TEST(list_test, copy_constructor) {
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  s21::list<std::string> basic({element, element2, element3, element4});
  s21::list<std::string> basic2(basic);
  EXPECT_TRUE(basic2.size() == 4);
  EXPECT_EQ(basic2.back(), element4);
  EXPECT_EQ(basic2.front(), element);
}

TEST(list_test, copy_constructor2) {
  s21::list<std::string> basic;
  s21::list<std::string> basic2(basic);
  EXPECT_TRUE(basic2.empty());
}

TEST(list_test, push_back) {
  s21::list<int> basic;
  basic.push_back(1);
  EXPECT_TRUE(basic.size() == 1);
  EXPECT_EQ(basic.back(), 1);
  EXPECT_EQ(basic.front(), 1);
}

TEST(list_test, push_back2) {
  s21::list<std::string> basic;
  std::string element = "hello";
  basic.push_back(element);
  EXPECT_TRUE(basic.size() == 1);
  EXPECT_EQ(basic.back(), element);
  EXPECT_EQ(basic.front(), element);
}

TEST(list_test, push_back3) {
  s21::list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  basic.push_back(element);
  basic.push_back(element2);
  EXPECT_TRUE(basic.size() == 2);
  EXPECT_EQ(basic.back(), element2);
  EXPECT_EQ(basic.front(), element);
}

TEST(list_test, push_back4) {
  s21::list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_back(element);
  basic.push_back(element2);
  basic.push_back(element3);
  basic.push_back(element4);
  EXPECT_TRUE(basic.size() == 4);
  EXPECT_EQ(basic.back(), element4);
  EXPECT_EQ(basic.front(), element);
}

TEST(list_test, push_front) {
  s21::list<int> basic;
  basic.push_front(1);
  EXPECT_TRUE(basic.size() == 1);
  EXPECT_EQ(basic.front(), 1);
}

TEST(list_test, push_front2) {
  s21::list<std::string> basic;
  std::string element = "hello";
  basic.push_front(element);
  EXPECT_TRUE(basic.size() == 1);
  EXPECT_EQ(basic.back(), element);
  EXPECT_EQ(basic.front(), element);
}

TEST(list_test, push_front3) {
  s21::list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  basic.push_front(element);
  basic.push_front(element2);
  EXPECT_TRUE(basic.size() == 2);
  EXPECT_EQ(basic.back(), element);
  EXPECT_EQ(basic.front(), element2);
}

TEST(list_test, push_front4) {
  s21::list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_front(element);
  basic.push_front(element2);
  basic.push_front(element3);
  basic.push_front(element4);
  EXPECT_TRUE(basic.size() == 4);
  EXPECT_EQ(basic.back(), element);
  EXPECT_EQ(basic.front(), element4);
}

TEST(list_test, push_back_and_front) {
  s21::list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_front(element2);
  basic.push_back(element);
  basic.push_front(element3);
  basic.push_back(element4);
  EXPECT_TRUE(basic.size() == 4);
  EXPECT_EQ(basic.back(), element4);
  EXPECT_EQ(basic.front(), element3);
}

TEST(list_test, pop_front) {
  s21::list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_front(element);
  basic.push_front(element2);
  basic.push_front(element3);
  basic.push_front(element4);
  basic.pop_front();
  EXPECT_TRUE(basic.size() == 3);
  EXPECT_EQ(basic.back(), element);
  EXPECT_EQ(basic.front(), element3);
}

TEST(list_test, pop_front2) {
  s21::list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_front(element);
  basic.push_front(element2);
  basic.push_front(element3);
  basic.push_front(element4);
  basic.pop_back();
  EXPECT_TRUE(basic.size() == 3);
  EXPECT_EQ(basic.back(), element2);
  EXPECT_EQ(basic.front(), element4);
}

TEST(list_test, pop_front_and_back) {
  s21::list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_front(element);
  basic.push_front(element2);
  basic.push_front(element3);
  basic.push_front(element4);
  basic.pop_front();
  basic.pop_back();
  EXPECT_TRUE(basic.size() == 2);
  EXPECT_EQ(basic.back(), element2);
  EXPECT_EQ(basic.front(), element3);
}

TEST(list_test, pop_front_and_back2) {
  s21::list<std::string> basic;
  std::string element = "hello";
  std::string element2 = "world";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_back(element);
  basic.push_back(element2);
  basic.push_back(element3);
  basic.push_back(element4);
  basic.pop_front();
  basic.pop_front();
  basic.pop_back();
  EXPECT_TRUE(basic.size() == 1);
  EXPECT_EQ(basic.back(), element3);
  EXPECT_EQ(basic.front(), element3);
}

TEST(list_test, swap) {
  s21::list<std::string> basic({"1", "2", "3"});
  EXPECT_EQ(basic.front(), "1");
  s21::list<std::string> basic2({"hello", "world"});
  EXPECT_EQ(basic2.front(), "hello");
  basic.swap(basic2);
  EXPECT_EQ(basic.front(), "hello");
  EXPECT_EQ(basic2.front(), "1");
}

TEST(list_test, swap2) {
  s21::list<std::string> basic({"1", "2", "3"});
  EXPECT_EQ(basic.front(), "1");
  s21::list<std::string> basic2({"hello", "world", "lets", "go!"});
  EXPECT_EQ(basic2.front(), "hello");
  basic.swap(basic2);
  EXPECT_EQ(basic.front(), "hello");
  EXPECT_EQ(basic.back(), "go!");
  EXPECT_EQ(basic2.back(), "3");
  EXPECT_EQ(basic2.front(), "1");
}

 TEST(list_test, swap3) {
   s21::list<std::string> basic;
   s21::list<std::string> basic2({"hello", "world", "lets", "go!"});
   basic.swap(basic2);
   EXPECT_TRUE(basic2.empty());
   EXPECT_EQ(basic.size(),(size_t)4);
   EXPECT_EQ(basic.front(),"hello");
 }

TEST(list_test, swap4) {
  std::list<std::string> basic;
  std::list<std::string> basic2({"hello", "world", "lets", "go!"});
  basic.swap(basic2);
  EXPECT_EQ(basic.front(), "hello");
  EXPECT_EQ(basic.back(), "go!");
  EXPECT_TRUE(basic2.empty());
}

TEST(list_test, operator_move) {
  s21::list<std::string> basic;
  s21::list<std::string> basic2({"hello", "world", "lets", "go!"});
  basic = std::move(basic2);
  EXPECT_EQ(basic.front(), "hello");
  EXPECT_EQ(basic.back(), "go!");
}

TEST(list_test, operator_move2) {
  s21::list<std::string> basic2;
  s21::list<std::string> basic({"hello", "world", "lets", "go!"});
  basic2 = std::move(basic);
  EXPECT_EQ(basic2.front(), "hello");
  EXPECT_EQ(basic2.back(), "go!");
}

TEST(list_test, insert) {
  s21::list<std::string> basic2;
  EXPECT_ANY_THROW(basic2.insert("123", 2));
}

TEST(list_test, insert2) {
  s21::list<std::string> basic2;
  EXPECT_ANY_THROW(basic2.insert("123", 1));
}

TEST(list_test, insert3) {
  s21::list<std::string> basic2;
  basic2.insert("123", 0);
  EXPECT_EQ(basic2.front(), "123");
}

TEST(list_test, insert4) {
  s21::list<std::string> basic2({"hello", "world", "lets", "go!"});
  EXPECT_EQ(basic2.size(), (size_t)4);
  basic2.insert("123", 0);
  EXPECT_EQ(basic2.front(), "123");
  EXPECT_EQ(basic2.size(), (size_t)5);
}

TEST(list_test, insert_iter) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::ListIterator it(basic2.begin());
  EXPECT_EQ(*basic2.begin(), basic2.front());
  basic2.insert_iter(it, "lol");
  EXPECT_EQ(basic2.front(), "lol");
}

TEST(list_test, insert_iter2) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::ListIterator it(basic2.begin());
  ++it;
  EXPECT_EQ(*basic2.begin(), basic2.front());
  basic2.insert_iter(it, "lol");
  EXPECT_EQ(basic2.front(), "hello");
}

TEST(list_test, insert_iter3) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::ListIterator it(basic2.begin());
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*basic2.begin(), basic2.front());
  basic2.insert_iter(it, "lol");
  EXPECT_EQ(basic2.back(), "go!");
}

TEST(list_test, insert_iter4) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::ListIterator it(basic2.begin());
  ++it;
  ++it;
  ++it;
  it++;
  EXPECT_EQ(*basic2.begin(), basic2.front());
  basic2.insert_iter(it, "lol");
  EXPECT_EQ(basic2.back(), "lol");
}

TEST(list_test, erase) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  auto it(basic2.begin());
  EXPECT_EQ(basic2.front(), "hello");
  basic2.erase(it);
  EXPECT_EQ(basic2.front(), "world");
//  ++it; // ecли не передвинуть итератор будет СЕГА!!!
//  basic2.erase(it);
//  EXPECT_EQ(basic2.front(), "lets");
}

TEST(list_test, std_erase) {
  std::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  std::list<std::string>::iterator it(basic2.begin());
  EXPECT_EQ(basic2.front(), "hello");
  basic2.erase(it);
  EXPECT_EQ(basic2.front(), "world");
//  ++it; // ecли не передвинуть итератор будет СЕГА!!!
//  basic2.erase(it);
//  EXPECT_EQ(basic2.front(), "lets");
}

TEST(list_test, erase2) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  auto it(basic2.end());
  EXPECT_EQ(basic2.back(), "go!");
  basic2.erase(it);
  EXPECT_EQ(basic2.back(), "lets");
  it = basic2.begin();
  basic2.erase(it);
  EXPECT_EQ(basic2.front(), "world");
  //  ++it; // ecли не передвинуть итератор будет СЕГА!!!
  //  basic2.erase(it);
  //  EXPECT_EQ(basic2.front(), "lets");
}

// TEST(list_test, max_size) {
//   std::list<std::string> basic2({"hello", "world", "lets", "go!"});
//   s21::list<std::string> basic({"hello", "world", "lets", "go!"});
//   EXPECT_EQ(basic2.max_size(),basic.max_size());
// }
//
// TEST(list_test, max_size2) {
//   std::list<char> basic2;
//   s21::list<char> basic;
//   EXPECT_EQ(basic2.max_size(),basic.max_size());
// }

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}