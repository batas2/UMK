#include "gracz.h"
#include<iostream>

using namespace std;
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	gracz Gracz1("Leon");
	gracz Gracz2("Zosia");

	srand( (unsigned)time(0));

	for(int i = 0; i < 10; i++){

		Gracz1.losuj();
		Gracz2.losuj();
	
		cout << "Runda " << i << " " << Gracz1.getImie() << " : " 
		<< Gracz1.getLiczba() << " <==> " << Gracz2.getImie() 
		<< " : " << Gracz2.getLiczba();

		if(Gracz1.getLiczba() > Gracz2.getLiczba()){
			cout << ". " << Gracz1.getImie() << " wygrywa runde !!!" << endl;
			Gracz1.punkty++;
		} else if(Gracz1.getLiczba() < Gracz2.getLiczba()){
			cout << ". " << Gracz2.getImie() << " wygrywa runde !!!" << endl;
			Gracz2.punkty++;
		} else {
			cout << ". Remis" << endl;
		}
	}
	if(Gracz1.punkty > Gracz2.punkty){
		cout << "Gre wygrywa " << Gracz1.getImie() << "!!! Punkty: " << Gracz1.getPunkty() << endl;
	} else if(Gracz1.punkty < Gracz2.punkty){
		cout << "Gre wygrywa " << Gracz2.getImie() << "!!! Punkty: " << Gracz2.getPunkty() << endl;
	} else{
		cout << "Remis!!! " << endl;
	}
}
