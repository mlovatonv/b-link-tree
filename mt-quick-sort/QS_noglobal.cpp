#include <vector>
#include <iostream>
#include <sys/time.h>
#include <fstream>
#include <pthread.h>

using namespace std;

bool first=true;

typedef struct
{
	int a;
	int b;
	int *v;
	int n;
	int part_v;

}Str;

void print_array(int v[],int n){
	for(int i=0;i<n;++i){
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

void swap(int &a, int &b){
	int aux=b;
	b=a;
	a=aux;
}

int partition(int v[], int a, int b){
	int pivot=v[b];
	int i=a-1;
	int j=a;
	for(;j<b;++j){
		if(v[j] <= pivot){
			++i;
			swap(v[i],v[j]);
		}
	}
	swap(v[i+1],v[b]);
	return i+1;
}

void* partition_p(void* all){
	Str *some=(Str*)all;
	int x=partition(some->v,some->a,some->b);
	some->part_v=x;
}

void quick_sort(int v[], int a, int b){
	if(b>a){
		int already=partition(v,a,b);
		quick_sort(v,a,already-1);
		quick_sort(v,already,b);
	}
}
void* quick_sort_p(void* all){
	Str *some=(Str*)all;
	quick_sort(some->v,some->a,some->b);
}

void* quick_sort_p_2C(void* some){
	ALL *all= (ALL*)some;
	int izq=all->izq;
	int der=all->der;
	if(izq < der){
		int alreadysort= partition(all);
		ALL A1, A2;
		A1.izq=izq;
		A1.der=alreadysort-1;
		A1.v=all->v;
		A2.izq=alreadysort+1;
		A2.der=der;
		A2.v=all->v;	
		if(first){
			first=false;
			pthread_t threads[THREADS];

			pthread_create(&threads[0], NULL,quick_sort_p_2C,(void*)(&A1));
			pthread_create(&threads[1], NULL,quick_sort_p_2C,(void*)(&A2));
			
			for(int i=0;i<THREADS;++i){
				pthread_join(threads[i],NULL);
			}
		}
		else{
			quick_sort_p_2C(&A1);
			quick_sort_p_2C(&A2);
		}
	}
}


void QuickSort(int v[],int n,int THREADS=1){
	if(THREADS==1){
		quick_sort(v,0,n-1);
	}
}

int main(){
	int VECTOR_SIZE=1000;

		struct timeval start,end;
		srand(clock());
		ALL P1;
		std::vector<int> v1;
		P1.v=&(v1);
		P1.izq=0;
		P1.der=VECTOR_SIZE-1;

		for(int i=0;i<VECTOR_SIZE;++i){
			int aux2=rand()%VECTOR_SIZE;
			(P1.v)->push_back(aux2);
		}
		//print:
		vector<int> vaux=*(P1.v);
		for(int i=0;i<VECTOR_SIZE;++i){
			cout<<vaux[i]<<" ";
		}
		cout<<endl<<endl;
		quick_sort_p_2C(&P1);
		
		vaux=*(P1.v);
		for(int i=0;i<VECTOR_SIZE;++i){
			cout<<vaux[i]<<" ";
		}
		cout<<endl;


		/*

	
*/
return 0;

}