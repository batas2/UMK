#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main()
{

	int *v;
	struct shmid_ds *buf;

	int id = shmget(260889, 1, IPC_CREAT|0600);
	if(id == -1){
		perror("Blad-shmget");
	}

	v = (int *)shmat(id, 0, 0);
	shmctl(id, IPC_STAT, buf);
	
	if(v != NULL){
		(*v) = 0;
		sleep(5);
		while( (buf->shm_nattch != 1) ){	
			shmctl(id, IPC_STAT, buf);
			sleep(1);
		}
		shmdt(v);
		shmctl(id, IPC_RMID, buf);
	}else{
		perror("Blad-shmat");
	}
	
}
