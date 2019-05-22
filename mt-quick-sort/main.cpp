#include <string.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <math.h>
#include <pthread.h>
#include "quickSort_paralelo.hpp"
using namespace std;

int main()
{
    ofstream times, size_p;
    times.open("QuickSort_times.txt");
    size_p.open("QuickSort_sizes.txt");

    int THREADS;
    
    for( THREADS = 1; THREADS < 9; THREADS *= 2 )
    {
        //cout << "threads: " << THREADS << endl;
        long n;
        for( int i = 100; i < 1000000; i = 2 * i)
        {
            n = i;
            int a[n];
            srand(clock());
            for( int i = 0; i < n; ++i)
            {
                a[i] = rand() % (n * 10);
            }
            auto start = chrono::system_clock::now();
            QuickSort(a, n, THREADS);
            auto end = chrono::system_clock::now();
            chrono::duration<float,milli> duration = end - start;
            
            cout << " n : " << n << " | ";
            cout << duration.count() << "ms" << endl;
            
            times << duration.count() << endl;
            size_p << n << endl;
        }
    }
    times.close();
    size_p.close();  

    return 0;
}