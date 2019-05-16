#include <string.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <math.h>
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
    int middle;
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
    merge(some->v,some->a,some->b,some->middle);

}

void merge_sort(int v[], int a, int b){
    int middle=(b-a)/2 +a+1;
    if(b>a){
        merge_sort(v,a,middle-1);
        merge_sort(v,middle,b);
        merge(v,a,b,middle);
    }
}
void* merge_sort_p(void* all){
    Str* some=(Str*)all;
    merge_sort(some->v,some->a,some->b);

}

void MergeSort(int v[], int n,int THREADS=1){
    if(THREADS==1){
        merge_sort(v,0,n-1);
    }
    else{
        pthread_t threads[THREADS];
        Str all_str[THREADS];
        int pivot=n/THREADS;
        int i=0;
        //todas las estructuras 
        for(i; i<THREADS-1 ; ++i){
            all_str[i].a = i*pivot;
            all_str[i].b = (i+1)*pivot-1;
            all_str[i].v=v;
            all_str[i].n=n-1;
            cout<<i<<" a: "<<all_str[i].a<<" b: "<<all_str[i].b<<endl;
        }
        all_str[i].a = i*pivot;
        all_str[i].b = n-1;
        all_str[i].v=v;
        all_str[i].n=n-1;
        cout<<i<<" a: "<<all_str[i].a<<" b: "<<all_str[i].b<<endl;


        //start of the threads
        for(i=0;i<THREADS;++i){
            pthread_create(&threads[i], NULL,merge_sort_p,&all_str[i]);
        }
        for(i=0;i<THREADS;++i){
            pthread_join(threads[i],NULL);
        }
        //Merge de todas las struct
        int aux2=THREADS;
        int aux=ceil(aux2/2);
        Str all_merge[aux];
        for(i=0;i<aux;i=i+2){
            all_merge[i].v=v;
            all_merge[i].a=all_str[i].a;
            all_merge[i].b=all_str[i+1].b;
            all_merge[i].n=n-1;
            all_merge[i].middle=all_str[i+1].a;
        }
        for(i=0;i<1;++i){
            pthread_create(&threads[i], NULL,merge_p,&all_merge[i]);
        }
        for(i=0;i<1;++i){
            pthread_join(threads[i],NULL);
        }
    }
}



int main(){
    
    int n=20;
    int THREADS=2;
    srand(clock());
    int a[n];
    for(int i=0;i<n;++i){
        a[i]=rand()%(n*10);
    }
    //print_array(a,n);
    auto start = std::chrono::system_clock::now();
    MergeSort(a,n,THREADS);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float,std::milli> duration = end - start;
    cout <<"THREADS: "<<THREADS<<" TIME: "<< duration.count() <<"S"<<endl;

    print_array(a,n);

    return 0;
}


