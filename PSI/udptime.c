#include "16_echo_batas2_head.c"
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(int argc, char *argv[])
{

	if(argc == 3){
		struct sockaddr_in6 addr;
		char addr_user[INET6_ADDRSTRLEN];
		
		strncpy(addr_user, argv[1], INET6_ADDRSTRLEN);
	
		addr.sin6_family = AF_INET6;
		addr.sin6_port = htons(atoi(argv[2]));

		inet_pton(AF_INET6, addr_user, &(addr.sin6_addr));

		int sock = socket(AF_INET6, SOCK_DGRAM, 0);
		char buf[256];
		int socklen;	
		while(recvfrom(sock, buf, 256, 0, (struct sockaddr*)&addr, &socklen) > 0){
			write(fileno(stdout), buf, sizeof(buf));
		}
	
		close(sock);
	}
}
