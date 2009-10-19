#include<iostream>

namespace mojens{
	bool wynik=true;
}

int pierwsza(int n){
	for(int i = 2; i < n; i++){
		if( n % i == 0 ) return i;
	}
	return 0;
}

using namespace std;

int main(){
	bool wynik = false;
	//if(wynik) cout << "Prawda\n"
	if(mojens::wynik) cout << "prawda\n";
	else cout << "Falsz\n";
	int n;
	cin >> n;
	int wynk = pierwsza(n);
	if(wynk == 0){
		cout <<  "pierszwa";
	}else{
		cout << "zlozona dzielnik: " << wynk;
	}
}
