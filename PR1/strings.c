#include<stdio.h>
#include<string.h>

int main(){
	char *s = malloc(sizeof(char)*10);
	char *t = malloc(sizeof(char)*10);
	char *p, *q;
	scanf("%s %s", s, t);
	printf("%d %d\n", strcmp(s, t), strncmp(s, t, 3));
	//strcpy(s, t); //strn(s, t, 3);
	//strcat(s, t); //Laczy znaki
	printf("%d \n", strlen(s));
	p = strchr(s, 'a'); //wskaznik do pierwszego a
	q = strrchr(s, 'b'); //wskiznik do ostatniego wystapienia znaki b
}
