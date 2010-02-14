#include<iostream>

using namespace std;

int a = 10, b = 5;

int sum(int aa, int bb=15);
double sum(double af, double bf);
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(){
	cout << sum(a, b) << "\n";
	cout << sum(a) << "\n";

	int sum(int aa = 35, int bb = 35);
	cout << sum() << "\n";

	double a_d = static_cast <double>(a);
	double b_d = static_cast <double>(b);
	cout << sum(a_d, b_d) << "\n";

	double sum(double aa = 35, double bb = 35);
	cout << sum(a_d, b_d) << "\n";
}

int sum(int af, int bf){
	return af + bf;
}

double sum(double af, double bf){
	cout << "double\n";
	return af + bf;
}
