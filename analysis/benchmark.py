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

    for i in range(100, max_value, 100):
        input = [str(random.randint(1, max_value)) for _ in range(i)]
        input_dict[i] = str(i) + ' ' + ' '.join(input)
    return input_dict


def main():
    five = {}
    ten = {}
    fifteen = {}

    input_dict = generate_input()

    print('Running simulation...')

    # for input_size, input in input_dict.items():
    #     five[input_size] = benchmark_sort(
    #         '../b-link-tree/b-link-tree', ('5 ' + input).encode())
    for input_size, input in input_dict.items():
        ten[input_size] = benchmark_sort(
            '../b-link-tree/b-link-tree', ('10 ' + input).encode())
    # for input_size, input in input_dict.items():
    #     fifteen[input_size] = benchmark_sort(
    #         '../b-link-tree/b-link-tree', ('125 ' + input).encode())

    # plt.plot(five.keys(), five.values(),
    #          label="b = 5")
    plt.plot(ten.keys(), ten.values(),
             label="b = 10")
    # plt.plot(fifteen.keys(), fifteen.values(),
    #          label="b = 125")
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2,
               mode="expand", borderaxespad=0.)
    plt.xlabel('n')
    plt.ylabel('time (seconds)')
    plt.show()


if __name__ == '__main__':
    main()
