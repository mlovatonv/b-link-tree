#include <string.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <math.h>
#include <pthread.h>
using namespace std;

void print_array( int v[] , int n )
{
    for (int i = 0; i < n; ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

typedef struct{
    int* v;
    int n;
    int a;
    int b;
    int middle;
} Str;

void Full_str(Str* aux, int a, int b, int v[], int n, int m=0)
{
    aux->a = a;
    aux->b = b;
    aux->v = v;
    aux->n = n;
    aux->middle = m;
}

void Debug_str(Str* aux){
    cout << aux->a << " " << aux->b << " " << aux->middle << endl;
}


void merge(int v[], int a, int b, int middle)
{
    int counter1 = middle - a;
    int counter2 = b - middle + 1;

    int I[counter1];
    int D[counter2];
    for (int i = 0; i < counter1; ++i)
    {
        I[i] = v[i + a];
    }
    for (int i = 0; i < counter2; ++i)
    {
        D[i]=v[i + middle];
    }

    int pi = 0;
    int pd = 0;
    int ite = a;
    while (pi < counter1 && pd < counter2)
    {
        if (I[pi] <= D[pd])
        {
            v[ite] = I[pi];
            ++pi;

        }else{
            v[ite] = D[pd];
            ++pd;
        }
        ++ite;
    }
    while (pi < counter1)
    {
        v[ite] = I[pi];
        ++pi;
        ++ite;
    }
    while (pd < counter2)
    {
        v[ite] = D[pd];
        ++pd;
        ++ite;
    }

}
void* merge_p(void* all )
{
    Str* some = (Str*)all;
    //int middle=(some->b-some->a)/2 +some->a+1;
    merge( some->v, some->a, some->b, some->middle);

}

void merge_sort(int v[], int a, int b)
{
    int middle = (b - a)/2 + a + 1;
    if (b > a)
    {
        merge_sort(v, a, middle - 1);
        merge_sort(v, middle, b);
        merge(v, a, b, middle);
    }
}
void* merge_sort_p(void* all)
{
    Str* some = (Str*)all;
    merge_sort( some->v, some->a, some->b);

}

void MergeSort(int v[], int n, int THREADS = 1)
{
    if (THREADS == 1)
    {
        merge_sort( v, 0, n - 1);
    }
    else
    {
        pthread_t threads[THREADS];
        Str all_str_init[THREADS];
        int pivot = n / THREADS;
        int i = 0;
        //todas las estructuras 
        for (i; i < THREADS; ++i)
        {
            Full_str(&all_str_init[i], i*pivot, (i + 1)*pivot - 1, v, n-1 );
        }
        all_str_init[i - 2].b = n - 1;
        //start of the threads
        for (int k = 0; k < THREADS; ++k)
        {
            pthread_create(&threads[k], NULL, merge_sort_p, &all_str_init[k]);
        }
        for (int k2 = 0; k2 < THREADS; ++k2)
        {
            pthread_join( threads[k2], NULL);
        }
        //Merge de todas las struct

        int aux = THREADS / 2;//2

        int control_2=1;
        int control = 2;
        
        while(aux >0){
            int cada_cuanto = pow(2,control_2) - 1;
            Str all_merge[aux];
            for(i = 0; i < aux; ++i ){
                Full_str( &all_merge[i], all_str_init[i * control].a, all_str_init[i*control + cada_cuanto].b, v, n-1, all_str_init[i*control + (cada_cuanto-1)/2 +1].a);
                //Debug_str( &all_merge[i] );
            }

            for (int k = 0; k < aux; ++k)
            {
                pthread_create(&threads[k], NULL, merge_p, &all_merge[k]);
            }
            for (int k2 = 0; k2 < aux; ++k2)
            {
                pthread_join( threads[k2], NULL);
            }

            ++control_2;
            control=control*2;
            aux = aux / 2;
        }
    }
}
    

