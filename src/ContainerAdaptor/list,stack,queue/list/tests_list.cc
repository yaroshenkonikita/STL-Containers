#include <gtest/gtest.h>

#include "s21_list.h"

TEST(list_test, def_constructor) {
  s21::list<int> basic;
  EXPECT_ANY_THROW(basic.front());
  EXPECT_ANY_THROW(basic.back());
  EXPECT_TRUE(basic.empty());
}

TEST(list_test, p_constructor) {
  s21::list<int> basic(12);
  EXPECT_EQ(basic.front(), int());
  EXPECT_EQ(basic.back(), int());
  EXPECT_EQ(basic.size(), size_t(12));
  EXPECT_FALSE(basic.empty());
}

TEST(list_test, p_constructor2) {
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

TEST(list_test, pop_back) {
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

TEST(list_test, pop_back2) {
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
  basic.pop_back();
  basic.pop_back();
  EXPECT_TRUE(basic.size() == 1);
  EXPECT_EQ(basic.back(), element4);
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
  EXPECT_EQ(basic.size(), (size_t)4);
  EXPECT_EQ(basic.front(), "hello");
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
  EXPECT_TRUE(basic2.empty());
}

TEST(list_test, operator_move2) {
  s21::list<std::string> basic2;
  s21::list<std::string> basic({"hello", "world", "lets", "go!"});
  basic2 = std::move(basic);
  EXPECT_EQ(basic2.front(), "hello");
  EXPECT_EQ(basic2.back(), "go!");
  EXPECT_TRUE(basic.empty());
}

TEST(list_test, constr_move) {
  s21::list<std::string> basic({"hello", "world", "lets", "go!"});
  s21::list<std::string> basic2(std::move(basic));
  EXPECT_EQ(basic2.front(), "hello");
  EXPECT_EQ(basic2.back(), "go!");
  EXPECT_TRUE(basic.empty());
}

TEST(list_test, iter) {
  s21::list<std::string> basic = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic.begin());
  EXPECT_EQ(*it, "hello");
}

TEST(list_test, iter2) {
  s21::list<std::string> basic = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic.begin());
  EXPECT_EQ(*it++, "world");
}

TEST(list_test, iter3) {
  s21::list<std::string> basic = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic.end());
  EXPECT_EQ(*it++, "hello");
}

TEST(list_test, iter4) {
  s21::list<std::string> basic = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic.begin());
  it++;
  it++;
  it++;
  EXPECT_EQ(*it, "go!");
}

TEST(list_test, iter5) {
  s21::list<std::string> basic = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic.begin());
  it++;
  it++;
  it++;
  it++;
  EXPECT_EQ(*it, "");
}

TEST(list_test, iter6) {
  s21::list<std::string> basic = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic.begin());
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, "hello");
}

TEST(list_test, insert_iter) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic2.begin());
  EXPECT_EQ(*basic2.begin(), basic2.front());
  basic2.insert(it, "lol");
  EXPECT_EQ(basic2.front(), "lol");
}

TEST(list_test, insert_iter2) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::ListIterator it(basic2.begin());
  ++it;
  EXPECT_EQ(*basic2.begin(), basic2.front());
  basic2.insert(it, "lol");
  EXPECT_EQ(basic2.front(), "hello");
}

TEST(list_test, insert_iter3) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::ListIterator it(basic2.begin());
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*basic2.begin(), basic2.front());
  basic2.insert(it, "lol");
  EXPECT_EQ(basic2.back(), "go!");
}

TEST(list_test, insert_iter4) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it;
  it = basic2.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*basic2.begin(), basic2.front());
  basic2.insert(it, "lol");
  EXPECT_EQ(basic2.back(), "lol");
}

TEST(list_test, insert_iter5) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic2.begin());
  ++it;
  ++it;
  ++it;
  it++;
  EXPECT_EQ(*basic2.begin(), basic2.front());
  basic2.insert(it, "lol");
  EXPECT_EQ(basic2.back(), "lol");
}

TEST(list_test, insert_iter6) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic2.begin());
  it--;
  basic2.insert(it, "lol");
  EXPECT_EQ(basic2.back(), "lol");
}

