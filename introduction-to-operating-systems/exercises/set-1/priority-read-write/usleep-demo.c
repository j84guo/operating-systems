// usleep - suspends execution of the calling thread for a certain number of microseconds
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int result = usleep(1000000);
	printf("result %d", result);
	return 0;
}
