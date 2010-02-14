#include<iostream>
#include<string>

using namespace std;

class osoba
{
private:
	string imie;
public:
	static int ilosc_osob;
	int wiek;

	osoba(string imie)
	{
		this->imie = imie;
		ilosc_osob++;
	}

	string podajimie()
	{
		return this->imie;
	}

	int podajwiek()
	{
		return this->wiek;
	}


	void lubi(osoba os)
	{
		cout << this->imie << " lubie " << os.imie << endl;
	}

	static void lubi2(osoba *os, osoba *os2)
	{
		cout << os->imie << " nie lubi " << os2->imie << endl;
	}

};


int osoba::ilosc_osob=0;
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	osoba Jan("Janek");
	osoba Kas("Kasia");

	cout << "ilosc " << osoba::ilosc_osob << endl;

	osoba *Kas_wsk = &Kas;
	osoba *Jan_wsk = &Jan;

	cout << "ilosc " << osoba::ilosc_osob << endl;

	Jan.lubi(Kas);
	Kas.lubi(Jan);

	Jan.lubi2(Jan_wsk, Kas_wsk);
	Kas.lubi2(Kas_wsk, Jan_wsk);	
}
