//
// Created by 12355 on 24.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_AVLTREE_H
#define CPP2_S21_CONTAINERS_0_AVLTREE_H

// #include <iostream>

namespace s21 {
template <class T, class Compare = std::less<Key>>
class multiset {
public:
    // using
    using key_type = T;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

    using size_type = std::size_t;
    using node_type = Node;

    
    using iterator = TreeIterator;
    using const_iterator = TreeConstIterator;

    using allocator_type = std::pmr::polymorphic_allocator<Node>;
    // using pointer = std::allocator_traits<Allocator>::pointer;

    class Node {
    private:
        Node() = default;
        Node(value_type value) : _value(value) {}
        Node(value_type value, Node *node) : _value(value), _parent(node) {}
        Node(Node &node) {
            _key = std::copy(node._key);
            _balance = std::copy(node._balance);
            _right = std::copy(node._right);
            _left = std::copy(node._left);
            _parent = std::copy(node._parent);
        }
        Node(Node &&node) {
            _key = std::exchange(node._key, value_type());
            _balance = std::exchange(node._balance, 0);
            _right = std::exchange(node._right, nullptr);
            _left = std::exchange(node._left, nullptr);
            _parent = std::exchange(node._parent, nullptr);
        }
        ~Node() { allocator_type::deallocate(_left, 1); allocator_type::deallocate(_right, 1); }
        value_type _key{};
        int _balance{};
        Node *_left{}, *_right{}, *_parent{};
    };

    class Iterator;
    class ConstIterator;

    node_type *_root{}, *_begin{}, *_end{};
    size_type _size;

    BinaryTree() { _root = _end = allocator_type::allocate(1); }
    // BinaryTree(const std::initializer_list<value_type>& items) { _root = new Node(value); }
    ~BinaryTree() { allocator_type::deallocate(root, 1); }

    insert() {
        Node *current_node = _root;
        if (current_node != _end) {
        } else {
            _root = allocator_type::allocate(1);
            _root._right = current_node;
        }
    }
    bool empty() {
        return _size == 0;
    }
    size_type max_size() {
        return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
    }
    class iterator<Node> {
        Node *iterator_node{};
    }

//    BinaryTree *a = new BinaryTree<int>{1};
};

} // namespace s21


//std::numeric_limits<type>::max()
#endif //CPP2_S21_CONTAINERS_0_AVLTREE_H
