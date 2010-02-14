#include<iostream>
using namespace std;
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(){

	int tab[10];

	for(int i = 0; i < 10; i++){
		tab[i] = i*i;
		//*(tab+i)=i*i;
	}

	wyswietl(tab);

	int *tab2;
	tab2 = new int[10];
	//int *tab2 = new int[10];

	wyswietl(tab2);

	delete []tab2;
	//delete tab2;
	
