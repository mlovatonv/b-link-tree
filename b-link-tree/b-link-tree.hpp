#include "b-link-node.hpp"

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
 
        // current->move_right();
        if (current->get_tuple(key) != nullptr)
        {
            return; // key already exists in tree
        }

        // current->lock();
        Node *link_node = nullptr;

        // leaf case
        if (current->entries < MAX_ENTRIES)
        {
            current->insert_leaf(key, data);
            // current->unlock();
            return;
        }
        else
        {
            Node *new_node = new Node(LEAF);
            key = this->rearrange_leaf(current, new_node, key, data);
            link_node = new_node;
            if (!node_stack.empty())
            {
                aux = current;
                current = node_stack.top();
                node_stack.pop();
                // current->lock();
                // current->move_right();
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
            }
            else // must split node
            {
                Node *new_node = new Node();
                key = this->rearrange_non_leaf(current, new_node, key, link_node);
                aux = current;
                link_node = new_node;
                current = node_stack.top();
                node_stack.pop();
                // current->lock();
                // current->move_right();
                // aux->unlock();
            }
        }

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
        }
    };

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