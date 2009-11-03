#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void dec2bin(int liczba){
if(liczba >1)
dec2bin(liczba/2);
printf("%d", liczba%2);
}

void odwroc(char *w){
    int i;
    for(i = 0; i < strlen(w)%2; i++){
        char *b;
        b = &w[i];
        w[i] = w[strlen(w) - 1 - i];
        w[strlen(w) - 1 - i] = &b;
    }
}

int horner(char *w, int st, int p){
	int i, s = (w[st]-48);

	for(i = st - 1; i >= 0 ; i--){
		s = s * p + (w[i]-48);
	}
	return s;
}

int main(){

	int p = 2;
	char t[100];
	int a, i;

/*	printf("Podaj liczbe w systemie dziesietnym: ");
	scanf("%d", &a);

	printf("Liczba %d w systemie binarnym: ", a);
	dec2bin(a);
	printf("\n");*/

	printf("Podaj liczbe w systemie binarnym: ");
	scanf("%s", &t);
	odwroc(t);
    printf("%s", t);

	//printf("Binarna Liczba %s, to ta sama liczba dziesietna %d\n", t, horner(t, strlen(t) - 1, p));
	return 0;
}
