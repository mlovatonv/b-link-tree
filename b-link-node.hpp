template<class T>
class ValuesN{
private:
    T value;
    ValuesN<T>* next;
    ValuesN<T>* AbajoIzq;
    ValuesN<T>* AbajoDer;
public:
    ValuesN(){
        next=nullptr;
        AbajoDer=nullptr;
        AbajoIzq=nullptr;
    };
};

template <class T>
class BLinkNode
{
    int n;
    ValuesN<T> *start;

public:
    BLinkNode(){
        this->start=nullptr;
        n=0;
    };

    void insert(T value){
        if(start==nullptr){
            ValuesN<T>* aux= new ValuesN<T>(value);
        }
    };
};
