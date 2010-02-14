#include<stdio.h>
#include<unistd.h>
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	int pid = 0;
	if( (pid = fork()) < 0 ){
		printf("Blad funkcji fork");
	}else{
		if(pid != 0){
			sleep(10);
		}
		printf("PID: %d\nPPID: %d\n", getpid(), getppid());
	}
}
