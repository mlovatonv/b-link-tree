#include <iostream>

#define LEAF true
#define NON_LEAF false

template <class T>
class BLinkNode;

template <class T>
struct NodeTuple
{
    T value;
    NodeTuple<T> *next;
    BLinkNode<T> *left_node;

    NodeTuple(T value)
    {
        this->value = value;
        this->next = nullptr;
        this->left_node = nullptr;
    };
};

template <class T>
struct BLinkNode
{
    NodeTuple<T> *start;
    BLinkNode<T> *next_node;
    bool m;
    int entries;

    BLinkNode(bool is_leaf)
    {
        this->start = nullptr;
        this->next_node = nullptr;
        this->m = is_leaf;
        this->entries = 0;
    };

    void insert(T value)
    {
        NodeTuple<T> *aux_ins = new NodeTuple<T>(value);
        if (start == nullptr)
        {
            this->start = aux_ins;
        } 
        else
        {
            NodeTuple<T> *aux = start;
            if (value < start->value)
            {
                start = aux_ins;
                aux_ins->next = aux;
            }
            else
            {
                while (aux->next != nullptr && aux->next->value < value)
                {
                    aux = aux->next;
                }
                if (aux->next != nullptr)
                {
                    NodeTuple<T> *aux2;
                    aux2 = aux->next;
                    aux->next = aux_ins;
                    aux_ins->next = aux2;
                }
                else
                {
                    aux->next = aux_ins;
                    aux_ins->next = nullptr;
                }
            }
        }
        ++entries;
    };

    void print()
    {
        NodeTuple<T> *aux = start;
        while (aux != nullptr)
        {
            std::cout << aux->value << "\n";
            aux = aux->next;
        }
    };
};
