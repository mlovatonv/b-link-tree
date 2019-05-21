import matplotlib.pyplot as plt

Q1 = open("../mt-quick-sort/QuickSort_times.txt", "r")
Q2 = open("../mt-quick-sort/QuickSort_sizes.txt",  "r")

I1 = open("../mt-merge-sort/ms_time.txt", "r")
#I2 = open("../mt-merge-sort/ms_sizes.txt",  "r")

VS=[]

cc=14

for y in range(cc):
	c=Q2.readline()
	VS.append(c)

for z in range(4):
	Qs=[]
	Is=[]
	for i in range(cc) :
		x=Q1.readline()
		Qs.append(float(x))

	for i in range(cc) :
		x=I1.readline()
		Is.append(float(x))

	plt.title("QuickSort vs MergeSort")
	plt.plot(VS, Qs, label="QuickSort")
	plt.plot(VS, Is, label="MergeSort")
	plt.xlabel("n")
	plt.ylabel("time (ms)")
	plt.legend(loc='best')
	plt.show()
