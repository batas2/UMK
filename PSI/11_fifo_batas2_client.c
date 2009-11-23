#include "11_fifo_batas2_head.c"

int main(int argc, char *argv[])
{

	if(argc == 2){
		int		f_serv, f_cli;		//Deskryptor fifo odpowiednio serwera, klienta
		char	line[SIZE_LINE];	//Bufor do zczytywania wyniku od serwera
		char	cmd[SIZE_CMD];		//Ciag zawierajacy sciezke do fifo oraz polecenie; Do wyslania do serwera
		char	fifo[SIZE_FIFO];	//sciezka do fifo klienta
		
		sprintf(fifo, "%s%d\0", CLIENT_FIFO, getpid());
		mkfifo(fifo, 0600);
	
		if( (f_serv = open(SERWER_FIFO, O_RDWR)) == -1){
			perror("Blad: Client-Open-SerwerFifo");
			exit(1);
		}
		
		if( (f_cli = open(fifo, O_RDONLY | O_NONBLOCK)) == -1){
			perror("Blad: Client-Open-ClientFifo");
			exit(1);
		}

		sprintf(cmd, "%s:%s\n", fifo, argv[1]);
		write(f_serv, cmd, sizeof(char) * SIZE_CMD);

		int v;
		while( (v = read(f_cli, line, sizeof(char) * SIZE_LINE)) == 0){
			sleep(1);
		}

		printf("%s", line);
		execlp("rm", "rm", "-f", fifo, NULL);
	}else{
		printf("Podaj jako parametr polecenie\n");
	}
	 
}

