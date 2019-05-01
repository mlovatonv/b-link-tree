#include "b-link-node.hpp"

#define K 5

template <class T>
class BLinkTree
{
    BLinkNode<T> * root;
public:   
    BLinkTree()
    {
        this->root = new BLinkNode<T>;
    };
    
    void insert(T value);
    
    void remove(T value);
    
    void print() 
    {
        std::stack<BLinkNode<T>*> node_stack;
        BLinkNode<T> * top_node;
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