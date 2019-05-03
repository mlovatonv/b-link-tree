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
        while (!aux_node->is_leaf)
        {
            aux_node = aux_node->search(key);
        }
        aux_node->insert(key, data);
    };

    void split_leaf()
    {};

    void split_non_leaf()
    {};
    
    void remove(KeyType key)
    {};
    
    void print() 
    {
        this->print(this->root);
    };

    void print(BLinkNode<KeyType, DataType> *node)
    {
        if (node != nullptr)
        {
            node->print();
            NodeTuple<KeyType, DataType> *aux = node->start;
            while (aux != nullptr)
            {
                this->print(aux->left_node);
                aux = aux->next;
            }
        }
    };
};