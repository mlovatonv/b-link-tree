#include <vector>
#include <iostream>
#include <sys/time.h>
#include <fstream>
#include <pthread.h>

using namespace std;

int THREADS=2;
bool first=true;

typedef struct
{
	int izq;
	int der;
	vector<int> *v;

}ALL;

int partition(ALL *some){
	vector<int> v;
	v=(*(some->v));
	int der=some->der;
	int izq=some->izq;
	int x=(*(some->v))[der];
	int i=izq-1;
	for(int j=izq;j<der;++j){
		if((*(some->v))[j]<=x){
			++i;
			int temp=(*(some->v))[i];
			(*(some->v))[i]=(*(some->v))[j];
			(*(some->v))[j]=temp;
		}
	}
	int temp2=(*(some->v))[i+1];
	(*(some->v))[i+1]=(*(some->v))[der];
	(*(some->v))[der]=temp2;
	return(i+1);
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