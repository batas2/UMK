#include<stdio.h>
#include<stdlib.h>

void dec2bin(int liczba){
if(liczba > 1)
	dec2bin(liczba/2); //Wywo³anie rekurencyjne
printf("%d", liczba%2); //a % b, w jezyku c oznacza reszte z dzielenia liczby a przez b
}

int main(){
	dec2bin(34); //Liczbe 34 mozna dowolnie modyfikowac, bo jest to ta liczba ktora bedzie zamieniana na system 2
	return 0;
}
