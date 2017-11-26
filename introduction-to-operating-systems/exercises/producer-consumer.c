/*
*	The producer consumer problem is when a many threads produce and one consumes.
*	Rather than having the consumer constantly trying to lock the mutex (expensive)
*	we let it sleep until the resource is ready to read through condition variables
*       as well as the wait(), signal(), broadcast() functions
*	Note that the mutex locks the resource (and info variables) itself.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUF_SIZE 3

int buffer[BUF_SIZE]; // shared buffer
int add = 0; // index to add
int rem = 0; // index to remove
int num = 0; // list size

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; // mutex for shared array
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER; // consumer waits on this condition
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER; // producer waits on this condition

// function signatures
void *producer(void *param);
void *consumer(void *param);

// main function takes the number of arguments and an array of them, including file name
int main(int argc, char* argv[]){

	// thread data structures
	pthread_t t1;
	pthread_t t2;

	int i;

	// create function runs the thread starting from the given method
	if(pthread_create(&t1, NULL, producer, NULL) != 0){
		fprintf(stderr, "Unable to create producer thread\n");
		exit(1);
	}

        // create function runs the thread starting from the given method
	if(pthread_create(&t2, NULL, consumer, NULL) != 0){
		fprintf(stderr, "Unable to create consumer thread\n");
		exit(1);
	}

	pthread_join(t1, NULL); // wait for producer
	pthread_join(t2, NULL); // wait for consumer
	printf("main thread quitting\n");
}

void* producer(void* param){

	int i;
	for(int i=1; i<=20; i++){

		// critical section
		pthread_mutex_lock(&m);

			// overflow
			if(num > BUF_SIZE){
				exit(1);
			}

			// wait needs a mutex pointer so it knows which object to unlock on entering wait and lock on exiting wait
			// note the while loop makes sure if another thread "beats" this one to the resource on waking up, we wait
                        // again and only add at the appropriate time
			while(num == BUF_SIZE){
				pthread_cond_wait(&c_prod, &m);
			}

			// wake up, lock the resource and add an item
			buffer[add] = i;
			add = (add+1) % BUF_SIZE;
			num++;
		pthread_mutex_unlock(&m);

		// signal to consumer
		// note that we avoid spurious wakeups by signalling after unlocking
		// this is possible because the signal operation does not depend on any characteristics of the shared resource
		pthread_cond_signal(&c_cons);
		printf("producer: inserted %d\n", i); fflush(stdout);
	}

	printf("producer quitting\n"); fflush(stdout);
	return 0;
}

void* consumer(void* param){

	int i;

	// infinite loop
	while(1){

		// critical section
		pthread_mutex_lock(&m);

			// underflow
			if(num < 0){
				exit(1);
			}

			// wait if nothing to read
			while(num == 0){
				pthread_cond_wait(&c_cons, &m);
			}

			// remove element if buffer empty
			i = buffer[rem];
			rem = (rem+1) % BUF_SIZE;
			num--;

		pthread_mutex_unlock(&m);

		// signal that a writer can write
		pthread_cond_signal(&c_prod);
		printf("consumed value %d\n", i); fflush(stdout);
	}
}























