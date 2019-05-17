#include "b-link-node.hpp"
#include <pthread.h>


pthread_mutex_t mutex3;
pthread_mutex_t mutex4;
pthread_mutex_t mutex5;
pthread_barrier_t our_barrier;


template <class KeyType, class DataType>
class BLinkTree
{
private:
    typedef BLinkNode<KeyType, DataType> Node;
    typedef NodeTuple<KeyType, DataType> NodeInNode;

    Node *root;
public: 
    BLinkTree()
    {
        this->root = new Node(LEAF);
    };

    DataType search(KeyType key, DataType _default)
    {
        Node *current = root;
        while (!current->is_leaf) // find a candidate leaf
        {
            current = current->scan_node(key);
        }
        while (!current->is_leaf && current->scan_node(key) == current->link_pointer)
        {
            current = current->link_pointer;
        }
        return current->get_data(key, _default);
    }

    void insert(KeyType key, DataType data) 
    {
        std::stack<Node*> node_stack;
        Node *current = root;
        Node *aux = nullptr;
        Node *link_node = nullptr;
        while (!current->is_leaf) // find a candidate leaf
        {
            aux = current;
            current = current->scan_node(key);
            if (current != aux->link_pointer)
            {
                node_stack.push(aux);
            }
        }
 
        move_right(current, key);
        if (current->get_tuple(key) != nullptr)
        {
            return; // key already exists in tree
        }

        // current->lock();
        while (current)
        {
            if (current->entries < MAX_ENTRIES) // current is safe
            {
                if (!current->is_leaf)
                {
                    current->insert_non_leaf(key, link_node);
                }
                else
                {
                    current->insert_leaf(key, data);   
                }
                // current->unlock();
                return;
            }
            else // must split node
            {
                Node *new_node = new Node();
                if (!current->is_leaf)
                {
                    key = this->rearrange_non_leaf(current, new_node, key, link_node);
                }
                else
                {
                    new_node->is_leaf = true;
                    key = this->rearrange_leaf(current, new_node, key, data);
                }
                aux = current;
                link_node = new_node;
                if (!node_stack.empty())
                {
                    current = node_stack.top();
                    node_stack.pop();
                    // current->lock();
                    move_right(current, key);
                }
                else 
                {
                    current = nullptr;
                }
                // aux->unlock();
            }
        }

        Node *new_root_node = new Node();
        NodeTuple<KeyType, DataType> *left = new NodeTuple<KeyType, DataType>(key);
        NodeTuple<KeyType, DataType> *right = new NodeTuple<KeyType, DataType>(link_node->get_last_tuple()->value);
        new_root_node->insert(left);
        new_root_node->insert(right);
        new_root_node->start->left_node = this->root;
        new_root_node->start->next->left_node = link_node;
        this->root = new_root_node;
        // current->unlock();
    };

    void move_right(Node* current, KeyType key)
    {
        Node* aux;
        while (current && current->scan_node(key) == current->link_pointer)
        {
            aux = current->scan_node(key);
            // aux->lock();
            // current->unlock();
            current = aux;
        }
    }

    KeyType rearrange_leaf(Node *current_node, Node *new_node, KeyType key, DataType data)
    {
        current_node->insert_leaf(key, data);
        return this->rearrange(current_node, new_node);
    }

    KeyType rearrange_non_leaf(Node *current_node, Node *new_node, KeyType key, Node *link_node)
    {
        current_node->insert_non_leaf(key, link_node);
        return this->rearrange(current_node, new_node);
    }

    KeyType rearrange(Node *current_node, Node *new_node)
    {
        new_node->link_pointer = current_node->link_pointer;
        current_node->link_pointer = new_node;

        NodeInNode *middle_tuple = current_node->get_middle_tuple();
        new_node->start = middle_tuple->next;
        middle_tuple->next = nullptr;

        int entries = current_node->entries;
        current_node->entries = entries / 2;
        new_node->entries = entries - current_node->entries;

        return middle_tuple->value;   
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