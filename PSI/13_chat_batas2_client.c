#include "13_chat_batas2_head.h"

/*
 * funkcja sluzaca do wykonanie podniesienia lub opuszeczenia semafora
 */
void sem_op(struct sembuf *buf, int sem_id, int sem_num, int sem_op)
{
	buf->sem_num = sem_num;
 	buf->sem_op = sem_op;
	buf->sem_flg = 0;
	if (semop(sem_id, buf, 1) == -1){
 		perror("Blad-semop");
	}
}
/*
 * funkcja piszaca do pamieci wiadomosc
 */
void msg(char *line,  char *buf, char *nick)
{
	char _msg[SIZE_LINE];

	strncpy(_msg, nick, 10);
	strcat(_msg, buf);
	
	strcpy(line, _msg);

	return;
}

int main(int argc, char *argv[])
{
	char	*line;
	char	nick[10];
	int	pid = getpid();
	struct  shmid_ds *mem_buf = malloc(sizeof(struct shmid_ds));
	struct	sembuf *sem_buf = malloc(sizeof(struct sembuf));
	
	if(argc == 2){
		strncpy(nick, argv[1], 8);
		strcat(nick, "> ");
	}else{
		sprintf(nick, "%d> ", pid);
	}

	int mem_id = shmget(MEM_ID, 0, 0600);
	if(mem_id == -1){
		perror("Blad-shmget");
	}

 	int sem_id = semget(SEM_ID, 1, 0600);
	if (sem_id == -1){
		perror("Blad-semget");
	}

	line = (char *)shmat(mem_id, NULL, 0);

	if(line != NULL){
		char buf[SIZE_LINE];
		int w = 0;
		
		while (strcmp(buf, "exit\n") != 0){
			sem_op(sem_buf, sem_id, 0, -1); //Opuszczam semafor
			write(fileno(stdout), line, strlen(line));

			write(fileno(stdout), nick, sizeof(nick));
			w = read(fileno(stdin), buf, sizeof(buf));
			buf[w] = '\0';
			
			msg(line, buf, nick); //"wysylanie" wiadomosci
		
			sem_op(sem_buf, sem_id, 0, +1);	//Podnosze semafor
		}
		shmdt(line);	
	}else{
		perror("Blad-shmat");
	}

	
}
