#include "11_fifo_batas2_head.c"

void koniec(int v)
{
	execlp("rm", "rm", "-f", SERWER_FIFO, NULL);
	printf("Serwer zakonczyl swoje dzialanie.\n");
	exit(1);
}

void podziel(char *in, char *cmd, char *fifo)
{
	char *pos;
	int n = 0;

	pos = strstr(in, ":");
	n = pos - in;

	strncpy(cmd, in, n);
	cmd[n] = '\0';
	
	memmove(in, in + n + 1, (strlen(in) - n) * sizeof(char) );
	strcpy(fifo, in);
	fifo[strlen(fifo) - 1] = '\0';	
}

int main()
{

	int 	f_serv, f_cli;
	int 	i = 0;

	mkfifo(SERWER_FIFO, 0600);

	if( (f_serv = open(SERWER_FIFO, O_RDONLY | O_NONBLOCK)) == -1){
		perror("Blad Serwer-open-SerwerFifo");
		koniec(0);
	}
	
	signal(SIGUSR1, koniec);

	while(i < 10){

		char	*line = (char *)malloc(sizeof(char) * SIZE_LINE);
		int 	v;

		while(	(v = read(f_serv, line, sizeof(char) * SIZE_LINE))  <= 0){
			sleep(1);
		}
		
		int pid = 0;
		if( (pid = fork()) < 0){
			perror("Blad Serwer-fork");
			koniec(0);
		}else{
			if(pid == 0){
				char	cmd[SIZE_CMD];
				char	fifo[SIZE_FIFO];
	
				podziel(line, fifo, cmd);
				
				if( (f_cli = open(fifo, O_RDWR)) == -1){
					perror("Blad Serwer-open-ClientFifo");
					koniec(0);
				}
				
				dup2(f_cli, fileno(stdout));
				execlp(cmd, cmd, NULL);
				
				char	buf[] = "Nie ma takiego polecenia!\n";
				
				write(f_cli, buf, sizeof(buf));		
				exit(1);
			}else{
				i++;
			}
		}
	}
	koniec(0);
}

