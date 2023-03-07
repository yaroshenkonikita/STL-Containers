//
// Created by 12355 on 24.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_BINARYTREE_H
#define CPP2_S21_CONTAINERS_0_BINARYTREE_H

#include  <iostream>

//#include <memory_resource>
//#include <functional>
//#include <limits>

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
    using const_iterator = const TreeIterator;



    BinaryTree() {
        _end->_right = _begin = _root = _end = new Node();
    }
    BinaryTree(const std::initializer_list<value_type>& items) {
        _begin = _root = _end = new Node();
        for (value_type item : items) {
            insert(item);
        }
    }
    ~BinaryTree() { delete _root; }

    void clear() {
        delete _root;
        _begin = _root = _end = new Node();
        _size = 0;
    }

    iterator lower_bound(const_reference key) {
        return TreeIterator(begin()); // недоделка
    }

    iterator insert(const_reference key) {
        Node *current_node = _root;
        if (current_node == _end) {
            current_node = _begin = _root = new Node(key);
            current_node->_right = _end;
            _end->_right = current_node;
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

    iterator begin() const noexcept {
        return TreeIterator(_begin);
    }

    iterator end() const noexcept {
        return TreeIterator(_end);
    }

    iterator cbegin() const noexcept {
        return TreeIterator(_begin);
    }

    iterator cend() const noexcept {
        return TreeIterator(_end);
    }

    bool empty() {
        return _size == 0;
    }

    size_type max_size() {
        return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
    }
protected:
    node_type *_root{}, *_begin{}, *_end{};
    size_type _size{};
};

// iterators ================================================================

template <class Key, class Compare>
class BinaryTree<Key, Compare>::TreeIterator {
public:
    TreeIterator() = delete;
    explicit TreeIterator(node_type* current) : current_node(current) {}
    ~TreeIterator() = default;

    Key operator*() {
        if (current_node == this->_end) {
            return this->_size;
        } else if (current_node == nullptr) {
            throw std::out_of_range("Дружище, ты куда собрался?"); // такого случая не должно быть
        }
        return current_node->_key;
    }

    TreeIterator operator++() {
        if (current_node->_right != nullptr) {
            current_node = current_node->_right;
        } else {
            node_type *last_position = current_node;
            current_node = current_node->_parent;
            if (current_node == nullptr) {
                throw std::out_of_range("Ты сирота, а ну в детский дом!!"); // такого случая не должно быть
            }
            while (current_node->_right == last_position || current_node->_right != nullptr) {
                last_position = current_node;
                current_node = current_node->_parent;
            }
            current_node = current_node->_right;
        }
        return *this;
    }

    TreeIterator operator--() {
        if (current_node == this->_begin) {
            current_node = this->_end;
        } else if (current_node->_left != nullptr) {
            current_node = current_node->_left;
        } else {
            node_type *last_position = current_node;
            current_node = current_node->_parent;
            if (current_node == nullptr) {
                throw std::out_of_range("Ты сирота, а ну в детский дом!!"); // такого случая не должно быть
            }
            while (current_node->_left == last_position || current_node->_left != nullptr) {
                last_position = current_node;
                current_node = current_node->_parent;
            }
            current_node = current_node->_left;
        }
        return *this;
    }

    bool operator!=(TreeIterator &other) {
        return other.current_node != current_node;
    }

    bool operator==(TreeIterator &other) {
        return other.current_node == current_node;
    }

private:
    node_type *current_node{};
};

template <typename Key, typename Compare>
class BinaryTree<Key, Compare>::TreeConstIterator {

};

} // namespace s21

#endif //CPP2_S21_CONTAINERS_0_BINARYTREE_H
