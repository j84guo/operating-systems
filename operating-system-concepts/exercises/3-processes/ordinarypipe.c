#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {

    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];

    int fd[2];
    pid_t pid;

    // create pipe
    if (pipe(fd) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }

    // fork child process
    pid = fork();
    if (pid < 0) { // error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
    }

     // parent process
    if (pid > 0) {

        // close the unused end of the pipe
        close(fd[READ_END]);

        // write to the pipe
        printf("parent writing : %s\n", write_msg);
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

        // close the write end of the pipe
        close(fd[WRITE_END]);
    }
    // child process
    // note in Unix child processes inherir pipes
    else {
        // close the unused end of the pipe
        close(fd[WRITE_END]);

        // read from the pipe
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("child reading : %s\n",read_msg);
    }

    // close the read end of the pipe
    close(fd[READ_END]);
    return 0;
}
