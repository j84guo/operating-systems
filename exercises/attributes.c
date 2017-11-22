#include <stdio.h>
#include <pthread.h>

void *foo (void* arg){
	printf("Foobar!\n");
	pthread_exit(NULL);
}

int main(void){
	
	int i;
	pthread_t thread1;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// todo : what does it mean to be detached or a kernel thread
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_create(&thread1, &attr, foo, NULL);
}