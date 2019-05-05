#include <vector>
#include <iostream>
#include <sys/time.h>
#include <fstream>
#include <pthread.h>

using namespace std;

int THREADS=2;
bool first=true;
vector<int> v;
vector<int> B;

int partition(int izq, int der){
	int x=v[der];
	int i=izq-1;
	for(int j=izq;j<der;++j){
		if(v[j]<=x){
			++i;
			int temp=v[i];
			v[i]=v[j];
			v[j]=temp;
		}
	}
	int temp2=v[i+1];
	v[i+1]=v[der];
	v[der]=temp2;
	return(i+1);
}

void quick_sort(int izq, int der){
	if(izq < der){
		int alreadysort= partition(izq, der);
		quick_sort(izq,alreadysort-1);
		quick_sort(alreadysort+1,der);
	}
}



void* quick_sort_p_2C(void* some){
	int *all= (int*)some;
	int izq=*(all);
	int der=*(all+2);
	if(izq < der){	
		int alreadysort= partition(izq, der);
		if(first){
			long arr1[2]={izq,alreadysort-1};
			long arr2[2]={alreadysort+1,der};
			first=false;
			pthread_t threads[THREADS];

			pthread_create(&threads[0], NULL,quick_sort_p_2C,(void*)(arr1));
			pthread_create(&threads[1], NULL,quick_sort_p_2C,(void*)(arr2));
			
			for(int i=0;i<THREADS;++i){
				pthread_join(threads[i],NULL);
			}
		}
		else{
			quick_sort(izq,alreadysort-1);
			quick_sort(alreadysort+1,der);
		}	
	}
}




int main(){
	int VECTOR_SIZE=100000;

		struct timeval start,end;
		srand(clock());
		for(int i=0;i<VECTOR_SIZE;++i){
			int aux2=rand()%VECTOR_SIZE;
			v.push_back(aux2);
			//B.push_back(aux2);
		}
		//print:
		for(int i=0;i<VECTOR_SIZE;++i){
			cout<<v[i]<<" ";
		}
		cout<<endl;
		long arr[2]={0,VECTOR_SIZE-1};
		quick_sort_p_2C(arr);
		for(int i=0;i<VECTOR_SIZE;++i){
			cout<<v[i]<<" ";
		}
		cout<<endl;


		/*

		time_t time;
		cout<<"Vector size: "<<VECTOR_SIZE<<endl;
		gettimeofday(&start,NULL);
		long arr[3]={A,0,VECTOR_SIZE-1}
		quick_sort_p_2C()
		gettimeofday(&end,NULL);
		long long  aux;
		aux=((end.tv_sec)-(start.tv_sec))*1000000;
		aux+=((end.tv_usec)-(start.tv_usec));
		cout<<" Time quick_sort parallel: "<<(long double)aux/1000000.0;
		cout<<endl;


		gettimeofday(&start,NULL);
		quick_sort(B,0,VECTOR_SIZE-1);
		gettimeofday(&end,NULL);
		aux=((end.tv_sec)-(start.tv_sec))*1000000;
		aux+=((end.tv_usec)-(start.tv_usec));
		cout<<" Time quick_sort : "<<(long double)aux/1000000.0;
		cout<<endl;

*/
return 0;

}