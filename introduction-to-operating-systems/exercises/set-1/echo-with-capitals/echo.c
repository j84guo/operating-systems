#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char* argv[]){
	int socket_desc;
	int new_socket;
	int c;
	char* message;
	struct sockaddr_in server;
	struct sockaddr_in client;

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1){
		printf("Could not creat socket");
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY; // socket accepts connections to all IP's
	server.sin_port = htons(8888);

	if(bind(socket_desc, (struct sockaddr*) &server, sizeof(server)) < 0){
		puts("Bind failed");
		return 1;
	}
	puts("Bind done");

	listen(socket_desc, 3);
	puts("Listening for incoming connections...");
	c = sizeof(struct sockaddr_in);

	int read_size;
	char client_message[1024];

	while((new_socket = accept(socket_desc, (struct sockaddr*) &client, (socklen_t*) &c))){
		puts("Connection accepted");
		message = "Hello from your server\n";
		write(new_socket, message, strlen(message));

		while((read_size = recv(new_socket, client_message, 1024, 0)) > 0){
			write(new_socket, client_message, read_size);
                }
		if(read_size == 0){
			puts("Client desconnected");
			fflush(stdout);
		}else if(read_size == -1){
			puts("Read failed");
			return 1;
		}
	}

	if(new_socket < 0){
		puts("Accept failed");
		return 1;
	}

	close(new_socket);
	return 0;
}
