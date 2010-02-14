#include<iostream>

using namespace std;

int silnia(int n){
	if (n == 0 || n == 1) return 1;
	else return n * silnia(n - 1);
}
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(){
	int n;
	cin >> n;
	if(n > 0){
		cout << silnia(n) << endl;
	}
}
