#include "18_batas2_statki_head.h"

int isEmpty(int *field[], int x, int y)
{
	field[x][y]++;
	return field[x][y];	
}

void game(int users[2])
{
        int i, j;
	int *fieldA[SIZE_P];
	int *fieldB[SIZE_P];
	
	char *cmd[5];
	for(i = 0; i < 5; i++){
		cmd[i] = (char *)malloc(sizeof(char) * 50);
	}
	
	for(i = 0; i < SIZE_P; i++){
		fieldA[i] = (int *)malloc(sizeof(int *) * SIZE_P);
		fieldB[i] = (int *)malloc(sizeof(int *) * SIZE_P);
		for(j = 0; j < SIZE_P; j++){
			fieldA[i][j] = 0;
			fieldB[i][j] = 0;
		}
	}

	int user = 1;
	char buf[SIZE_BUF];
	while(cmd[1] != CMD_EXIT){
		user = !user;
		write(users[user], CMD_TURN, sizeof(CMD_TURN));
		read(users[user], buf, SIZE_BUF);
		split(buf, cmd);
		int x = cmd[2][0] - 48, y = cmd[3][0] - 48;
		if(cmd[1][0] == ISET){
			int r = 0;
			if(user){
				r = isEmpty(fieldA, x, y);
			}else{
				r = isEmpty(fieldB, x, y);
			}
			char msg[SIZE_BUF];
			switch(r){
				case 1: sprintf(msg, MSG_EMPTY, x, y); break;
				case 2: sprintf(msg, MSG_HIT, x, y); break;
				case 3: sprintf(msg, MSG_HITTED, x, y); break;
			}
			write(users[user], msg, sizeof(msg));
		}
	}
}
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(int argc, char *argv[])
{
//	if(argc != 2){
//		printf("Zla liczba parametrow\n ./serwer [port]");
//		exit(0);
//	}
	char sport[] = "2608";
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(sport));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if( bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1 ){
		perror("Blad-bind");
	}

	if(listen(sock, MAX_PLAYERS) == -1){
		perror("Blad-listen");
	}

	int i;
	int users[2]; users[0] = -1; users[1] = -1;

	for(i = 0; i < MAX_PLAYERS; i++)
	{
		socklen_t size = sizeof(struct sockaddr_in);
		int sockd = -1;
		if( (sockd = accept(sock, (struct sockaddr *)&addr, &size)) == -1 ){
			perror("Blad accept");
		}
		
		if(users[0] == -1){
			write(sockd, MSG_WAIT, sizeof(MSG_WAIT));
			users[0] = sockd;
		}else{
			users[1] = sockd;
	//		int pid = -1;
	//		if( (pid = fork()) == -1){
	//			perror("Blad-fork");
	//		}else{
	//			if(pid == 0){
					write(users[0], MSG_START, sizeof(MSG_START));
					write(users[1], MSG_START, sizeof(MSG_START));
					
					game(users);

					write(users[0], MSG_STOP, sizeof(MSG_STOP));
					write(users[1], MSG_STOP, sizeof(MSG_STOP));
			
					close(users[0]);
					close(users[1]);

	//				exit(1);
	//			}
			}
		}
//	}
}
