#include "12_mem_batas2_head.h"
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{

	int *buf;

	int id = shmget(MEM_ID, SIZE_MEM, 0600);
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
