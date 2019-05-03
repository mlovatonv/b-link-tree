#include "b-link-node.hpp"

template <class KeyType, class DataType>
class BLinkTree
{
    BLinkNode<KeyType, DataType> *root;
public:   
    BLinkTree()
    {
        this->root = new BLinkNode<KeyType, DataType>(LEAF);
    };

    void insert(KeyType key, DataType data) 
    {
        BLinkNode<KeyType, DataType> *aux_node = root;
        NodeTuple<KeyType, DataType> *aux_tuple;
        // while (!aux_node->is_leaf)
        // {
        //     while (aux_tuple )
        // }
    };
    
    void remove(KeyType key);
    
    void print() 
    {};

    void print(BLinkNode<KeyType, DataType> *node)
    {};
};