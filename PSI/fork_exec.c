#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
main(){

		int pid = 0;
		if( (pid = fork()) < 0 ){
			printf("Blad funkcji fork");
		}else{
			if(pid == 0){
				execlp("ls", "ls", '\0');
			}else{
				int status;
				wait(&status);
			}
		}
}
