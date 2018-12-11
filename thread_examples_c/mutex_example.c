#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define CREATE_MUTEX

int counter=0;
#ifdef CREATE_MUTEX
pthread_mutex_t counter_mutex=PTHREAD_MUTEX_INITIALIZER;
#endif

void* increment(void* ptr){
	for(int i=0; i<1e4; i++)
	{
		if(i%100==0){
			#ifdef CREATE_MUTEX
			pthread_mutex_lock(&counter_mutex);
			counter+=1;
			pthread_mutex_unlock(&counter_mutex);
			#else
			counter+=1;
			#endif
		}
	}
}

int main(int argc,char**argv){
	pthread_t threads[2];
	int num_of_threads=2;
	for(int i=0; i<num_of_threads; i++){
		pthread_create(threads+i,NULL,increment,NULL);
	}
	for(int i=0; i<num_of_threads; i++){
		pthread_join(threads[i],NULL);
	}
	printf("%i\n",counter);
	return EXIT_SUCCESS;
}
