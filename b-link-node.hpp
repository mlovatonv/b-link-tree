#include <iostream>
template<class T>
class ValuesN{
public:
    T value;
    ValuesN<T>* next;
    ValuesN<T>* AbajoIzq;
    ValuesN<T>* AbajoDer;

    ValuesN(T value){
        std::cout<<value<<"\n";
        next=nullptr;
        AbajoDer=nullptr;
        AbajoIzq=nullptr;
        this->value=value;
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
        ValuesN<T> *aux_ins= new ValuesN<T>(value);
        if(start==nullptr){
            this->start=aux_ins;
        } 
        
        else{
            ValuesN<T>* aux= start;
            while(aux->next != nullptr && aux->next->value<value){
                aux=aux->next;
            }
            if(aux->next!=nullptr){
                ValuesN<T>* aux2;
                aux2=aux->next;
                aux->next=aux_ins;
                aux_ins->next=aux2;
            }
            else{
                aux->next=aux_ins;
                aux_ins->next=nullptr;
            }
        }
        
    };
    void Print(){
        ValuesN<T>* aux= start;
        while(aux!=nullptr){
            std::cout<<aux->value<<"\n";
            aux=aux->next;
        }
    };
};
