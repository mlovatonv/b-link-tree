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
void* merge_p(void* all){
    Str* some=(Str*)all;
    int middle=(some->b-some->a)/2 +some->a+1;
    merge(some->v,some->a,some->b,middle);

}

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
        int pivot=(n/4);

        Str Struct1,Struct2,Struct3,Struct4,Struct5,Struct6;

        Struct1.a=0;
        Struct1.b=pivot-1;
        Struct1.v=v;
        Struct1.n= n-1;

        Struct2.a=pivot;
        Struct2.b=pivot*2 -1;
        Struct2.v=v;
        Struct2.n=n-1;

        Struct3.a=pivot*2;
        Struct3.b=pivot*3-1;
        Struct3.v=v;
        Struct3.n=n-1;

        Struct4.a=pivot*3;
        Struct4.b=n-1;
        Struct4.v=v;
        Struct4.n=n-1;

        Struct5.a=0;
        Struct5.b=pivot*2-1;
        Struct5.v=v;
        Struct5.n= n-1;

        Struct6.a=pivot*2;
        Struct6.b=n-1;
        Struct6.v=v;
        Struct6.n=n-1;

        int THREADS=4;
        pthread_t threads[THREADS];
        pthread_create(&threads[0], NULL,merge_sort_C2,&Struct1);
        pthread_create(&threads[1], NULL,merge_sort_C2,&Struct2);
        pthread_create(&threads[2], NULL,merge_sort_C2,&Struct3);
        pthread_create(&threads[3], NULL,merge_sort_C2,&Struct4);
        for(int i=0;i<THREADS;++i){
            pthread_join(threads[i],NULL);
        }
        pthread_create(&threads[0], NULL,merge_p,&Struct5);
        pthread_create(&threads[1], NULL,merge_p,&Struct6);
        for(int i=0;i<2;++i){
            pthread_join(threads[i],NULL);
        }
        merge(v,0,n-1,pivot*2);
    }
}



int main(){
    
    int n=1000000;
    int THREADS=1;
    srand(clock());
    int a[n];
    for(int i=0;i<n;++i){
        a[i]=rand()%(n*10);
    }
    //print_array(a,n);
    cout<<endl;
    auto start = std::chrono::system_clock::now();
    MergeSort(a,n,THREADS);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float,std::milli> duration = end - start;
    cout <<"THREADS: "<<THREADS<<" TIME: "<< duration.count() <<"S"<<endl;

    //print_array(a,n);

    return 0;
}


