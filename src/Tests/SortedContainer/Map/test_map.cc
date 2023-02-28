#include <gtest/gtest.h>

#include <algorithm>

TEST(Map, default_constructor_instructor_insert) {
    std::map<int, int> basic;
    basic.insert({5, 5});
    basic.insert({20, 2});
    basic.insert({2, 20});
    int s[3] = {20, 5, 2};
    int *a = s, *b = a + 2;
    for (auto &item : basic) {
        EXPECT_EQ(item.second, *a++);
        EXPECT_EQ(item.first, *b--);
    }
}

TEST(Map, initializator_constructor_int) {
    std::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2}, {8, 8}, {0, 2}, {-228, 5}};
    int s1[6] = {-228, 0, 2, 4, 6, 8};
    int s2[6] = {5, 2, 2, 4, 7, 8};
    int *a = s1, *b = s2;
    for (auto &item : basic) {
        EXPECT_EQ(item.first, *a++);
        EXPECT_EQ(item.second, *b++);
    }
}

TEST(Map, initializator_constructor_double) {
    std::map<double, double> basic = {{999, 222}, {6, 6}, {3, 3}, {2, 4}, {90, -8}, {0, -29}, {-1, -1}};
    double s1[7] = {-1, 0, 2, 3, 6, 90, 999};
    double s2[7] = {-1, -29, 4, 3, 6, -8, 222};
    double *a = s1, *b = s2;
    for (auto &item : basic) {
        EXPECT_DOUBLE_EQ(item.first, *a++);
        EXPECT_DOUBLE_EQ(item.second, *b++);
    }
}

TEST(Map, initializator_constructor_char) {
    std::map<char, char> basic = {{'c', 'c'}, {'d', 'v'}, {'a', 'b'}, {'b', 'n'}};
    char s1[4] = {'a', 'b', 'c', 'd'};
    char s2[4] = {'b', 'n', 'c', 'v'};
    char *a = s1, *b = s2;
    for (auto &item : basic) {
        EXPECT_EQ(item.first, *a++);
        EXPECT_EQ(item.second, *b++);
    }
}

TEST(Map, copy_constructor_int) {
    std::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2}, {8, 8}, {0, 2}, {-228, 5}};
    std::map<int, int> copy{basic};
    int s1[6] = {-228, 0, 2, 4, 6, 8};
    int s2[6] = {5, 2, 2, 4, 7, 8};
    int *a = s1, *b = s2;
    for (auto &item : copy) {
        EXPECT_EQ(item.first, *a++);
        EXPECT_EQ(item.second, *b++);
    }
    EXPECT_EQ(basic.size(), copy.size());
}

TEST(Map, move_constructor_int) {
    std::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2}, {8, 8}, {0, 2}, {-228, 5}};
    std::map<int, int> move{std::move(basic)};
    int s1[6] = {-228, 0, 2, 4, 6, 8};
    int s2[6] = {5, 2, 2, 4, 7, 8};
    int *a = s1, *b = s2;
    for (auto &item : move) {
        EXPECT_EQ(item.first, *a++);
        EXPECT_EQ(item.second, *b++);
    }
    EXPECT_EQ(basic.size(), 0);
    EXPECT_EQ(move.size(), 6);
}

TEST(Map, move_operator_int) {
    std::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2}, {8, 8}, {0, 2}, {-228, 5}};
    std::map<int, int> move = std::move(basic);
    int s1[6] = {-228, 0, 2, 4, 6, 8};
    int s2[6] = {5, 2, 2, 4, 7, 8};
    int *a = s1, *b = s2;
    for (auto &item : move) {
        EXPECT_EQ(item.first, *a++);
        EXPECT_EQ(item.second, *b++);
    }
    EXPECT_EQ(basic.size(), 0);
    EXPECT_EQ(move.size(), 6);
}

TEST(Map, iterator_begin_end) {
    std::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2}, {8, 8}, {0, 2}, {-228, 5}};
    auto iter = basic.begin();
    auto iter_end = basic.end();
    int s1[6] = {-228, 0, 2, 4, 6, 8};
    int s2[6] = {5, 2, 2, 4, 7, 8};
    int *a = s1, *b = s2, size = 0;
    while (iter != iter_end) {
        EXPECT_EQ((*iter).first, *a++);
        EXPECT_EQ((*iter++).second, *b++);
        ++size;
    }
    EXPECT_EQ(size, 6);
}

