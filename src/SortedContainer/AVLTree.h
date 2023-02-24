//
// Created by 12355 on 24.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_AVLTREE_H
#define CPP2_S21_CONTAINERS_0_AVLTREE_H

template <typename Key, typename T>
class AVLTree {

    class Node {
    private:
        Key key;
        T value;
        unsigned int balance{};
        Node *left, *right;
    public:
        Node() : key(0), value(0), balance(0), left(nullptr), right(nullptr) {}
        Node(Key _key, T _value) : key(_key), value(_value) {}
        explicit Node(Key _key) : key(_key) {}
        ~Node() { delete left; delete right; }
    };
private:
    Node *root;
public:
    AVLTree() : root(nullptr) {}
    explicit AVLTree(Key key) { root = new Node(key); }
    explicit AVLTree(Key key, T value) { root = new Node(key, value); }
};


#endif //CPP2_S21_CONTAINERS_0_AVLTREE_H
