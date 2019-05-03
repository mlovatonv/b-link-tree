#include ".hpp"

template <class KeyType, class DataType>
class BLinkNode;

template <class KeyType, class DataType>
struct NodeTuple
{
    KeyType value;
    BLinkNode<KeyType, DataType> *left_node;
    BLinkNode<DataType, DataType> *data_node;
    NodeTuple<KeyType, DataType> *next;

    NodeTuple(KeyType value)
    {
        this->value = value;
        this->left_node = nullptr;
        this->data_node = nullptr;
        this->next = nullptr;
    };

    NodeTuple(KeyType value, DataType data)
    {
        this->value = value;
        this->left_node = nullptr;
        this->data_node = new BLinkNode<DataType, DataType>(DATA);
        this->data_node->start = new NodeTuple<DataType, DataType>(data);
        this->next = nullptr;
    };

    NodeTuple<KeyType, DataType>* get_last()
    {
        NodeTuple<KeyType, DataType> *aux = this;
        while (aux != nullptr && aux->next != nullptr)
        {
            aux = aux->next;
        }
        return aux;
    };
};

template <class KeyType, class DataType>
struct BLinkNode
{
    NodeTuple<KeyType, DataType> *start;
    BLinkNode<KeyType, DataType> *next_node;
    bool is_leaf;
    int entries;

    BLinkNode(bool is_leaf)
    {
        this->start = nullptr;
        this->next_node = nullptr;
        this->is_leaf = is_leaf;
        this->entries = 0;
    };

    void insert(NodeTuple<KeyType, DataType> *new_tuple)
    {
        NodeTuple<KeyType, DataType> *aux1 = this->start;
        NodeTuple<KeyType, DataType> **aux2 = &(this->start);
        while (aux1 != nullptr && aux1->value < new_tuple->value)
        {
            aux2 = &(aux1->next);
            aux1 = aux1->next;
        }
        *aux2 = new_tuple;
        new_tuple->next = aux1;
        ++this->entries;
    };

    void insert(KeyType key) 
    {
        insert(new NodeTuple<KeyType, DataType>(key));
    };

    void insert(KeyType key, DataType data) 
    {
        insert(new NodeTuple<KeyType, DataType>(key, data));
    };

    BLinkNode<KeyType, DataType>* search(KeyType key)
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        while (aux != nullptr && aux->value < key)
        {
            aux = aux->next;
        }
        return aux->left_node;
    }

    NodeTuple<KeyType, DataType>* divide()
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        for (int i = 0; i < (this->entries / 2) - 1; ++i)
        {
            aux = aux->next;
        }
        NodeTuple<KeyType, DataType> *middle_node = aux->next;
        aux->next = nullptr;
        return middle_node;
    };

    NodeTuple<KeyType, DataType>* get_tuple(KeyType value)
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        while (aux != nullptr && aux->value != value)
        {
            aux = aux->next;
        }
        return aux;
    };

    DataType get_data(KeyType value)
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        while (aux != nullptr && aux->value != value)
        {
            aux = aux->next;
        }
        return aux->data_node->start->value;
    }

    void print()
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        std::cout << "{ ";
        while (aux != nullptr)
        {
            std::cout << aux->value << " ";
            aux = aux->next;
        }
        std::cout << "}\n";
    };

};
