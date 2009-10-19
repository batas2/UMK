#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int i = 0;
	argv += argc - 1;
	while(i < argc){
		printf("%s\n", *argv);
		i++; argv--;
	}
}
