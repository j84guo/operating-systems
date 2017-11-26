#include <stdio.h> // printf
#include <stdlib.h> // standard library, e.g. free, malloc(), atoi(), NULL
#include <arpa/inet.h> // htons(), inet_addr(), inet_ntoa()
#include <string.h> // C style strings, e.g. strlen
#include <unistd.h> // NULL and other miscellaneous
#include <netdb.h> // network/db functions, e.g. gethostbyname()

int main(int argc, char* argv[]){

	int socket_desc; // server socket descriptor
	struct  sockaddr_in server; // server socket tells OS where to send packets
	char* message; // client message
	char server_response[1024]; // server message

	// creates a server socket with ipv4 address, for TCP packets, using IP protocol
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1){
		printf("Could not create socket for server.");
	}

	// converts from ipv4 dotted-octet notation to big-endian binary
	server.sin_addr.s_addr = inet_addr("172.217.2.163");
	// AF_INET ipv4
	server.sin_family = AF_INET;
	// server port in big-endian binary
	server.sin_port = htons(80);

	// connects with server
	// file descriptor refers to server endpoint
	// socket struct contains endpoint data
	// size of socket struct is also passed
	if(connect(socket_desc, (struct sockaddr*) &server, sizeof(server)) < 0){
		puts("Error connecting");
		return 1;
	}
	puts("Connected to server\n");

	// send GET request
	// notice how the descriptor is used to reference to remote server
	// length of message is also passed
	// optional flags can be used (bitwise OR with 1...) in the last arg
	message = "GET / HTTP/1.1\r\n\r\n";
	if(send(socket_desc, message, strlen(message), 0) < 0){
		puts("Send failed");
		return 1;
	}
	puts("Sent client data\n");

	// read server response
	// notice again that the descriptor is used to identify the remote server
	// also included is the max message length and flags
	if(recv(socket_desc, server_response, 1024, 0) < 0){
		puts("Read server response");
		return 1;
	}
	puts("Reply received\n");
	puts(server_response);

	// de-allocates the file descriptor, process locks on resource unlocked
	close(socket_desc);
	return 0;
}
