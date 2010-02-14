#include<iostream>

using namespace std;

class MojaKlasa{
public:
	int *liczba;

	MojaKlasa(int p)
	{
		this->liczba = new int(p);
	}

	/* Swoj konstruktor kopiujacy
	MojaKlasa(const MojaKlasa &c) //const musi byc!!
	{
		this->liczba = new int( *(c.liczba) );
	}
	*/
	~MojaKlasa()
	{
		if( !this->liczba )
			delete this->liczba;
		
	}	
};
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	MojaKlasa obj(5);
	MojaKlasa kopia_obj(obj);

	cout << *(obj.liczba) << " " << *(kopia_obj.liczba) << endl;

	*(kopia_obj.liczba) = 10;

	cout << *(obj.liczba) << " " << *(kopia_obj.liczba) << endl;
}
