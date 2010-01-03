#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
	if(argc == 3){

		char host[128];
		int port;

		struct hostent *h;
		char buf[1024];

		strncpy(host, argv[1], sizeof(host));
		port = atoi(argv[2]);

		h = gethostbyname(host);

		if(h == NULL){
			perror("Blad-gethostbyname");
			error(1);
		}

		struct sockaddr_in addr;

		addr.sin_family = AF_INET;
		addr.sin_addr = *(struct in_addr *) h->h_addr;
		addr.sin_port = ntohs(port);
		        	
		int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		
		if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
			perror("Blad-connect");
			exit(1);
		}

		write(sock, "GET /\r\n", strlen("GET /\r\n"));
		
		int r;
		while ( (r = recv(sock, buf, sizeof(buf), 0) ) > 0){
			printf("%s", buf);
			memset(buf, 0x0, sizeof(buf));
		}
		printf("%s", buf);

		close(sock);

	}else{
		printf("./client [adres] [port]\n");
	}
	
}
