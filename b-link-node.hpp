#include <iostream>
template<class T>
struct NodeTuple
{
    T value;
    NodeTuple<T>* next;
    NodeTuple<T>* AbajoIzq;

    NodeTuple(T value){
        next=nullptr;
        AbajoIzq=nullptr;
        this->value=value;
    };
};

template <class T>
class BLinkNode
{
    int n;
    BLinkNode<T> * right;
    NodeTuple<T> * start;
public:
    BLinkNode(){
        this->start=nullptr;
        n=0;
    };

    void insert(T value){
        NodeTuple<T> *aux_ins= new NodeTuple<T>(value);
        if(start==nullptr){
            this->start=aux_ins;
        } 
        
        else{
            NodeTuple<T>* aux= start;
            if(value < start->value){
                start=aux_ins;
                aux_ins->next=aux;
            }
            else{
                while(aux->next != nullptr && aux->next->value<value){
                    aux=aux->next;
                }
                if(aux->next!=nullptr){
                    NodeTuple<T>* aux2;
                    aux2=aux->next;
                    aux->next=aux_ins;
                    aux_ins->next=aux2;
                }
                else{
                    aux->next=aux_ins;
                    aux_ins->next=nullptr;
                }
            }
        }
        
    };
    void Print(){
        NodeTuple<T>* aux= start;
        while(aux!=nullptr){
            std::cout<<aux->value<<"\n";
            aux=aux->next;
        }
    };
};
