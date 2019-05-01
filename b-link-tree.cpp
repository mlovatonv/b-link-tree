#include <iostream>
#include <limits>
#include <stack>

#include "b-link-tree.hpp"

template<class T>
Node<T>::Node(bool _is_leaf)    
{
    is_leaf = _is_leaf;
    children_number = 0;
    parent = nullptr;
    for (int i = 0; i < K; ++i)
    {
        values[i] = std::numeric_limits<T>::max();
        children[i] = nullptr;
    }
};

template<class T>
void Node<T>::print() 
{
    std::cout << "{ ";
    for (int i = 0; i < K; ++i)
    {
        std::cout << values[i] << " ";
    }
    std::cout << "}";
};

template<class T>
BLinkTree<T>::BLinkTree() 
{
    this->root = new Node<T>(LEAF);
};

template<class T>
void BLinkTree<T>::insert(T value) 
{
    this->root
};

template<class T>
void BLinkTree<T>::print() 
{
    std::stack<Node<T>*> node_stack;
    Node<T> * top_node;
    node_stack.push(this->root);
    while (!node_stack.empty())
    {
        top_node = node_stack.top();
        node_stack.pop();

        top_node->print();
        for (int i = 0; i < top_node->children_number; ++i)
        {
            node_stack.push(top_node->children[i]);
        }
    }
};
