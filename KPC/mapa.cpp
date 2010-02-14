#include<iostream>
#include<string>
#include<map>
#include<algorithm>

using namespace std;

class student
{
public:
	string imie, nazwisko;
	int indeks;
	double srednia;

	student()
	{
	}

	student(const char *imie, const char *nazwisko, int indeks)
	{
		this->indeks = indeks;
		this->imie.assign(imie);
		this->nazwisko.assign(nazwisko);
	}
};
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	student *tab;
	tab = new student[3];
	tab[2] = new student("Ja", "Be", 323);
	student Mikus("Mikolaj", "Fejzer", 229708);
	student Szybus("Szymon", "Bachnij", 229702);
	student Bartus("Bartosz", "Frackowiak", 229711);

	Mikus.srednia = 2.4;
	Szybus.srednia = 3.4;
	Bartus.srednia = 6.8;

	map<string, student> studenci;
	map<string, student>::iterator it;

	studenci.insert( pair<string, student>("haha", Mikus) );
	studenci.insert( pair<string, student>("baba", Szybus) );
	studenci.insert( pair<string, student>("lala", Bartus) );

	for ( it = studenci.begin() ; it != studenci.end(); it++ )
    		cout << (*it).first << " => " << (*it).second.nazwisko << " - " << (*it).second.srednia << endl;

}
