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
        NodeTuple<KeyType, DataType> *middle_tuple = original_node->get_middle_tuple();
        BLinkNode<KeyType, DataType> *parent_node = new BLinkNode<KeyType, DataType>(NON_LEAF);
        parent_node->insert(middle_tuple->value);
        parent_node->insert(middle_tuple->get_last()->value);
        parent_node->start->left_node = original_node;

        original_node->next_node = new BLinkNode<KeyType, DataType>(LEAF);
        parent_node->start->next->left_node = original_node->next_node;
        original_node->next_node->start = middle_tuple->next;
        middle_tuple->next = nullptr;

        int initial_entries = original_node->entries;
        original_node->entries = initial_entries / 2;
        original_node->next_node->entries = initial_entries - original_node->entries;

        this->root = parent_node;
    };

    void split_non_leaf()
    {   
        auto aux = this->root->start;
        NodeTuple<KeyType, DataType>* aux_tuple;
        for(int i=0;i<(this->root->entries)/2;++i){
            aux=aux->next;
        }
        aux_tuple=aux;
        this->root->desconectar_tupla(aux->value);

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