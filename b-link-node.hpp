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

    void insert(KeyType key, DataType data) 
    {
        NodeTuple<KeyType, DataType> *new_tuple = new NodeTuple<KeyType, DataType>(key, data);
        NodeTuple<KeyType, DataType> *aux1 = this->start;
        NodeTuple<KeyType, DataType> **aux2 = &(this->start);
        while (aux1 != nullptr && aux1->value < new_tuple->value)
        {
            aux2 = &(aux1->next);
            aux1 = aux1->next;
        }
        *aux2 = new_tuple;
        new_tuple->next = aux1;
        ++entries;
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

    void print()
    {
        NodeTuple<KeyType, DataType> *aux = this->start;
        std::cout << "{ ";
        while (aux != nullptr)
        {
            std::cout << aux->value << " ";
            aux = aux->next;
        }
        std::cout << "}";
        std::cout<<"\n";
    };
    NodeTuple<KeyType, DataType>* desconectar_tupla(KeyType value){
        auto aux1=this->start;
        auto aux2=this->start->next;
        while(aux2->value<value){
            aux1=aux1->next;
            aux2=aux2->next;
        }
        aux1->next=aux2->next;
        return aux2;
    }
    NodeTuple<KeyType, DataType>* node_tuple(KeyType value){
        auto aux1=this->start;
        while(aux1->value<value){
            aux1=aux1->next;
        }
        return aux1;
    }

};
