#include "b-link-node.hpp"
#include <pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;
pthread_mutex_t mutex4;
pthread_mutex_t mutex5;

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

    DataType search(KeyType key)
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
        return current->get_data(key);
    }

    void insert(KeyType key, DataType data) 
    {
        std::stack<Node*> node_stack;
        Node *current = root;
        Node *aux = nullptr;
        while (!current->is_leaf) // find a candidate leaf
        {
            aux = current;
            current = current->scan_node(key);
            if (current != aux->link_pointer)
            {
                node_stack.push(current);
            }
        }
 
        move_right(current, key);
        if (current->get_tuple(key) != nullptr)
        {
            return; // key already exists in tree
        }
        pthread_mutex_lock(&mutex1);
        current;
        //current->lock();
        Node *link_node = nullptr;

        // leaf case
        if (current->entries < MAX_ENTRIES)
        {
            current->insert_leaf(key, data);
            pthread_mutex_unlock(&mutex1);

            //current->unlock();
            return;
        }
        else
        {
            pthread_mutex_unlock(&mutex1);
            //current->unlock();
            Node *new_node = new Node(LEAF);
            key = this->rearrange_leaf(current, new_node, key, data);
            link_node = new_node;
            pthread_mutex_lock(&mutex2);
            if (!node_stack.empty())
            {
                aux = current;
                current = node_stack.top();
                node_stack.pop();
                // current->lock();
                move_right(current, key);
                // aux->unlock();
            }

        }

        // non-leaf case
        while (!node_stack.empty())
        {
            if (current->entries < MAX_ENTRIES) // current is safe
            {
                current->insert_non_leaf(key, link_node);
                link_node = nullptr;
                // current->unlock();
                pthread_mutex_unlock(&mutex2);
            }
            else // must split node
            {
                Node *new_node = new Node();
                key = this->rearrange_non_leaf(current, new_node, key, link_node);
                aux = current;
                link_node = new_node;
                current = node_stack.top();
                node_stack.pop();
                pthread_mutex_lock(&mutex3);
                // current->lock();
                move_right(current, key);
                // aux->unlock();
            }
        }
        pthread_mutex_unlock(&mutex2);

        if (link_node)
        {
            Node *new_node = new Node();
            NodeTuple<KeyType, DataType> *left = new NodeTuple<KeyType, DataType>(key);
            NodeTuple<KeyType, DataType> *right = new NodeTuple<KeyType, DataType>(link_node->get_last_tuple()->value);
            new_node->insert(left);
            new_node->insert(right);
            new_node->start->left_node = this->root;
            new_node->start->next->left_node = link_node;
            this->root = new_node;
            // current->unlock();
            pthread_mutex_unlock(&mutex3);
        }
    };

    void move_right(Node* current, KeyType key)
    {
        Node* aux;
        pthread_mutex_lock(&mutex4);
        while (current && current->scan_node(key) == current->link_pointer)
        {
            aux = current->scan_node(key);
            // aux->lock();
            // current->unlock();
            current = aux;
        }
        pthread_mutex_unlock(&mutex4);
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

        current_node->entries = MAX_ENTRIES / 2;
        new_node->entries = MAX_ENTRIES - current_node->entries;

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