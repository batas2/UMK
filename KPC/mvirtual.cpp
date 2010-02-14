#include <iostream>

using namespace std;

class zwierze{
public:
	zwierze(){
		cout<<"Konstruktor zwierzecia"<<endl;
	}
	virtual void jedz(){
		cout<<"mniam"<<endl;
	}
	~zwierze()
	{
		cout << "Po zwierzeciu" << endl;
	}
protected:
	void jedzszybko(){
		cout<<"mniam mniam"<<endl;
	}
private:
	void jedzbardzoszybko(){
		cout<<"mniam miniam mniam"<<endl;
	}
};

class pies: public zwierze{
public:
	pies(){
		cout<<"Konstruktor psa"<<endl;
	}
	void jedz(){
		cout<<"Hau"<<endl;
	}
	~pies()
	{
		cout << "Po psie" << endl;
	}
};

class kot: public zwierze{
public:
	kot(){
		cout<<"Konstruktor kota"<<endl;
	}
	void jedz(){
		cout<<"mniam"<<endl;
	}
	~kot()
	{
		cout << "Po kocie" << endl;
	}
};

/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(int argc,char **argv){
	zwierze *w;
	pies azor;
	kot nieazor;
	w=&azor;
	w->jedz();
	azor.jedz();
	w=&nieazor;
	w->jedz();

	return 0;
}
