#include "16_echo_head.c"

int main(int argc, char *argv[])
{

	if(argc == 3){
		struct sockaddr_in6 addr;
		char addr_user[INET6_ADDRSTRLEN];
		
		strncpy(addr_user, argv[1], INET6_ADDRSTRLEN);
	
		addr.sin6_family = AF_INET6;
		addr.sin6_port = htons(atoi(argv[2]));

		inet_pton(AF_INET6, addr_user, &(addr.sin6_addr));

		int sock = socket(AF_INET6, SOCK_STREAM, 0);

		if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in6)) == -1){
			perror("Blad-connect");
		}

		char buf[256];
		
		read(fileno(stdin), buf, sizeof(buf));
		buf[strstr(buf, "\n") - buf + 1] = '\0';
		write(sock, buf, sizeof(buf));

		sleep(1);
	
		read(sock, buf, sizeof(buf));
		write(fileno(stdout), buf, strlen(buf));
	
		close(sock);
	}
}