TEST(list_test, insert_iter7) {
  std::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  std::list<std::string>::iterator it(basic2.begin());
  --it;
  basic2.insert(it, "lol");
  EXPECT_EQ(basic2.back(), "lol");
}

TEST(list_test, insert_iter8) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::iterator it(basic2.begin());
  basic2.insert(it, "lol");
  EXPECT_EQ(basic2.front(), "lol");
}

TEST(list_test, emplace) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  s21::list<std::string>::const_iterator it(basic2.begin());
  basic2.emplace(it, "1");
  EXPECT_EQ(basic2.front(), "1");
}

TEST(list_test, emplace2) {
  s21::list<int> basic2 = {1, 3, 5, 7};
  s21::list<int>::const_iterator it(basic2.begin());
  auto it2 = basic2.emplace(it, 11, 12);
  EXPECT_EQ(basic2.front(), 11);
  EXPECT_EQ(*it--, 12);
  EXPECT_EQ(*it--, 11);
  EXPECT_EQ(*it2, 12);
}

TEST(list_test, emplace3) {
  s21::list<std::string> basic2 = {"hello", "hello", "world", "lets", "go!"};
  s21::list<std::string>::const_iterator it(basic2.begin());
  auto it2 = basic2.emplace(it, "hi", "ho", "123");
  EXPECT_EQ(basic2.front(), "hi");
  EXPECT_EQ(*it--, "123");
  EXPECT_EQ(*it--, "ho");
  EXPECT_EQ(*it--, "hi");
  EXPECT_EQ(*it--, "");
  EXPECT_EQ(*it--, "go!");
  EXPECT_EQ(*it2, "123");
}

TEST(list_test, emplace4) {
  s21::list<int> basic2 = {1, 3, 5, 7};
  s21::list<int>::const_iterator it(basic2.begin());
  it++;
  auto it2 = basic2.emplace(it, 11, 12);
  EXPECT_EQ(basic2.front(), 1);
  EXPECT_EQ(*it--, 12);
  EXPECT_EQ(*it--, 11);
  EXPECT_EQ(*it2, 12);
}

TEST(list_test, emplace5) {
  s21::list<int> basic2 = {1, 3, 5, 7};
  s21::list<int>::const_iterator it(basic2.end());
  auto it2 = basic2.emplace(it--, 11, 12);
  EXPECT_EQ(basic2.back(), 7);
  EXPECT_EQ(*it--, 12);
  EXPECT_EQ(*it--, 11);
  EXPECT_EQ(*it2, 12);
}

TEST(list_test, emplace_back) {
  s21::list<std::string> basic2 = {"hello", "hello", "world", "lets", "go!"};
  s21::list<std::string>::const_iterator it(basic2.end());
  basic2.emplace_back("hi", "ho", "123");
  EXPECT_EQ(*it--, "123");
  EXPECT_EQ(*it--, "ho");
  EXPECT_EQ(*it--, "hi");
  EXPECT_EQ(*it--, "go!");
}

TEST(list_test, emplace_front) {
  s21::list<std::string> basic2 = {"hello", "hello", "world", "lets", "go!"};
  basic2.emplace_front("hi", "ho", "123");
  s21::list<std::string>::const_iterator it(basic2.begin());
  EXPECT_EQ(*it, "hi");
  EXPECT_EQ(*it++, "ho");
  EXPECT_EQ(*it++, "123");
  EXPECT_EQ(*it++, "hello");
  it = basic2.begin();
  EXPECT_EQ(*it--, "");
  EXPECT_EQ(*it--, "go!");
}

TEST(list_test, unique) {
  s21::list<std::string> basic2 = {"hello", "hello", "world", "lets", "go!"};
  basic2.unique();
  EXPECT_EQ(basic2.front(), "hello");
  s21::list<std::string>::iterator it(basic2.begin());
  EXPECT_EQ(*it++, "world");
}

