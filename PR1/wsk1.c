#include<stdio.h>


int dlugosc(char *x, int *b, int *a){
	int i = 0;
	while(*x != '\0'){
		if(*x == 'a'){++*a;}
		if(*x == 'b'){++*b;}
		x++; i++;
	}
	return i;
}

int main(){
	char *slowo="abcdef";
	int a = 0, b = 0, d = 0;
	d = dlugosc(slowo, &b, &a);
	printf("%d %d %d\n", d, b, a);
}
