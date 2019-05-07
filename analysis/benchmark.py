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
    b_link_tree = {}
    mt_insertion_sort = {}
    mt_quick_sort = {}

    input_dict = generate_input()

    print('Running simulation...')

    for input_size, input in input_dict.items():
        b_link_tree[input_size] = benchmark_sort(
            '../b-link-tree/main.cpp', input)
        mt_insertion_sort[input_size] = benchmark_sort(
            '../mt-insertion-sort/main.cpp', input)
        mt_quick_sort[input_size] = benchmark_sort(
            '../mt_quick_sort', input)

    plt.plot(b_link_tree.keys(), b_link_tree.values(), 
             label="B-link-tree")
    plt.plot(mt_insertion_sort.keys(), mt_insertion_sort.values(),
             label="MT Insertion Sort")
    plt.plot(mt_quick_sort.keys(), mt_quick_sort.values(),
             label="MT Quicksort")
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, 
               mode="expand", borderaxespad=0.)       
    plt.show()


if __name__ == '__main__':
    main()
