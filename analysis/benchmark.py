from datetime import datetime, timedelta
import subprocess
import random
import matplotlib.pyplot as plt


def benchmark_sort(program, input):
    start = datetime.now()
    subprocess.run(program, input=input)
    end = datetime.now()
    return (end - start).total_seconds()


def generate_input(max_value=10000):
    input_dict = {}

    for i in range(1, max_value, 100):
        input = [str(random.randint(1, max_value)) for _ in range(i)]
        input_dict[i] = ' '.join(input).encode()
    
    return input_dict


def main():
    insertion_sort = {}
    merge_sort = {}
    quick_sort = {}

    input_dict = generate_input()

    print('Running simulation...')

    for input_size, input in input_dict.items():
        insertion_sort[input_size] = benchmark_sort(
            './../algorithms/insertion_sort', input)
        merge_sort[input_size] = benchmark_sort(
            './../algorithms/merge_sort', input)
        quick_sort[input_size] = benchmark_sort(
            './../algorithms/quick_sort', input)

    plt.plot(insertion_sort.keys(), insertion_sort.values(), 
             label="Insertion sort")
    plt.plot(merge_sort.keys(), merge_sort.values(),
             label="Merge sort")
    plt.plot(quick_sort.keys(), quick_sort.values(),
             label="Quick sort")
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, 
               mode="expand", borderaxespad=0.)       
    plt.show()


if __name__ == '__main__':
    main()
