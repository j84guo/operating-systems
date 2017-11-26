#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	int socket_desc;
	int new_socket;
	int c;
	char *message;
	struct sockaddr_in server;
	struct sockaddr_in client;

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1){
		printf("Could not create socket");
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	if(bind(socket_desc, (struct sockaddr*) &server, sizeof(server)) < 0){
		puts("Bind failed");
	}
	puts("Bind done");

	listen(socket_desc, 3);

	puts("Listening for incoming connections...");
	c = sizeof(struct sockaddr_in);

	while((new_socket = accept(socket_desc, (struct sockaddr*) &client, (socklen_t*)&c))){
		puts("Connected accepted");

		message = "Hardcoded reply from server\n";
		write(new_socket, message, strlen(message)); // since sockets are treated like files, write can be used to send data
	}

	if(new_socket < 0){
		perror("Accept failed");
		return 1;
	}

	return 0;
}
