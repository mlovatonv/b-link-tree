from datetime import datetime, timedelta
import subprocess
import random
import matplotlib.pyplot as plt


def benchmark_sort(program, input):
    start = datetime.now()
    subprocess.run(program, input=input)
    end = datetime.now()
    return (end - start).total_seconds()


def generate_input(max_value=500000):
    input_dict = {}

    for i in range(10000, max_value, 10000):
        input = [str(random.randint(1, max_value)) for _ in range(i)]
        input_dict[i] = (str(i) + ' ' + ' '.join(input)).encode()
    return input_dict


def main():
    only_insert = {}
    insert_search = {}

    input_dict = generate_input()

    print('Running simulation...')

    for input_size, input in input_dict.items():
        only_insert[input_size] = benchmark_sort(
            '../b-link-tree/only_insert', input)
    
    for input_size, input in input_dict.items():
        insert_search[input_size] = benchmark_sort(
            '../b-link-tree/insert_search', input)

    plt.plot(only_insert.keys(), only_insert.values(), 
             label="Insert")   
    plt.plot(insert_search.keys(), insert_search.values(), 
             label="Insert and search")
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2,
               mode="expand", borderaxespad=0.) 
    plt.xlabel('n')
    plt.ylabel('time (seconds)')
    plt.show()


if __name__ == '__main__':
    main()
