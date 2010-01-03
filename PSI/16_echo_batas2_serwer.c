#include "16_echo_head.c"

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("Zla liczba parametrow\n ./serwer [port]");
	}else{
		struct sockaddr_in6 addr;

		addr.sin6_family = AF_INET6;
		addr.sin6_port = htons(atoi(argv[1]));
		addr.sin6_addr = in6addr_any;

		int sock = socket(AF_INET6, SOCK_STREAM, 0);

		if( bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in6)) == -1 ){
			perror("Blad-bind");
		}
	
		if(listen(sock, 10) == -1){
			perror("Blad-listen");
		}
	
		int i = 0;
		while( i < 10 )
		{
			i++;
	
			socklen_t size = sizeof(struct sockaddr_in6);
			int sockd = -1;
			if( (sockd = accept(sock, (struct sockaddr *)&addr, &size)) == -1 )
			{
				perror("Blad accept");
			}

			int pid = -1;
			if( (pid = fork()) == -1){
				perror("Blad-fork");
			}else{
				if(pid == 0){
					char buf[SIZE_BUF] = "";
					
					read(sockd, buf, sizeof(buf));
					write(sockd, buf, strlen(buf));
					close(sockd);	
					exit(1);
				}
			}
		}
	//	close(sock);
	}
}
