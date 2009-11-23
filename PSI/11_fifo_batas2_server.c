#include "11_fifo_batas2_head.c"

void koniec(int v)
{
	exit(0);
}

void podziel(char *in, char *cmd, char *fifo)
{
	char *pos;
	int n = 0;

	pos = strstr(in, ":");
	n = pos - in;

	strncpy(cmd, in, n);
	
	memmove(in, in + n + 1, (strlen(in) - n) * sizeof(char) );
	strcpy(fifo, in);
	
}

int main()
{

	/*char in[] = "test:test2\0";
	char cmd[50], fifo[50];

	podziel(in, cmd, fifo);

	printf("%s  --  %s", cmd, fifo);
*/
	int f_serv, f_cli;
	char line[512];


	mkfifo(SERVER_FIFO, 0770);
	f_serv = open(SERVER_FIFO, O_RDONLY | O_NONBLOCK);
	
	signal(SIGUSR1, koniec);

	while(1){
		read(f_serv, line, sizeof(line));
		int pid = 0;
		if( (pid = fork()) < 0){
			perror("Blad fork");
		}else{
			if(pid == 0){
				char cmd[256], fifo[256];
				podziel(line, cmd, fifo);

				mkfifo(fifo, 0770);
				f_cli = open(fifo, O_WRONLY);
				
				dup2(f_cli, fileno(stdout));
				execlp(cmd, cmd, NULL);		
			}else{
				printf("CLIENT: %s", line);
			}		
		}
	} 
}

