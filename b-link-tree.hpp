#include <limits>

#define K 5

template<class T>
struct Node 
{
    int children_number;
    Node *parent;
    Node *children[K + 1];
    T values[K];
    
    Node()
    {
        children_number = 0;
        parent = nullptr;
        for (int i = 0; i < K; ++i)
        {
            values[i] = std::numeric_limits<T>::max();
            children[i] = nullptr;
        }
    }
};


template <class T>
class B_link_tree
{
    Node<T> * root;
public:   
    B_link_tree();
    void insert(T value);
};