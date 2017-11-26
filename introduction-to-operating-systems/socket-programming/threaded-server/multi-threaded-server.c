#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

void* connection_handler(void*);

int main(int argc, char* argv[]){

	int socket_desc;
	int new_socket;
	int c;
	int* new_sock;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char* message;

	// Create server socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1){
		printf("Could not create server socket");
	}

	// Prepare server socket data structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	// Bind server socket to port
	if(bind(socket_desc, (struct sockaddr*) &server, sizeof(server)) < 0){
		puts("Binding server socket failed");
		return 1;
	}
	puts("Bind done");

	// Listen on port
	listen(socket_desc, 2);

	// Accept clients
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while( (new_socket = accept(socket_desc, (struct sockaddr*) &client, (socklen_t*) &c)) ){
		puts("Connection accepted");

		// Reply to client
		message = "Received your request and assigning handler thread for your socket\n";
		write(new_socket, message, strlen(message));

		pthread_t sniffer_thread; // new thread
		new_sock = malloc(1); // 1 byte integer for client socket handle
		*new_sock = new_socket;

		if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock) < 0){
			perror("Could not create thread");
			return 1;
		}

		puts("Handler assigned");
	}

	if(new_socket < 0){
		perror("Accept failed");
		return -1;
	}

	return 0;
}

void* connection_handler(void* socket_desc){

	// save client socket descriptor
	int sock = *(int*) socket_desc;
	int read_size;
	char* message;
	char client_message[1024];

	message = "Greetings, I am your connection handler\n";
	send(sock, message, strlen(message), 0);

	while( (read_size = recv(sock, client_message, 1024, 0)) > 0 ){
		write(sock, client_message, read_size);
	}

	if(read_size == 0){
		puts("Client disconnected\n");
		fflush(stdout);
	}else if(read_size == -1){
		perror("recv failed");
	}

	free(socket_desc);
	return 0;
}
