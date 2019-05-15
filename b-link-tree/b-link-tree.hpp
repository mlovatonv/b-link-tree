#include "b-link-node.hpp"

template <class KeyType, class DataType>
class BLinkTree
{
public: 
    typedef BLinkNode<KeyType, DataType> Node;
    typedef NodeTuple<KeyType, DataType> NodeInNode;
    Node *root;
  
    BLinkTree()
    {
        this->root = new Node(LEAF);
    };

    void insert(KeyType key, DataType data) 
    {
        std::stack<Node> node_stack;
        Node *current = root;
        while (!current->is_leaf)
        {
            node_stack.push(current);
            current = current->scan_node(key);
        }

        // candidate leaf
        // current->lock(); 
        current->move_right();

        if (current->get_tuple(key) != nullptr)
        {
            // key already exists in tree
            return;
        }

        Node *node_to_add = nullptr;
        while (!node_stack.empty())
        {
            if (current->entries <= MAX_ENTRIES) // current is safe
            {
                if (!current->is_leaf)
                {
                    current->insert(key, node_to_add);
                }
                else
                {
                    current->insert(key, data);
                }
                // current->unlock();
            }
            else // must split node
            {
                Node *new_node = new Node(current->is_leaf);
                if (!current->is_leaf)
                {
                    this->rearrange_non_leaf(current, new_node, key, node_to_add);
                }
                else
                {
                    this->rearrange_leaf(current, new_node, key, data);
                }
                KeyType max_value = current->get_last_tuple();
                Node *old_node = current;
                key = max_value;
                node_to_add = new_node;
                current = node_stack.top();
                node_stack.pop();
                // current->lock();
                current->move_right();
                // old_node->unlock();
            }
            
        }
    };

    void rearrange_leaf(Node *current_node, Node *new_node, KeyType key, DataType data)
    {
        current_node->insert(key, data);
        
        new_node->link_pointer = current_node->link_pointer;
        current_node->link_pointer = new_node;

        NodeInNode *middle_tuple = current_node->get_middle_tuple();
        new_node->start = middle_tuple->next;
        middle_tuple->next = nullptr;

        current_node->entries = MAX_ENTRIES / 2;
        new_node->entries = MAX_ENTRIES - current_node->entries;
    }

    void rearrange_non_leaf(Node *current_node, Node *new_node, KeyType key, Node *node_to_add)
    {
        current_node->insert(key);
        
        new_node->link_pointer = current_node->link_pointer;
        current_node->link_pointer = new_node;

        NodeInNode *middle_tuple = current_node->get_middle_tuple();
        new_node->start = middle_tuple->next;
        middle_tuple->next = nullptr;

        current_node->entries = MAX_ENTRIES / 2;
        new_node->entries = MAX_ENTRIES - current_node->entries;
    }
    
    void remove(KeyType key)
    {};

    void merge()
    {};
    
    void print() 
    {
        this->print(this->root);
    };

    void print(Node *node)
    {
        if (node != nullptr)
        {
            node->print();
            NodeInNode *aux = node->start;
            while (aux != nullptr)
            {
                this->print(aux->left_node);
                aux = aux->next;
            }
        }
    };
};