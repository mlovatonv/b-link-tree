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
        this->data_node = new BLinkNode<DataType, DataType>();
        this->data_node->start = new NodeTuple<DataType, DataType>(data);
        this->next = nullptr;
    };
};

template <class KeyType, class DataType>
struct BLinkNode
{
    NodeTuple<KeyType, DataType> *start;
    BLinkNode<KeyType, DataType> *link_pointer;
    bool is_leaf;
    int entries;

    BLinkNode(bool is_leaf = false)
    {
        this->start = nullptr;
        this->link_pointer = nullptr;
        this->is_leaf = is_leaf;
        this->entries = 0;
    };

    void insert_leaf(KeyType key, DataType data)
    {
        NodeTuple<KeyType, DataType> *new_tuple = new NodeTuple<KeyType, DataType>(key, data);
        this->insert(new_tuple);
    }

    void insert_non_leaf(KeyType key, BLinkNode<KeyType, DataType> *link_node)
    {
        BLinkNode<KeyType, DataType> *old_node = nullptr;
        NodeTuple<KeyType, DataType> *new_tuple = new NodeTuple<KeyType, DataType>(key);
        this->insert(new_tuple);

        old_node = new_tuple->next->left_node;
        new_tuple->next->left_node = link_node;
        new_tuple->left_node = old_node;
    }

    void insert(NodeTuple<KeyType, DataType> *new_tuple)
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        NodeTuple<KeyType, DataType> **aux2 = &(this->start);
        while (aux != nullptr && aux->value < new_tuple->value)
        {
            aux2 = &(aux->next);
            aux = aux->next;
        }
        *aux2 = new_tuple;
        new_tuple->next = aux;
        ++this->entries;
    }

    BLinkNode<KeyType, DataType>* scan_node(KeyType key)
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        while (aux != nullptr && aux->value < key)
        {
            aux = aux->next;
        }
        return aux ? aux->left_node : this->link_pointer;
    }

    NodeTuple<KeyType, DataType>* get_middle_tuple()
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        for (int i = 0; i < (this->entries / 2) - 1; ++i)
        {
            aux = aux->next;
        }
        NodeTuple<KeyType, DataType> *middle_tuple = aux;
        return middle_tuple;
    };

    NodeTuple<KeyType, DataType>* get_last_tuple()
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        while (aux != nullptr && aux->next != nullptr)
        {
            aux = aux->next;
        }
        return aux;
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

    DataType get_data(KeyType value, DataType _default)
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        while (aux != nullptr && aux->value != value)
        {
            aux = aux->next;
        }
        return aux ? aux->data_node->start->value : _default;
    }

    void print()
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        std::cout << "{ ";
        if (this->is_leaf)
        {
            std::cout << "M ";
        }
        while (aux != nullptr)
        {
            std::cout << aux->value << " ";
            aux = aux->next;
        }
        std::cout << "}\n";
    };

};
