#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[], char *environ[])
{
	int i = 0;
	while(environ[i] != '\0'){
		printf("%s\n", environ[i++]);
	}
}