TEST(list_test, unique2) {
  s21::list<std::string> basic2 = {"hello", "hello", "world",
                                   "lets",  "go!",   "go!"};
  basic2.unique();
  EXPECT_EQ(basic2.back(), "go!");
  s21::list<std::string>::iterator it(basic2.begin());
  --it;
  EXPECT_EQ(*it--, "go!");
  EXPECT_EQ(*it--, "lets");
}

TEST(list_test, unique3) {
  s21::list<std::string> basic2 = {"hello", "hello", "world", "world",
                                   "lets",  "go!",   "go!"};
  basic2.unique();
  EXPECT_EQ(basic2.back(), "go!");
  s21::list<std::string>::iterator it(basic2.begin());
  EXPECT_EQ(*it, "hello");
  EXPECT_EQ(*it++, "world");
  EXPECT_EQ(*it++, "lets");
  EXPECT_EQ(*it++, "go!");
  EXPECT_EQ(*it++, "");
  EXPECT_EQ(*it++, "hello");
}

TEST(list_test, unique4) {
  s21::list<std::string> basic2 = {"hello", "hello", "world", "world",
                                   "lets",  "go!",   "go!"};
  basic2.unique();
  s21::list<std::string>::iterator it(basic2.begin());
  EXPECT_EQ(*it, "hello");
  EXPECT_EQ(*it--, "");
  EXPECT_EQ(*it--, "go!");
  EXPECT_EQ(*it--, "lets");
  EXPECT_EQ(*it--, "world");
  EXPECT_EQ(*it--, "hello");
}

TEST(list_test, erase) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  auto it(basic2.begin());
  EXPECT_EQ(basic2.front(), "hello");
  basic2.erase(it);
  EXPECT_EQ(basic2.front(), "world");
}

TEST(list_test, std_erase) {
  std::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  auto it(basic2.begin());
  EXPECT_EQ(basic2.front(), "hello");
  basic2.erase(it);
  EXPECT_EQ(basic2.front(), "world");
}

TEST(list_test, std_erase2) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  auto it(basic2.end());
  EXPECT_EQ(basic2.back(), "go!");
  basic2.erase(it);
  EXPECT_EQ(basic2.back(), "lets");
}

TEST(list_test, std_erase3) {
  std::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  auto it(basic2.end());
  --it;
  EXPECT_EQ(basic2.back(), "go!");
  basic2.erase(it);
  EXPECT_EQ(basic2.back(), "lets");
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
}

TEST(list_test, erase3) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  auto it(basic2.begin());
  while (it != basic2.end()) {
    basic2.erase(it);
    it = basic2.begin();
  }
  EXPECT_TRUE(basic2.empty());
}

TEST(list_test, erase4) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  auto it(basic2.begin());
  EXPECT_EQ(*it++, "world");
  basic2.erase(it);
  it = basic2.begin();
  EXPECT_EQ(*it++, "lets");
}

TEST(list_test, splice) {
  s21::list<std::string> basic = {"hello", "world"};
  s21::list<std::string> basic2 = {"lets", "go!"};
  s21::list<std::string>::const_iterator it;
  it = basic.begin();
  basic.splice(it, basic2);
  EXPECT_EQ(basic.front(), "lets");
  EXPECT_EQ(basic.back(), "world");
  EXPECT_EQ(*it, "hello");
  EXPECT_EQ(*it++, "world");
}

TEST(list_test, splice2) {
  s21::list<std::string> basic = {"hello", "world"};
  s21::list<std::string> basic2 = {"lets", "go!"};
  s21::list<std::string>::iterator it2(basic.begin());
  s21::list<std::string>::const_iterator it(it2.current);
  basic.splice(it++, basic2);
  it = basic.begin();
  EXPECT_EQ(*it++, "lets");
  EXPECT_EQ(*it++, "go!");
  EXPECT_EQ(basic.front(), "hello");
  EXPECT_EQ(basic.back(), "world");
}

TEST(list_test, splice3) {
  s21::list<std::string> basic = {"hello", "world"};
  s21::list<std::string> basic2 = {"lets", "go!"};
  auto it = basic.end();
  basic.splice(it, basic2);
  EXPECT_EQ(basic.front(), "hello");
  EXPECT_EQ(basic.back(), "go!");
}

