import matplotlib.pyplot as plt

f = open("QS_p.txt", "r")

vector_size=[10,100,1000,10000,10000,1000000]
T1=[]
T2=[]
T4=[]


for i in range(6) :
	x=f.readline()
	T1.append(float(x))

for i in range(6) :
	x=f.readline()
	T2.append(float(x))

for i in range(6) :
	x=f.readline()
	T4.append(float(x))



plt.title("Time vs n")

plt.plot(vector_size, T1, label="without parallelism")
plt.plot(vector_size, T2, label="2 threads")
plt.plot(vector_size, T4, label="4 threads")
plt.xlabel("n")
plt.ylabel("time (ms)")
plt.legend(loc='best')
plt.show()
