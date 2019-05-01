#include "b-link-node.hpp"

#define K 5

template <class KeyType, class DataType>
class BLinkTree
{
    BLinkNode<KeyType> * root;
public:   
    BLinkTree()
    {
        this->root = new BLinkNode<KeyType>;
    };
    
    void insert(KeyType key, DataType data);
    
    void remove(KeyType key);
    
    void print() 
    {
        std::stack<BLinkNode<KeyType>*> node_stack;
        BLinkNode<KeyType> * top_node;
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
};