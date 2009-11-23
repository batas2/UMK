#include "11_fifo_batas2_head.c"

int main()
{

	int f_serv, f_cli;
	char line[512];

	char fifo[256];
	sprintf(fifo, "%s%d", CLIENT_FIFO, getpid());

	mkfifo(fifo, 0770);
	
	f_serv = open(SERVER_FIFO, O_WRONLY);
	f_cli = open(fifo, O_RDONLY | O_CREAT);

	char cmd[512];
	sprintf(cmd, "%s:%s", fifo, "ls");
	write(f_serv, cmd, sizeof(cmd));

	sleep(2);

	char buf[1000];
	read(f_cli, buf, sizeof(buf));

	printf("%s", buf);
	
/*	while(1){
		read(fileno(f_serv), line, sizeof(line));
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
	}*/ 
}

