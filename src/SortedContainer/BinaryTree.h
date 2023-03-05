//
// Created by 12355 on 24.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_BINARYTREE_H
#define CPP2_S21_CONTAINERS_0_BINARYTREE_H

#include <iostream>

#include <memory_resource>
#include <functional>
#include <limits>

namespace s21 {
template <class Key, class Compare = std::less<Key>>
class BinaryTree {
public:
    class TreeIterator;
    class TreeConstIterator;
private:
    // node body ================================================================
    class Node {
    public:
        Node() = default;
        explicit Node(Key key) : _key(key) {}
        Node(Key key, Node *node) : _key(key), _parent(node) {}
        ~Node() { delete _left; delete _right; }
        Key _key{};
        int _balance{};
        Node *_left{}, *_right{}, *_parent{};
    };



public:
    // pre-implementation =======================================================

    // using ====================================================================
    using key_type = Key;
    using value_type = Key;
    using reference = value_type&;
    using const_reference = const value_type&;

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using node_type = Node;
    using iterator = TreeIterator;
    using const_iterator = TreeConstIterator;



    BinaryTree() { _root = _end = new Node(); }
    BinaryTree(const std::initializer_list<value_type>& items) {
         _root = _end = new Node();
        for (value_type item : items) {
            insert(item);
        }
    }
    ~BinaryTree() { delete _root; }

    void clear() {
        delete _root;
        _root = _end = new Node();
        _begin = nullptr;
    }

    iterator lower_bound(const_reference key) {

    }

    iterator insert(const_reference key) {
        Node *current_node = _root;
        if (current_node == _end) {
            current_node = _begin = _root = new Node(key);
            current_node->_right = _end;
        } else {
            while (true) {
                if (Compare{}(key, current_node->_key)) {
                    if (current_node->_left != nullptr) {
                        current_node = current_node->_left;
                    } else {
                        current_node->_left = new Node(key, current_node);
                        if (current_node == _begin) {
                            _begin = current_node->_left;
                        }
                        break;
                    }
                } else if (current_node->_right != nullptr && current_node->_right != _end) {
                    current_node = current_node->_right;
                } else {
                    if (current_node->_right == _end) {
                        current_node->_right = new Node(key, current_node);
                        current_node->_right->_right = _end;
                    } else {
                        current_node->_right = new Node(key, current_node);
                    }
                    break;
                }
            }
        }
        ++_size;
    }
    bool empty() {
        return _size == 0;
    }
    size_type max_size() {
        return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
    }
private:
    node_type *_root{}, *_begin{}, *_end{};
    size_type _size{};
};

// iterators ================================================================
template <typename Key, typename Compare>
class BinaryTree<Key, Compare>::TreeIterator {
public:
private:

};

template <typename Key, typename Compare>
class BinaryTree<Key, Compare>::TreeConstIterator {

};

} // namespace s21

#endif //CPP2_S21_CONTAINERS_0_BINARYTREE_H
