#include<stdio.h>
#include<stdlib.h>
void kopiuj(char *s, char *t){

	while(*t != '\0'){
		*s = *t;
		s++; t++;
	}
}

int main(){

	char x[] = "abcdf";
	char *y;
	y = (char *)malloc(sizeof(char)*5);
	kopiuj(y, x);
	printf("%s\n", y);
}

