#include "b-link-tree.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <pthread.h>
#include <vector>
using namespace std;

typedef struct{
    BLinkTree<int, std::string> *btree;
    int *v1;
    string *v2;
    int n;
}DATAX;

void* insert_parallel(void * all){
    DATAX* some=(DATAX*)all;
    for(int i=0;i<some->n;++i){
        some->btree->insert(*(some->v1 + i),*(some->v2 +1));
    }
}
int main()
{
    // BLinkTree<int, std::string> tree;
    // int THREADS=2;
    // pthread_mutex_init(&mutex1, NULL);
    // pthread_mutex_init(&mutex2, NULL);
    
    // int n=5;
    // int all_keys[n]={1,2,3,4,5};
    // string all_data[n]={"a","b","c","d","e"};
    // int all_keys2[n]={11,12,13,14,15};
    // string all_data3[n]={"a","b","c","d","e"};

    // DATAX stru1,stru2;
    // stru1.btree=&tree;
    // stru2.btree=&tree;
    // stru1.n=n;
    // stru2.n=n;
    // stru1.v1=all_keys;
    // stru2.v1=all_keys2;
    // stru1.v2=all_data;
    // stru2.v2=all_data3;

    // pthread_t threads[THREADS];
    // pthread_create(&threads[0], NULL,insert_parallel,(void*)(&stru1));
    // pthread_create(&threads[1], NULL,insert_parallel,(void*)(&stru2));

    // for(int i=0;i<THREADS;++i){
    //     pthread_join(threads[i],NULL);
    // }

    BLinkTree<int, int> tree;
    int n, x, threads = 2;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        tree.insert(x, x);
    }
    return 0;
}
