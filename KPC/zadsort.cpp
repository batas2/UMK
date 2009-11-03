#include<iostream>

using namespace std;

void sort(int *tab, int n)
{
	for(int i = 0; i < n - 1; i++){
		int min = tab[i], min_j = i;
	
		for(int j = i + 1; j < n; j++){
			 	if(tab[j] < min){
					min = tab[j];
					min_j = j;
				}
		}
		if(min_j != i){
			int buf = tab[i];
			tab[i] = min;
			tab[min_j] = buf;
		}
	}
}

void wyswietl(int *tab, int n)
{
	for(int i = 0; i < n; i++){
		cout << tab[i] << "\n";
	}
}

int main()
{
	int tab[100];
	int i = 0, buf = 0;

	while( (cin >> buf) && (buf > 0) && (i < 100) ){
		tab[i++] = buf;
	}
	sort(tab, i);
	wyswietl(tab, i);
}

