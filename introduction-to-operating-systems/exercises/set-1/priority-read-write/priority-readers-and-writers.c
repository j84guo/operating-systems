// function signatures
#include "priority-readers-and-writers.h"

#include <pthread.h> // posix thread library
#include <stdio.h> // input / output streams
#include <stdlib.h> // standard library, e.g. malloc() and free()
#include <unistd.h> // library with NULL, gethostname(), fork()

// GLOBAL CONSTANTS
#define NUM_READERS 5 // total readers
#define NUM_READS 5 // reads per reader
#define NUM_WRITERS 5 // total writers
#define NUM_WRITES 5 // writes per writer

// GLOBAL SHARED DATA
unsigned int gSharedValue = 0; // shared variable
pthread_mutex_t gSharedMemoryLock = PTHREAD_MUTEX_INITIALIZER; // mutex for shared variable
pthread_cond_t gReadPhase = PTHREAD_COND_INITIALIZER; // read condition (readers wait for this)
pthread_cond_t gWritePhase = PTHREAD_COND_INITIALIZER; // write condition (writers wait for this)
int gWaitingReaders = 0; // number of waiting readers
int gReaders = 0; // number of readers

// main function
int main(int argc, char **argv) {

	int i;

	// thread id's
	int readerNum[NUM_READERS];
	int writerNum[NUM_WRITERS];

	// reader and writer threads
	pthread_t readerThreadIDs[NUM_READERS];
	pthread_t writerThreadIDs[NUM_WRITERS];

	// seed the random number generator
	srandom((unsigned int)time(NULL));

	// start the reader threads
	for(i = 0; i < NUM_READERS; i++) {
		readerNum[i] = i;
		pthread_create(&readerThreadIDs[i], NULL, readerMain, &readerNum[i]);
	}

	// start the writer threads
	for(i = 0; i < NUM_WRITERS; i++) {
		writerNum[i] = i;
		pthread_create(&writerThreadIDs[i], NULL, writerMain, &writerNum[i]);
	}

	// wait on readers
	for(i = 0; i < NUM_READERS; i++) {
		pthread_join(readerThreadIDs[i], NULL);
	}

	// wait on writers
	for(i = 0; i < NUM_WRITERS; i++) {
		pthread_join(writerThreadIDs[i], NULL);
	}

  return 0;
}

// note that by using a lock on a proxy variable (as opposed to the shared resource),
// the reader threads can read simultanriously, yet entering and exiting the critical
// section is done in an orderly fashion (no data race)
// priority is given to readers, so only if there are no readers do they signal to the writers
void *readerMain(void *threadArgument) {

	// thread id
	int id = *((int*)threadArgument);
	int i = 0;
	int numReaders = 0;

	// perform all reads
	for(i = 0; i < NUM_READS; i++) {

		// wait so that reads and writes do not all happen at once
	  	usleep(1000 * (random() % NUM_READERS + NUM_WRITERS));

		// enter critical section
	  	pthread_mutex_lock(&gSharedMemoryLock);
		  	gWaitingReaders++;
		  	while (gReaders == -1) {
		  		pthread_cond_wait(&gReadPhase, &gSharedMemoryLock);
		  	}
		  	gWaitingReaders--;
		  	numReaders = ++gReaders; // capture the number of readers at the moment this thread starts reading
		pthread_mutex_unlock(&gSharedMemoryLock);

		// read data
		fprintf(stdout, "[r%d] reading %u  [readers: %2d]\n", id, gSharedValue, numReaders);

	  	// exit critical section
	  	pthread_mutex_lock(&gSharedMemoryLock);
		  	gReaders--;
		  	if (gReaders == 0) {
		  		pthread_cond_signal(&gWritePhase);
		  	}
	  	pthread_mutex_unlock(&gSharedMemoryLock);
	}

	pthread_exit(0);
}

void *writerMain(void *threadArgument) {

	int id = *((int*)threadArgument);
	int i = 0;
	int numReaders = 0;

	for(i = 0; i < NUM_WRITES; i++) {
	  // Wait so that reads and writes do not all happen at once
	   usleep(1000 * (random() % NUM_READERS + NUM_WRITERS));

	  // Enter critical section
	  pthread_mutex_lock(&gSharedMemoryLock);
	  	while (gReaders != 0) {
	  		pthread_cond_wait(&gWritePhase, &gSharedMemoryLock);
	  	}
	  	gReaders = -1;
	  	numReaders = gReaders;
	  pthread_mutex_unlock(&gSharedMemoryLock);

	  // Write data
	  fprintf(stdout, "[w%d] writing %u* [readers: %2d]\n", id, ++gSharedValue, numReaders);

	  // Exit critical section
	  pthread_mutex_lock(&gSharedMemoryLock);
	  	gReaders = 0;

                // notice how priority is given to the readers, we broadcast to readers if any are waiting
		// only if there are no readers do we signal another write 
		if (gWaitingReaders > 0) {
	  		pthread_cond_broadcast(&gReadPhase);
	  	}
	  	else {
	  		pthread_cond_signal(&gWritePhase);
	  	}
	  pthread_mutex_unlock(&gSharedMemoryLock);
  }

  pthread_exit(0);
}
