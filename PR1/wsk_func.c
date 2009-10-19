#include<stdlib.h>
#include<stdio.h>

int dodaj(int a, int b){return a+b;}
int odejmij(int a, int b){return a-b;}

int f(int (*wsk)(int, int), int x, int y){
	return wsk(x, y);
}

int main(){
	int x = 5, y = 7;
	int (*wsk)(int, int);
	wsk = &dodaj;
	printf("%d\n", wsk(x, y));

	wsk = &odejmij;
	printf("%d\n", wsk(x, y));

	wsk = &dodaj;
	printf("%d\n", f(wsk/*dodaj albo odejmij*/, x, y));
//	int *(*wsk)(int, int); wskaznik do funkcji ktora zwraca wskaznik na inta
}
