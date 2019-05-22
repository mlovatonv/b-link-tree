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

void print_array(int v[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

void Full_str(Str* aux, int a, int b, int v[], int n)
{
    aux->a = a;
    aux->b = b;
    aux->v = v;
    aux->n = n;
}

void swap(int &a, int &b)
{
    int aux = b;
    b = a;
    a = aux;
}

int partition(int v[], int a, int b)
{
    if(b > a)
    {
        int pivot = v[b];
        int i = a-1;
        int j = a;
        for(; j<b; ++j){
            if(v[j] <= pivot){
                ++i;
                swap(v[i],v[j]);
            }
        }
        swap(v[i+1],v[b]);
    return i+1;
    }
}

void* partition_p(void* all)
{
    Str *some = (Str*)all;
    int x = partition(some->v, some->a, some->b);
    some->part_v = x;
}

void quick_sort(int v[], int a, int b)
{
    if(b > a)
    {
        int already = partition(v,a,b);
        quick_sort(v, a, already-1);
        quick_sort(v, already, b);
    }
}
void* quick_sort_p(void* all)
{
    Str *some = (Str*)all;
    quick_sort(some->v, some->a, some->b);
}

void QuickSort(int v[], int n, int THREADS=1)
{
    if(THREADS == 1)
    {
        quick_sort(v, 0, n-1);
    }
    if(THREADS == 2)
    {
        pthread_t threads[THREADS];   
        int y = partition(v, 0, n-1);
        Str all_str[THREADS];
        Full_str(&all_str[0], 0, y-1, v, n-1);
        Full_str(&all_str[1], y+1, n-1, v, n-1);

        for(int i = 0; i < THREADS; ++i)
        {
            pthread_create(&threads[i], NULL,quick_sort_p, (void*)(&all_str[i]));
        }
        for(int k2 = 0; k2 < THREADS; ++k2)
        {
            pthread_join(threads[k2],NULL);
        }
    }
    if(THREADS == 4)
    {
        pthread_t threads[THREADS];
        int a=partition(v, 0, n-1);
        Str str_f[2];

        Full_str(&str_f[0], 0, a-1, v, n-1);
        Full_str(&str_f[1], a+1, n-1, v, n-1);
        
        for(int i = 0; i < 2; ++i)
        {
            pthread_create(&threads[i], NULL, partition_p, (void*)(&str_f[i]));
        }
        for(int k2 = 0; k2 < 2; ++k2){
            pthread_join(threads[k2], NULL);
        }
        int b = str_f[0].part_v;
        int c = str_f[1].part_v;


        Str all_str[THREADS];
        Full_str(&all_str[0], 0, b-1, v, n-1);
        Full_str(&all_str[1], b+1, a-1, v, n-1);
        Full_str(&all_str[2], a+1, c-1, v, n-1);
        Full_str(&all_str[3], c+1, n-1, v, n-1);
        for(int i = 0; i < THREADS; ++i)
        {
            pthread_create(&threads[i], NULL, quick_sort_p, (void*)(&all_str[i]));
        }
        for(int k2 = 0; k2 < THREADS; ++k2)
        {
            pthread_join(threads[k2], NULL);
        }
    }
    if(THREADS == 8)
    {
        pthread_t threads[THREADS];
        int all_values[THREADS-1];
        int a = partition(v, 0, n-1);
        Str str_f[8];
        all_values[0] = a;

        Full_str(&str_f[0], 0, a - 1, v, n - 1);
        Full_str(&str_f[1], a + 1, n - 1, v, n - 1);

        for(int i = 0; i < 2; ++i)
        {
            pthread_create(&threads[i], NULL, partition_p, (void*)(&str_f[i]));
        }
        for(int k2 = 0; k2 < 2; ++k2){
            pthread_join(threads[k2], NULL);
        }

        all_values[1] = str_f[0].part_v;
        all_values[2] = str_f[1].part_v;

        Full_str(&str_f[2], 0, all_values[1] - 1, v, n - 1);
        Full_str(&str_f[3], all_values[1] + 1, all_values[0] - 1, v, n - 1);
        Full_str(&str_f[4], all_values[0] + 1, all_values[2] - 1, v, n - 1);
        Full_str(&str_f[5], all_values[2] + 1, n - 1, v, n - 1);

        for(int i = 0; i < 4; ++i)
        {
            pthread_create(&threads[i], NULL, partition_p, (void*)(&str_f[i+2]));
        }
        for(int k2 = 0; k2 < 4; ++k2)
        {
            pthread_join(threads[k2], NULL);
        }
        all_values[3] = str_f[2].part_v;
        all_values[4] = str_f[3].part_v;
        all_values[5] = str_f[4].part_v;
        all_values[6] = str_f[5].part_v;

        Full_str(&str_f[0], 0, all_values[3] - 1, v, n - 1);
        Full_str(&str_f[1], all_values[3] + 1, all_values[1] - 1, v, n - 1);
        Full_str(&str_f[2], all_values[1] + 1, all_values[4] - 1, v, n - 1);
        Full_str(&str_f[3], all_values[4] + 1, all_values[0] - 1, v, n - 1);
        Full_str(&str_f[4], all_values[0] + 1, all_values[5] - 1, v, n - 1);
        Full_str(&str_f[5], all_values[5] + 1, all_values[2] - 1, v, n - 1);
        Full_str(&str_f[6], all_values[2] + 1, all_values[6] - 1, v, n - 1);
        Full_str(&str_f[7], all_values[6] + 1, n - 1, v, n - 1);

        for(int i = 0; i < THREADS; ++i)
        {
            pthread_create(&threads[i], NULL, quick_sort_p, (void*)(&str_f[i]));
        }
        for(int k2 = 0; k2 < THREADS; ++k2)
        {
            pthread_join(threads[k2], NULL);
        }

    }

}
