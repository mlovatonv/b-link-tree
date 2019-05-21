import matplotlib.pyplot as plt

f = open("QuickSort_times.txt", "r")
a = open("QuickSort_sizes.txt",  "r")


T1=[]
T2=[]
T4=[]
T8=[]
VS=[]

cc=14
for y in range(cc):
	c=a.readline()
	VS.append(c)


for i in range(cc) :
	x=f.readline()
	T1.append(float(x))


for i in range(cc) :
	x=f.readline()
	T2.append(float(x))


for i in range(cc) :
	x=f.readline()
	T4.append(float(x))


for i in range(cc) :
	x=f.readline()
	T8.append(float(x))


plt.title("QuickSort: Time vs n")

plt.plot(VS, T1, label="without parallelism")
plt.plot(VS, T2, label="2 threads")
plt.plot(VS, T4, label="4 threads")
plt.plot(VS, T8, label="8 threads")
plt.xlabel("n")
plt.ylabel("time (ms)")
plt.legend(loc='best')
plt.show()
