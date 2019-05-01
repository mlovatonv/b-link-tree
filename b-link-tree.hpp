#define K 5
#define LEAF true
#define NOT_LEAF false

template<class T>
struct Node 
{
    bool is_leaf;
    int children_number;
    T values[K];
    Node * parent;
    Node * children[K + 1];
    
    Node(bool _is_leaf);
    void print();
};


template <class T>
class BLinkTree
{
    Node<T> * root;
public:   
    BLinkTree();
    void insert(T value);
    void remove(T value);
    void print();
};
