#include <stdio.h> // printf
#include <string.h> // strlen
#include <sys/types.h> // contains a number of basic derived types
#include <sys/socket.h>  // SOCK_STREAM, socket(), bind(), connect(), accept()
#include <netdb.h> // network and database functions like gethostbyaddr(), gethostbyname()
#include <arpa/inet.h> // internet methods like inet_ntoa(), htons()
#include <netinet/in.h> // internet utilities like sockaddr_in, in_addr

int main(int argc, char *argv[]){

	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	if(argc != 2){
		fprintf(stderr, "usage: ./getaddrinfo <hostname>\n\n");
		return 1;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	// hints.ai_flags = AI_PASSIVE; // uses local ip

	if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
 		return 2;
	}

	printf("IP addresses for %s:\n\n", argv[1]);

	for(p = res; p != NULL; p = p->ai_next) {
		void *addr;
		char *ipver;
		
		if (p->ai_family == AF_INET) { 
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else { 
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf(" %s: %s\n", ipver, ipstr);
 	}
}