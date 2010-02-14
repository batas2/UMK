#include<iostream>

using namespace std;
int a = 10, b = 15;

void fun(int aa, int bb);
void funref(int aa, int &bb);
void funvoid();
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	cout << a << "  " << b << "\n";
	fun(a, b);
	cout << a << "  " << b << "\n";
	funref(a, b);
	cout << a << "  " << b << "\n";
	funvoid();
}

void fun(int aa, int bb)
{
	aa = 0; bb = 0;
}
void funref(int aa, int &bb)
{
	aa = 0; bb = 0;
}
void funvoid()
{
	printf(":)\n");
}

