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


template <class T>
class Nodo
{
    int n;
    *ValuesN start;

    Nodo(){
        start=nullptr;
        n=0;
    }

    void insert(T value){
        if(start==nullptr){
            ValuesN* aux= new ValuesN();
            aux->value =value;
        }
    }
}

template<class T>
class ValuesN{
private:
    int value;
    *ValuesN next;
    *ValuesN AbajoIzq;
    *ValuesN AbajoDer;
public:
    ValuesN(){
        next=nullptr;
        AbajoDer=nullptr;
        AbajoIzq=nullptr
    }


}
