// split.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void move(char *str, int n)
{
	memmove(str, str + n, (strlen(str) - n) * sizeof(char));
	str[strlen(str) - n] = '\0';
	return;
}

void split_a(char *str, char *result[])
{
	char *pos;
	int pos_i, i = 0;
	
	while( (pos = strstr(str, " ")) != NULL ){
		pos_i = pos - str;
		//printf("%s => %d\n", str, pos - str);
		strncpy(result[i], str, sizeof(char) * (pos_i));
		result[i++][pos_i] = '\0';
		move(str, pos_i + 1);
	}
	result[i] = str;
	result[i][strlen(result[i]) - 1] = '\0';
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char cmd[255];
	char *arg[10];
	
	while(1){
		int i;
		fgets(cmd, sizeof(cmd), stdin);
		for(i = 0; i < 10; i++){
			arg[i] = (char *)malloc(sizeof(char) * 25);
			arg[i][0] = '\0';
		}

		split_a(cmd, arg);

		for(i = 0; i < 10; i++){
			printf("%d - %s\n", arg[i]);
			free(arg[i]);
		}
		//free(arg);
	}
	return 0;
}