TEST(Map, empty_size) {
    std::map<int, int> basic;
    EXPECT_TRUE(basic.empty());
    EXPECT_EQ(basic.size(), 0);
    basic.insert({4, 4});
    EXPECT_EQ(basic.size(), 1);
    EXPECT_FALSE(basic.empty());
}

TEST(Map, empty_erase) {
    std::map<int, int> basic;
    EXPECT_TRUE(basic.empty());
    basic.insert({4, 4});
    EXPECT_FALSE(basic.empty());
    basic.erase(4);
    EXPECT_TRUE(basic.empty());
}

TEST(Map, insert) {
    std::map<int, int> basic;
    std::pair pair = basic.insert({5, 5});
    EXPECT_EQ((*pair.first).first, 5);
    EXPECT_TRUE(pair.second);
    std::pair pair2 = basic.insert({5, 5});
    EXPECT_EQ((*pair2.first).first, 5);
    EXPECT_FALSE(pair2.second);
    basic.insert({20, 20});
    basic.insert({2, 2});
    int s[3] = {2, 5, 20};
    int *a = s;
    for (auto &item : basic) {
        EXPECT_EQ(item.first, *a++);
    }
}

TEST(Map, empty_clear) {
    std::map<int, int> basic;
    EXPECT_TRUE(basic.empty());
    basic.insert({4, 5});
    EXPECT_FALSE(basic.empty());
    basic.clear();
    EXPECT_TRUE(basic.empty());
}

