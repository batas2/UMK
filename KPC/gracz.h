#include<cstring>
#include<cstdlib>
#include<ctime>
#include<iostream>

class gracz
{

public: int punkty;

	gracz(const char *imie)
	{
		strcpy(nazwa, imie);
		punkty = 0;
	}

	~gracz(void);
	char * getImie();
	void losuj();
	int oszukuj();
	int getPunkty();
	int getLiczba();

private: char nazwa[20];
	 int liczba;
};

char * gracz::getImie()
{
	return nazwa;
}

void gracz::losuj()
{
	liczba = rand() % 11;
}

int gracz::oszukuj()
{
	punkty+=3;
	return 3;
}

int gracz::getPunkty()
{
	return punkty;
}

int gracz::getLiczba()
{
	return liczba;
}
gracz::~gracz(void)
{
	std::cout << "PAPA " << nazwa << std::endl;
}
