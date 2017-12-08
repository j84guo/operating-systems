#include <sys/types.h> // various system types, e.g. related to threads and processes
#include <stdio.h> // io types and functions like printf
#include <unistd.h> // access to POSIX api, including system call wrappers like fork() and I/O functions like read(), write() 

int main() {

	pid_t pid;

	// fork a child process
	pid = fork();
	if (pid < 0) { // error occurred
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) { // child process
		execlp("/bin/ls","ls",NULL);
	}
	else {
		// parent process
		// parent will wait for the child to complete
		wait(NULL);
		printf("Child Complete \n");
	}

	return 0;
}
