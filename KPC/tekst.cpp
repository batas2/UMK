#include<iostream>
#include<string>

using namespace std;

class tekst
{
private:
	string napis;
public:
	
	tekst(string napis)
	{
		this->napis = napis;		
	}

	int znajdz(string klucz)
	{
		int n = 0, pos = -1;
		while( (pos = this->napis.find(klucz, ++pos)) != string::npos){
			n++;
		}
		return n;
	}
	
	void dodaj(tekst *T)
	{
		this->napis.append(T->napis);
	}

};
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{

	string klucz, _tekst1, _tekst2, _tekst3;

	getline(cin, klucz);
	getline(cin, _tekst1);
	getline(cin, _tekst2);

	tekst tekst1(_tekst1);
	tekst tekst2(_tekst2);

	cout << tekst1.znajdz(klucz) << endl;
	cout << tekst2.znajdz(klucz) << endl;

	tekst1.dodaj(&tekst2);
	
	cout << tekst1.znajdz(klucz) << endl;


}
