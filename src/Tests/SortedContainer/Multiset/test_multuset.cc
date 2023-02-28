#include <gtest/gtest.h>

#include <algorithm>
// #include <iostream>

TEST(Multiset, default_constructor) {
    std::multiset<int> basic;
    basic.insert(5);
    basic.insert(20);
    basic.insert(2);
    int s[3] = {2, 5, 20};
    int *a = s;
    for (auto &item : basic) {
        EXPECT_EQ(item, *a++);
    }
}

TEST(Multiset, initializator_constructor_int) {
    std::multiset<int> basic = {6, 4, 2, 8, 0, -228};
    int s[6] = {-228, 0, 2, 4, 6, 8};
    int *a = s;
    for (auto &item : basic) {
        EXPECT_EQ(item, *a++);
    }
}

TEST(Multiset, initializator_constructor_double) {
    std::multiset<double> basic = {999, 6, 3, 2, 90, 0, -1};
    double s[7] = {-1, 0, 2, 3, 6, 90, 999};
    double *a = s;
    for (auto &item : basic) {
        EXPECT_DOUBLE_EQ(item, *a++);
    }
}

TEST(Multiset, initializator_constructor_char) {
    std::multiset<char> basic = {'c', 'd', 'a', 'b'};
    char s[4] = {'a', 'b', 'c', 'd'};
    char *a = s;
    for (auto &item : basic) {
        EXPECT_TRUE(item == *a++);
    }
}

TEST(Multiset, copy_constructor_int) {
    std::multiset<int> basic = {6, 4, 2, 8, 0, -228};
    std::multiset<int> copy{basic};
    int s[6] = {-228, 0, 2, 4, 6, 8};
    int *a = s;
    for (auto &item : copy) {
        EXPECT_EQ(item, *a++);
    }
    EXPECT_EQ(basic.size(), copy.size());
}

TEST(Multiset, move_constructor_int) {
    std::multiset<int> basic = {6, 4, 2, 8, 0, -228};
    std::multiset<int> move{std::move(basic)};
    int s[6] = {-228, 0, 2, 4, 6, 8};
    int *a = s;
    for (auto &item : move) {
        EXPECT_EQ(item, *a++);
    }
    EXPECT_EQ(basic.size(), 0);
    EXPECT_EQ(move.size(), 6);
}

TEST(Multiset, move_operator_int) {
    std::multiset<int> basic = {6, 4, 2, 8, 0, -228};
    std::multiset<int> move = std::move(basic);
    int s[6] = {-228, 0, 2, 4, 6, 8};
    int *a = s;
    for (auto &item : move) {
        EXPECT_EQ(item, *a++);
    }
    EXPECT_EQ(basic.size(), 0);
    EXPECT_EQ(move.size(), 6);
}

TEST(Multiset, iterator_begin_end) {
    std::multiset<int> basic = {6, 4, 2, 8, 0, -228};
    auto iter = basic.begin();
    auto iter_end = basic.end();
    int s[6] = {-228, 0, 2, 4, 6, 8};
    int *a = s;
    while (iter != iter_end) {
        EXPECT_EQ(*iter++, *a++);
    }
    EXPECT_EQ(basic.size(), 6);
}

TEST(Multiset, empty) {
    std::multiset<int> basic;
    EXPECT_TRUE(basic.empty());
    basic.insert(4);
    EXPECT_FALSE(basic.empty());
}

// TEST(Multiset, iterator_begin_end_except) {
//     std::multiset<int> basic = {9, 4, 2, 8, 0, -228, 6};
//     auto iter = basic.begin();
//     auto iter_end = basic.end();
//     int s[6] = {-228, 0, 2, 4, 3, 8};
//     // int *a = s;
//     printf("%d\n\n", *iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     printf("%d\n\n", *--iter_end);
//     // EXPECT_ANY_THROW();
//     // EXPECT_ANY_THROW(*iter_end);
//     // EXPECT_ANY_THROW(iter_end++);
// }

TEST(Multiset, pipez) {
    std::map<int, int> exp = {{1, 1}};
    std::map<int, int> exp2 = {{1, 1}};
    printf("%d\n\n", exp < exp2);
    printf("%d\n\n", exp > exp2);
    printf("%d\n\n", exp == exp2);


    // std::map<std::map<int, int>, int> basic = {{exp, 2}, 2};
    // auto iter = basic.begin();
    // printf("%d\n\n", *iter);
    // auto iter_end = basic.end();
    // int s[6] = {-228, 0, 2, 4, 6, 8};
    // int *a = s;
    // while (iter != iter_end) {
    //     EXPECT_EQ(*iter++, *a++);
    // }
    // EXPECT_EQ(basic.size(), 6);
}