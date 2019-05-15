#include <string.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <map>
#include <pthread.h>
using namespace std;

void print_array(int v[],int n){
    for(int i=0;i<n;++i){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

typedef struct{
    int* v;
    int n;
    int a;
    int b;
}Str;

void merge(int v[], int a, int b, int middle){
    int counter1=middle-a;
    int counter2=b- middle +1;

    int I[counter1];
    int D[counter2];
    for(int i=0;i<counter1;++i){
        I[i]=v[i+a];
    }
    for(int i=0;i<counter2;++i){
        D[i]=v[i+middle];
    }

    int pi=0;
    int pd=0;
    int ite=a;
    while(pi<counter1 && pd<counter2){
        if(I[pi] <= D[pd]){
            v[ite]=I[pi];
            ++pi;

        }else{
            v[ite]=D[pd];
            ++pd;
        }
        ++ite;
    }
    while(pi < counter1){
        v[ite]=I[pi];
        ++pi;
        ++ite;
    }
    while(pd < counter2){
        v[ite]=D[pd];
        ++pd;
        ++ite;
    }

}
/*
typedef struct{
    vector<int> *v;
    int a;
    int b;
}Str;
*/

void merge_sort(int v[], int a, int b){
    int middle=(b-a)/2 +a+1;
    if(b>a){
        merge_sort(v,a,middle-1);
        merge_sort(v,middle,b);
        merge(v,a,b,middle);
    }
}
void* merge_sort_C2(void* all){
    Str* some=(Str*)all;
    int a=some->a;
    int b=some->b;
    int middle=(b-a)/2 +a+1;
    if(b>a){
        merge_sort(some->v,a,middle-1);
        merge_sort(some->v,middle,b);
        merge(some->v,a,b,middle);
    }
}

void MergeSort(int v[], int n,int hilos=1){
    if(hilos==1){
        merge_sort(v,0,n-1);
    }
    if(hilos==2){
        int middle=(n/2);
        Str Struct1,Struct2;

        Struct1.a=0;
        Struct1.b=middle-1;
        Struct1.v=v;
        Struct1.n= n-1;

        Struct2.a=middle;
        Struct2.b=n-1;
        Struct2.v=v;
        Struct2.n=n-1;

        int THREADS=2;
        pthread_t threads[THREADS];
        pthread_create(&threads[0], NULL,merge_sort_C2,&Struct1);
        pthread_create(&threads[1], NULL,merge_sort_C2,&Struct2);
        for(int i=0;i<THREADS;++i){
            pthread_join(threads[i],NULL);
        }
        merge(v,0,n-1,middle);

    }
    if(hilos == 4){

    }
}



int main(){
    
    int n=4;
    int a[n]={7,6,3,2};
    print_array(a,n);
    MergeSort(a,n,2);
    print_array(a,n);

    return 0;
}


