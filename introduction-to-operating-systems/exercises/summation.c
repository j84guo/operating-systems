#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; 
void *runner(void *param); 

int main(int argc, char *argv[]) {
	pthread_t tid; // thread id
	pthread_attr_t attr; // thread attributes include stack size and scheduling information
	
	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value> \n");
		return -1;
	}
	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"%d must be >= 0 \n", atoi(argv[1]));
		return -1;
	}

	pthread_attr_init(&attr); // default attributes
	pthread_create(&tid, &attr, runner, argv[1]); // create new thread 
	pthread_join(tid, NULL); // synchronous threading (fork and join)

	printf("sum = %d \n",sum);
}

void *runner(void *param){
	int i, upper = atoi(param);
	sum = 0;
	
	for (i = 1; i <= upper; i++)
		sum += i;
	
	pthread_exit(0); // releases thread data structures 
}