TEST(Map, size_clear) {
    std::map<int, int> basic{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
    EXPECT_EQ(basic.size(), 6);
    basic.insert({4, 4});
    EXPECT_EQ(basic.size(), 6);
    basic.insert({7, 7});
    EXPECT_EQ(basic.size(), 7);
    basic.clear();
    EXPECT_EQ(basic.size(), 0);
}

// TEST(Map, max_size) {
//     std::map<double, double> basic1{1, 2, 3};
//     std::map<__int128> basic2{1, 2, 3, 4};
//     std::map<char, char> basic3;
//     // EXPECT_EQ(basic1.max_size(), 230584300921369395); // std 17
//     // EXPECT_EQ(basic2.max_size(), 192153584101141162);
//     // EXPECT_EQ(basic3.max_size(), 230584300921369395);
//     EXPECT_EQ(basic1.max_size(), 461168601842738790); // std 20
//     EXPECT_EQ(basic2.max_size(), 384307168202282325);
//     EXPECT_EQ(basic3.max_size(), 461168601842738790);
// }

// TEST(Map, swap_int) {
//     std::map<int, int> basic1{1, 2, 3};
//     std::map<int, int> basic2{1, 2, 3, 4};
//     EXPECT_EQ(basic1.size(), 3);
//     EXPECT_EQ(basic2.size(), 4);
//     int s1[3] = {1, 2, 3};
//     int s2[4] = {1, 2, 3, 4};
//     int *a = s1;
//     for (auto &item : basic1) {
//         EXPECT_EQ(item, *a++);
//     }
//     a = s2;
//     for (auto &item : basic2) {
//         EXPECT_EQ(item, *a++);
//     }
//     basic1.swap(basic2);
//     EXPECT_EQ(basic1.size(), 4);
//     EXPECT_EQ(basic2.size(), 3);
//     a = s1;
//     for (auto &item : basic2) {
//         EXPECT_EQ(item, *a++);
//     }
//     a = s2;
//     for (auto &item : basic1) {
//         EXPECT_EQ(item, *a++);
//     }
// }
// TEST(Map, swap_double) {
//     std::map<double, double> basic1{78, 23, -9};
//     std::map<double, double> basic2{55, 22, -8, -0.5};
//     EXPECT_EQ(basic1.size(), 3);
//     EXPECT_EQ(basic2.size(), 4);
//     double s1[3] = {-9, 23, 78};
//     double s2[4] = {-8, -0.5, 22, 55};
//     double *a = s1;
//     for (auto &item : basic1) {
//         EXPECT_DOUBLE_EQ(item, *a++);
//     }
//     a = s2;
//     for (auto &item : basic2) {
//         EXPECT_DOUBLE_EQ(item, *a++);
//     }
//     basic1.swap(basic2);
//     EXPECT_EQ(basic1.size(), 4);
//     EXPECT_EQ(basic2.size(), 3);
//     a = s1;
//     for (auto &item : basic2) {
//         EXPECT_DOUBLE_EQ(item, *a++);
//     }
//     a = s2;
//     for (auto &item : basic1) {
//         EXPECT_DOUBLE_EQ(item, *a++);
//     }
// }

// TEST(Map, merge_double) {
//     std::map<double, double> basic1{78, 23, -9, -8, -0.5};
//     std::map<double, double> basic2{55, 22, -8, -0.5};
//     EXPECT_EQ(basic1.size(), 5);
//     EXPECT_EQ(basic2.size(), 4);
//     basic1.merge(basic2);
//     double s1[7] = {-9, -8, -0.5, 22, 23, 55, 78};
//     double *a = s1;
//     for (auto &item : basic1) {
//         EXPECT_DOUBLE_EQ(item, *a++);
//     }
//     EXPECT_EQ(basic1.size(), 7);
//     EXPECT_EQ(basic2.size(), 2);
// }

// TEST(Map, merge_char) {
//     std::map<char, char> basic1{78, 23, -9, -8};
//     std::map<char, char> basic2{55, 22, -8, 0};
//     EXPECT_EQ(basic1.size(), 4);
//     EXPECT_EQ(basic2.size(), 4);
//     basic1.merge(basic2);
//     char s1[7] = {-9, -8, 0, 22, 23, 55, 78};
//     char *a = s1;
//     for (auto &item : basic1) {
//         EXPECT_EQ(item, *a++);
//     }
//     EXPECT_EQ(basic1.size(), 7);
//     EXPECT_EQ(basic2.size(), 1);
// }

// TEST(Map, iterator_find) {
//     std::map<double, double> basic1{78, 23, -9, 22, 22, 22, 23};
//     EXPECT_EQ(basic1.size(), 4);
//     auto iter_22 = basic1.find(22);
//     EXPECT_DOUBLE_EQ(*iter_22, 22);
//     EXPECT_DOUBLE_EQ(*++iter_22, 23);
//     EXPECT_DOUBLE_EQ(*++iter_22, 78);
// }

// TEST(Map, iterator_find2) {
//     std::map<double, double> basic1{78, 7.75, -9, -999, -8, 0.5, 2.88};
//     EXPECT_EQ(basic1.size(), 7);
//     auto iter_22 = basic1.find(-9);
//     EXPECT_DOUBLE_EQ(*iter_22, -9);
//     EXPECT_DOUBLE_EQ(*++iter_22, -8);
//     EXPECT_DOUBLE_EQ(*++iter_22, 0.5);
//     EXPECT_DOUBLE_EQ(*++iter_22, 2.88);
//     EXPECT_DOUBLE_EQ(*++iter_22, 7.75);
// }

// TEST(Map, contains_int) {
//     std::map<int, int> basic1{78, 7, -9, -999, -8, 0, 2};
//     EXPECT_EQ(basic1.size(), 7);
//     EXPECT_TRUE(basic1.contains(-9));
//     EXPECT_TRUE(basic1.contains(-999));
//     EXPECT_TRUE(basic1.contains(0));
//     EXPECT_FALSE(basic1.contains(-33));
//     EXPECT_FALSE(basic1.contains(77));
//     EXPECT_FALSE(basic1.contains(-98));
// }

// TEST(Map, lower_bound_and_upper_bound) {
//     std::map<int, int> basic1{782, 7, -9, -999, -8, 7, 2, 32};
//     EXPECT_EQ(basic1.size(), 7);
//     std::pair pair = {basic1.lower_bound(-9), basic1.upper_bound(32)};
//     char s1[5] = {-9, -8, 2, 7, 32};
//     char *a = s1;
//     int size = 0;
//     while (pair.first != pair.second) {
//         ++size;
//         EXPECT_EQ(*pair.first, *a++);
//         ++pair.first;
//     }
//     EXPECT_EQ(size, 5);
//     EXPECT_EQ(basic1.size(), 7);
// }

// TEST(Map, lower_bound_and_upper_bound2) {
//     std::map<int, int> basic1{782, 7, -9, -999, -8, 7, 2, 32};
//     EXPECT_EQ(basic1.size(), 7);
//     std::pair pair = {basic1.lower_bound(-9), basic1.upper_bound(6)};
//     char s1[3] = {-9, -8, 2};
//     char *a = s1;
//     int size = 0;
//     while (pair.first != pair.second) {
//         ++size;
//         EXPECT_EQ(*pair.first, *a++);
//         ++pair.first;
//     }
//     EXPECT_EQ(size, 3);
//     EXPECT_EQ(basic1.size(), 7);
// }
