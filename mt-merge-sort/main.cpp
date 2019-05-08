#include <iostream>
#include <limits>
#define INT_MAX 2147483647

void merge(int array[], int p, int q, int r)
{
    int left_length = q - p + 1, 
        right_length = r - q;

    int left[left_length + 1], right[right_length + 1];

    for (int i = 0; i < left_length; ++i) 
    {
        left[i] = array[p - 1 + i];
    }

    for (int j = 0; j < right_length; ++j) 
    {
        right[j] = array[q + j];
    }

    left[left_length] = INT_MAX;
    right[right_length] = INT_MAX;

    int i = 0, j = 0;
    for (int k = p - 1; k < r; ++k) 
    {
        if (left[i] <= right[j])
        {
            array[k] = left[i];
            ++i;
        }
        else 
        {
            array[k] = right[j];
            ++j;
        }
    }
}

void merge_sort(int array[], int p, int r) 
{
    if (p < r) 
    {
        int q = (p + r) / 2;
        merge_sort(array, p, q);
        merge_sort(array, q + 1, r);
        merge(array, p, q, r);
    }
}

int main() 
{
    int size = 5;
    int foo[size] = {2, 4, 1, 6, 0};

    merge_sort(foo, 1, size);

    for (auto &x : foo) 
    {
        std::cout << x << " ";
    }
    
    return 0;
}
