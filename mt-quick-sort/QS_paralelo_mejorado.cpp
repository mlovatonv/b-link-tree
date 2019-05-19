#include <string.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <math.h>
#include <pthread.h>
using namespace std;

typedef struct
{
    int a;
    int b;
    int *v;
    int n;
    int part_v;

}Str;

void print_array(int v[],int n){
    for(int i=0;i<n;++i){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

void Full_str(Str* aux,int a,int b,int v[],int n){
    aux->a=a;
    aux->b=b;
    aux->v=v;
    aux->n=n;
}

void swap(int &a, int &b){
    int aux=b;
    b=a;
    a=aux;
}

int partition(int v[], int a, int b){
    int pivot=v[b];
    int i=a-1;
    int j=a;
    for(;j<b;++j){
        if(v[j] <= pivot){
            ++i;
            swap(v[i],v[j]);
        }
    }
    swap(v[i+1],v[b]);
    return i+1;
}

void* partition_p(void* all){
    Str *some=(Str*)all;
    int x=partition(some->v,some->a,some->b);
    some->part_v=x;
}

void quick_sort(int v[], int a, int b){
    if(b>a){
        int already=partition(v,a,b);
        quick_sort(v,a,already-1);
        quick_sort(v,already,b);
    }
}
void* quick_sort_p(void* all){
    Str *some=(Str*)all;
    quick_sort(some->v,some->a,some->b);
}
void* QuickSort_p(void* all){
    Str* some=(Str*)all;
    quick_sort(some->v,some->n,some->part_v);
}

void QuickSort(int v[], int n,int THREADS=1){
    if(THREADS==1)
    {
        quick_sort(v,0,n-1);
    }
    if(THREADS==2)
    {
        pthread_t threads[THREADS];   
        int y=partition(v,0,n-1);
        Str all_str[THREADS];
        Full_str(&all_str[0],0,y-1,v,n-1);
        Full_str(&all_str[1],y+1,n-1,v,n-1);

        for(int i=0;i<THREADS;++i){
            pthread_create(&threads[i], NULL,quick_sort_p,(void*)(&all_str[i]));
        }
        for(int k2=0;k2<THREADS;++k2){
            pthread_join(threads[k2],NULL);
        }
    }
    if(THREADS==4)
    {
        pthread_t threads[THREADS];
        int a=partition(v,0,n-1);
        Str str_f[2];

        Full_str(&str_f[0],0,a-1,v,n-1);
        Full_str(&str_f[1],a+1,n-1,v,n-1);
        
        for(int i=0;i<2;++i){
            pthread_create(&threads[i], NULL,partition_p,(void*)(&str_f[i]));
        }
        for(int k2=0;k2<2;++k2){
            pthread_join(threads[k2],NULL);
        }
        int b=str_f[0].part_v;
        int c=str_f[1].part_v;


        Str all_str[THREADS];
        Full_str(&all_str[0],0,b-1,v,n-1);
        Full_str(&all_str[1],b+1,a-1,v,n-1);
        Full_str(&all_str[2],a+1,c-1,v,n-1);
        Full_str(&all_str[3],c+1,n-1,v,n-1);
        for(int i=0;i<THREADS;++i){
            pthread_create(&threads[i], NULL,quick_sort_p,(void*)(&all_str[i]));
        }
        for(int k2=0;k2<THREADS;++k2){
            pthread_join(threads[k2],NULL);
        }
    }

}


int main()
{
    ofstream file;
    file.open("QS_p.txt");
    int THREADS;
    for(THREADS=1;THREADS<6;THREADS*=2){
        int n;
        for(int i=10;i<10000000;i=10*i){
            n=i;
            int a[n];
            srand(clock());
            for(int i=0;i<n;++i){
                a[i]= rand()%(n*10);
            }
            //print_array(a,n);
            auto start = chrono::system_clock::now();
            QuickSort(a,n,THREADS);
            auto end = chrono::system_clock::now();
            chrono::duration<float,milli>duration= end - start;
            //print_array(a,n);
            cout<<duration.count()<<"ms"<<endl;
            file<<duration.count()<<endl;
        }
    }

    return 0;
}
