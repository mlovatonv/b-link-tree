#define K 5

template<class T>
struct Node 
{
    int children_number;
    Node *parent;
    Node *children[K + 1];
    T values[K];
    
    Node();
};


template <class T>
class BLinkTree
{
    Node<T> * root;
public:   
    BLinkTree();
    void insert(T value);
    void remove(T value);
};
