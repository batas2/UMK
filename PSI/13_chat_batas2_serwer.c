#include "13_chat_batas2_head.h"

int _stop = 0;

void koniec(int v)
{
	_stop = 1;
	printf("Serwer zakonczyl swoje dzialanie.\n");
}

int main(int argc, char *argv[])
{
	char	*line;
	struct	shmid_ds *mem_buf = malloc(sizeof(struct shmid_ds));
	struct	sembuf *sem_buf = malloc(sizeof(struct sembuf));

	int i = 0;	

	signal(SIGUSR1, koniec);

	int mem_id = shmget(MEM_ID, sizeof(char) * SIZE_LINE, IPC_CREAT|0600);
	if(mem_id == -1){
		perror("Blad-shmget");
	}

	line = (char *)shmat(mem_id, NULL, 0);

 	int sem_id = semget(SEM_ID, 1, IPC_CREAT|0600);
	if (sem_id == -1){
		perror("Blad-semget");
	}

	if (semctl(sem_id, 0, SETVAL, (int)1) == -1){
 		perror("Blad-semctl");
	}
	
	if(line != NULL){
		strcpy(line, "Start rozmowy\n");
		while( !_stop ){	
			if(argc > 1 && argv[1]){
				printf("%d: %s", i++, line);
			}
			sleep(1);
		}
		shmdt(line);
		shmctl(mem_id, IPC_RMID, mem_buf);
	}else{
		perror("Blad-shmat");
	}
	
}
