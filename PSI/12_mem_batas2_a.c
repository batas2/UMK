#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main()
{

	int *buf;

	int id = shmget(260889, 1, 0600);
	if(id == -1){
		perror("Blad-shmget");
	}

	buf = (int *)shmat(id, 0, 0);

	sleep(5);

	if(buf != NULL){
		int i;
		for(i = 0; i < 5; i++){
			(*buf)+=5;
			printf("%d\tpid: %d\n", *buf, getpid());
			sleep(2);
		}
		shmdt(buf);	
	}else{
		perror("Blad-shmat");
	}

	
}
