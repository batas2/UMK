#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct osoba{
	int wzrost;
	char nazwisko[20];
};

double srednia(struct osoba tab[5]){
	int i, suma = 0;
	srand(time(NULL));
	for(i = 0; i < 5; i++){
		tab[i].wzrost = rand() % 200;
		suma += tab[i].wzrost;
	}
	return (double)suma / 5;
}
int main(){
	struct osoba tab[5];
	printf("%lf\n", srednia(tab));
}
