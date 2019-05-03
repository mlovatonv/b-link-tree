#include "b-link-node.hpp"

template <class KeyType, class DataType>
class BLinkTree
{
public: 
    BLinkNode<KeyType, DataType> *root;
  
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

    void split_leaf(BLinkNode<KeyType, DataType> *original_node)
    {
        NodeTuple<KeyType, DataType> *middle_tuple = original_node->divide();
        BLinkNode<KeyType, DataType> *parent_node = new BLinkNode<KeyType, DataType>(NON_LEAF);
        BLinkNode<KeyType, DataType> *next_node = new BLinkNode<KeyType, DataType>(LEAF);

        next_node->start = middle_tuple;
        parent_node->start = new NodeTuple<KeyType, DataType>(middle_tuple->value);
        parent_node->start->left_node = original_node;
        parent_node->start->next = new NodeTuple<KeyType, DataType>(middle_tuple->get_last()->value);
        parent_node->start->next->left_node = next_node;
        original_node->next_node = next_node;

        this->root = parent_node;
    };

    void split_non_leaf()
    {   
        
    };
    
    void remove(KeyType key)
    {};

    void merge()
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