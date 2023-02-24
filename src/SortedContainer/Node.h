//
// Created by 12355 on 24.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_NODE_H
#define CPP2_S21_CONTAINERS_0_NODE_H

template <typename Key, typename T>
class Node {
private:
    Key key;
    T value;
    unsigned int balance;
    Node *left, *right;
    Node() : key(0), value(0), balance(0), left(nullptr), right(nullptr) {}
    Node(Key _key, T _value) : key(_key), value(_value) {}
    ~Node() { delete left; delete right; }
};


#endif //CPP2_S21_CONTAINERS_0_NODE_H
