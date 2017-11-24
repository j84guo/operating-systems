#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char* argv[]){

	int socket_desc;
	struct sockaddr_in server;
	char *message;
	char server_response[1024];

	socket_desc = socket(AF_INET, SOCK_STREAM, 0); // arguments ipv4, tcp, IP

	if(socket_desc == -1){
		printf("Could not create socket");
	}

	server.sin_addr.s_addr = inet_addr("172.217.2.99");
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	if(connect(socket_desc, (struct sockaddr*) &server, sizeof(server)) < 0){
		puts("Connect error");
		return 1;
	}

	puts("Connected\n");

	message = "GET / HTTP/1.1\r\n\r\n";
	if(send(socket_desc, message, strlen(message), 0) < 0){
		puts("Send failed");
		return 1;
	}
	puts("Data sent\n");

	if(recv(socket_desc, server_response, 1024, 0) < 0){
		puts("Read failed");
		return 1;
	}
	puts("Reply received\n");
	puts(server_response);

	close(socket_desc);
	return 0;
}
