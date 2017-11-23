#include <stdio.h> // input/output streams
#include <stdlib.h> // malloc, free

// socket header files
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <errno.h> // perror
#include <strings.h> // for bzero

int main () {

	// get tcp socket
	// bind to port
	// listen for request
	// close connection

	int sock; // server socket number
	int cli; // client socket number
	int sent; // bytes sent
	struct sockaddr_in server; // server socket data structure
	struct sockaddr_in client; // client socket data structure
	unsigned int len; // length of socket struct
	char mesg[] = "Hello to the socket programming world!"; // data to send

	// create socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket: ");
		exit(-1);
	}

	// initialize socket data structure
	server.sin_family = AF_INET;
	server.sin_port = htons(10000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);

        len = sizeof(struct sockaddr_in);

	// bind to port
	if((bind(sock, (struct sockaddr*) &server, len)) == -1){
		perror("bind: ");
		exit(-1);
	}

	// listen
	if((listen(sock, 5)) == -1){
		perror("listen: ");
		exit(-1);
	}

	// infinite accept loop
	while(1){
		if((cli = accept(sock, (struct sockaddr*) &client, &len)) == -1){
			perror("accept: ");
			exit(-1);
		}

		printf("sending response");
		sent = send(cli, mesg, strlen(mesg), 0);
		printf("Sent %d bytes to client : %d\n", sent, inet_ntoa(client.sin_addr));

		close(cli);
	}
}
