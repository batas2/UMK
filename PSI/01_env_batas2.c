#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[], char *environ[])
{
	int i;
	for(i = 0; i < sizeof(environ); i++){
		printf("%s\n", environ[i]);
	}
}
