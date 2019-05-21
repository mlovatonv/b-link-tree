#include <string.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <math.h>
#include <pthread.h>
#include "mergeSort_paralelo.hpp"
using namespace std;

int main()
{
    ofstream file, size;
    file.open("ms_time.txt");
    size.open("ms_sizes.txt");
    int THREADS;
    
    for (THREADS = 1; THREADS < 9; THREADS *= 2)
    {
        int n;
        for (int i = 100; i < 1000000; i = 2 * i)
        {
            n = i;
            int a[n];
            srand(clock());
            for (int i = 0; i < n; ++i)
            {
                a[i] = rand() % (n * 10);
            }
            //print_array(a,n);
            auto start = chrono::system_clock::now();
            MergeSort( a, n, THREADS);
            auto end = chrono::system_clock::now();
            chrono::duration<float,milli>duration = end - start;
            //print_array(a,n);
            cout << duration.count() << "ms" << endl;
            file << duration.count() << endl;
            size << n << endl;
        }
    }
    return 0;
}
