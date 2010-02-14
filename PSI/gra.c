#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

#define SIZE 10

char **screen;

void print()
{
	
	int pid = 0;
	//if( (pid = fork()) >= 0  ){
	//	if(pid == 0){
			//execlp("clear", "clear", NULL);
			printf("\033[2J");
	//	}else{
			//sleep(1);
			int i, j;
			for(i = 0; i < SIZE; i++){
				printf("%s\n", screen[i]);
			}
			//sleep(1);
	//	}
//	}
}

void alloc()
{
	int i, j;
	screen = (char **)malloc(sizeof(char *) * SIZE);
	//screen[0] = (char *)malloc(SIZE * SIZE * sizeof(char));
	for(i = 0; i < SIZE; i++){
		//screen[i] = screen[0] + i * SIZE;
		screen[i] = (char *)malloc(sizeof(char) * 10);
	}

	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			screen[i][j] = '.';
		}
		screen[i][SIZE] = '\0';
	}
}

int main()
{
	
	alloc();
	int i = 0;
	//while(i < 1000){
	print();// i++;
	char c;
//	c = getchar();
//:q	printf("%d", c);
	//}
}
