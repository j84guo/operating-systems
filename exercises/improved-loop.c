#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 400 

void *threadFunc(void *arg){
	int *a = (int*) arg;
	int myNum = *a;
	printf("Thread number %d\n", myNum);
	return 0;
}

int main(void){
	
	int i;

	pthread_t tid[NUM_THREADS];
	int arr[NUM_THREADS];

	//order is still not guaranteed but we have unique numbers per thread
	for(int i=0; i<NUM_THREADS; i++){
		arr[i] = i;
		pthread_create(&tid[i], NULL, threadFunc, &arr[i]);
	}

	for(int i=0; i<NUM_THREADS; i++){
		pthread_join(tid[i], NULL);
	}

	return 0;
}