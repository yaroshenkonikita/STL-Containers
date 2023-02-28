//
// Created by 12355 on 24.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_AVLTREE_H
#define CPP2_S21_CONTAINERS_0_AVLTREE_H

#include <iostream>
#include "n-dist.h"

template <class Key, class Compare = std::less<Key>>
class AVLTree {

    class Node {
    public:
        Node() = default;
        Node(Value value) : _value(value) {}
        ~Node() { delete _left; delete _right; }
    private:
        using key_type = Key;
        using value_type = Value;
        key_type _key{};
        value_type _value{};
        int _balance{};
        Node *_left{}, *_right{}, *parent{};
    };

    bool empty() {
        if (root == nullptr) {
            return true;
        }
        return false;
    }

private:
    Node *root{};
public:
    AVLTree() = default;
    AVLTree(value_type value) { root = new Node(value); }
    ~AVLTree() { delete root; }

//    AVLTree *a = new AVLTree<int>{1};
};


//std::numeric_limits<type>::max()
#endif //CPP2_S21_CONTAINERS_0_AVLTREE_H
