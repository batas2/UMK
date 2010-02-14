#include "18_batas2_statki_head.h"

void rSet(char *data[])
{

}

void rEmpty(char *data[])
{

}

void rHit(char *data[])
{

}

void rTurn(int sock)
{
	int a = 0, b = 0;
	printf("Twoja Kolej! Podaj wspolrzedne strzalu:\n");
	scanf("%d %d", &a, &b);
	char buf[SIZE_BUF];
	sprintf(buf, CMD_SET, a, b);
	write(sock, buf, sizeof(buf));
	printf("Prosze czekac na ruch przeciwnika.\n");
}

void game(int sock)
{
        int i;
	char *cmd[5];
	for(i = 0; i < 5; i++){
		cmd[i] = (char *)malloc(sizeof(char) * 50);
	}

	char buf[SIZE_BUF];
	while(cmd[1] != CMD_EXIT){
		read(sock, buf, SIZE_BUF);
		split(buf, cmd);
		if(!strcmp(cmd[0], "MSG")){
			printf("%s\n", cmd[1]);
		}else{
			switch(cmd[1][0]){
				case ISET: rSet(cmd); break;
				case IEMPTY: rEmpty(cmd); break;
				case IHIT: rHit(cmd); break;
				case ITURN: rTurn(sock); break;
			}
		}
	}
}
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(int argc, char *argv[])
{

//	if(argc != 3){
//		printf("Zle parametry!\n");
//		exit(1);
//	}
	char host[] = "127.0.0.1";
	int port = 2608;

	struct hostent *h;

//	strncpy(host, argv[1], sizeof(host));
//	port = atoi(argv[2]);

	h = gethostbyname(host);

	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_addr = *(struct in_addr *) h->h_addr;
	addr.sin_port = ntohs(port);
		
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("Blad-connect");
	}
	
	game(sock);

	close(sock);
	
}
