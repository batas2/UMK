#include<iostream>

using namespace std;

class MojaKlasa{
public:
	int liczba;

	MojaKlasa(int p){
		this->liczba = p;
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

	cout << obj.liczba << " " << kopia_obj.liczba << endl;
}
