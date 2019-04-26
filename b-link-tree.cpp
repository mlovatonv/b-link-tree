#include <limits>

#include "b-link-tree.hpp"

template<class T>
Node<T>::Node()    
{
    children_number = 0;
    parent = nullptr;
    for (int i = 0; i < K; ++i)
    {
        values[i] = std::numeric_limits<T>::max();
        children[i] = nullptr;
    }
};

template<class T>
BLinkTree<T>::BLinkTree() 
{
    this->root = new Node<T>();
};
