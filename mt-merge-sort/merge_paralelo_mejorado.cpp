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
    //int middle=(some->b-some->a)/2 +some->a+1;
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
        for(i; i<THREADS ; ++i){
            all_str[i].a = i*pivot;
            all_str[i].b = (i+1)*pivot-1;
            all_str[i].v=v;
            all_str[i].n=n-1;
            cout<<"i . "<<i<<endl;
            cout<<" v "<<all_str[i].v<<endl;
            cout<<" a "<<all_str[i].a<<endl;
            cout<<" b "<<all_str[i].b<<endl;
        }
        all_str[i-2].b = n-1;
        //start of the threads
        for(int k=0;k<THREADS;++k){
            pthread_create(&threads[k], NULL,merge_sort_p,&all_str[k]);
        }
        for(int k2=0;k2<THREADS;++k2){
            pthread_join(threads[k2],NULL);
        }

        //Merge de todas las struct
        int aux2=THREADS;
        int aux=ceil(aux2/2);//2

        int cada_cuanto=1;
        Str all_merge[THREADS-1];

        for(i=0;i<aux;++i){
            all_merge[i].v=v;
            all_merge[i].a=all_str[2*i].a;
            all_merge[i].b=all_str[2*i+1].b;
            all_merge[i].n=n-1;
            all_merge[i].middle=all_str[2*i+1].a;
            cout<<i<<endl;
            cout<<" v "<<all_merge[i].v<<endl;
            cout<<" a "<<all_merge[i].a<<endl;
            cout<<" b "<<all_merge[i].b<<endl;
            cout<<" m "<<all_merge[i].middle<<endl;

        }
        cout<<i;
        //++cada_cuanto;
        for(int j=0;j<aux;++j){
            cout<<"hete"<<endl;
            pthread_create(&threads[j], NULL,merge_p,&all_merge[j]);
        }
        for(int j=0;j<aux;++j){
            pthread_join(threads[j],NULL);
        }
        
        int ite_aux=i;
        i=0;
        
        while(aux!=1){
            aux=ceil(aux/2);//1
                for(int y=0;y<aux;++y){
                all_merge[y+i].v=v;
                all_merge[y+i].a=all_merge[2*(y)].a;
                all_merge[y+i].b=all_merge[2*(y)+1].b;
                all_merge[y+i].n=n-1;
                all_merge[y+i].middle=all_merge[2*(y)+1].a;

                cout<<"y: "<<y+i<<endl;
                cout<<" v "<<all_merge[y+i].v<<endl;
                cout<<" a "<<all_merge[y+i].a<<endl;
                cout<<" b "<<all_merge[y+i].b<<endl;
                cout<<" middle "<<all_merge[y+i].middle<<endl;
                ++ite_aux;
            }
            for(int j=0;j<aux;++j){
                cout<<"a "<<all_merge[j+i].a<<endl;
                cout<<"b "<<all_merge[j+i].b<<endl;
                cout<<"middle "<<all_merge[j+i].middle<<endl;
                pthread_create(&threads[j], NULL,merge_p,&all_merge[j+i]);
            }
            for(int j=0;j<aux;++j){
                pthread_join(threads[j],NULL);
            }
        }
        
        
    }
}



int main(){
    
    int n=32;
    int THREADS=16;
    srand(clock());
    int a[n];
    for(int i=0;i<n;++i){
        a[i]=rand()%(n*10);
    }
    print_array(a,n);
    auto start = std::chrono::system_clock::now();
    MergeSort(a,n,THREADS);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float,std::milli> duration = end - start;
    cout <<"THREADS: "<<THREADS<<" TIME: "<< duration.count() <<"S"<<endl;

    print_array(a,n);

    return 0;
}