TEST(list_test, reverse) {
  s21::list<std::string> basic2 = {"hello", "world", "lets", "go!"};
  EXPECT_EQ(basic2.front(), "hello");
  basic2.reverse();
  EXPECT_EQ(basic2.front(), "go!");
  auto it = basic2.begin();
  EXPECT_EQ(*it, "go!");
  EXPECT_EQ(*it--, "");
  EXPECT_EQ(*it--, "hello");
}

TEST(list_test, reverse2) {
  s21::list<std::string> basic2;
  EXPECT_TRUE(basic2.empty());
  basic2.reverse();
  EXPECT_TRUE(basic2.empty());
}

TEST(list_test, reverse3) {
  s21::list<std::string> basic2({"1"});
  EXPECT_EQ(basic2.front(), "1");
  basic2.reverse();
  EXPECT_EQ(basic2.front(), "1");
}

TEST(list_test, reverse4) {
  s21::list<int> basic2({1, 2, 3, 12312312, 100500});
  EXPECT_EQ(basic2.front(), 1);
  basic2.reverse();
  EXPECT_EQ(basic2.front(), 100500);
}

TEST(list_test, sort) {
  s21::list<std::string> basic({"hello", "world", "lets", "go!"});
  EXPECT_EQ(basic.front(), "hello");
  basic.sort();
  EXPECT_EQ(basic.front(), "go!");
  std::list<std::string> basic2({"hello", "world", "lets", "go!"});
  EXPECT_EQ(basic2.front(), "hello");
  basic2.sort();
  EXPECT_EQ(basic2.front(), "go!");
}

TEST(list_test, sort2) {
  s21::list<std::string> basic;
  basic.sort();
  EXPECT_TRUE(basic.empty());
  std::list<std::string> basic2;
  basic2.sort();
  EXPECT_TRUE(basic.empty());
}

TEST(list_test, sort3) {
  s21::list<int> basic(
      {-100, 12321, 123, -5124, 13, 0, -111, 17, 5125, 41349394, -31423434, 2});
  std::list<int> basic2(
      {-100, 12321, 123, -5124, 13, 0, -111, 17, 5125, 41349394, -31423434, 2});
  basic.sort();
  basic2.sort();
  EXPECT_EQ(basic.front(), -31423434);
  EXPECT_EQ(basic2.front(), -31423434);
  EXPECT_EQ(basic2.back(), 41349394);
}

TEST(list_test, merge) {
  s21::list<int> basic(
      {-100, 12321, 123, -5124, 13, 0, -111, 17, 5125, 41349394, -31423434, 2});
  s21::list<int> basic2({1000000000, -1000000000});
  basic.sort();
  basic2.sort();
  basic.merge(basic2);
  EXPECT_EQ(basic.front(), -1000000000);
  EXPECT_EQ(basic.back(), 1000000000);
  EXPECT_TRUE(basic2.empty());
}

TEST(list_test, merge2) {
  std::list<int> basic;
  std::list<int> basic2({1000000000, -1000000000});
  basic.sort();
  basic2.sort();
  basic.merge(basic2);
  EXPECT_EQ(basic.front(), -1000000000);
  EXPECT_EQ(basic.back(), 1000000000);
  EXPECT_TRUE(basic2.empty());
}

TEST(list_test, merge3) {
  s21::list<int> basic;
  s21::list<int> basic2({1000000000, -1000000000});
  basic.sort();
  basic2.sort();
  basic.merge(basic2);
  EXPECT_EQ(basic.front(), -1000000000);
  EXPECT_EQ(basic.back(), 1000000000);
  EXPECT_TRUE(basic2.empty());
}

TEST(list_test, max_size) {
  std::list<std::string> basic2({"hello", "world", "lets", "go!"});
  s21::list<std::string> basic({"hello", "world", "lets", "go!"});
  EXPECT_EQ(basic2.max_size(), basic.max_size());
}

TEST(list_test, max_size2) {
  std::list<char> basic2;
  s21::list<char> basic;
  EXPECT_EQ(basic2.max_size(), basic.max_size());
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}