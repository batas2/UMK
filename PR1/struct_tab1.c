#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct osoba{
	double oceny[10];
};

double srednia(struct osoba oso){
	int i, suma = 0;
	for(i = 0; i < 10; i++){
		oso.oceny[i] = (double)(rand() % 4 + 1);
		suma += oso.oceny[i];
	}
	return (double)suma / 5;
}
int main(){
	struct osoba tab[5];
	int i = 0;
	srand(time(NULL));
	for(i = 0; i < 5; i++){
		printf("Srednia nr: %d --> %lf\n", i, srednia(tab[i]));
	}
}
