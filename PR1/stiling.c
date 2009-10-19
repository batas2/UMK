#include<stdio.h>

long stiling(int n, int k){
	if(k == 1){
		return 1;
	}else if(n == k){
		return 1;
	}else if(k > n){
		return 0;
	}else{
		return k * stiling(n - 1, k) + stiling(n - 1, k - 1);
	}
}

long silnia(int n){
	if( n == 0){
		return 1;
	}else{
		return silnia(n - 1) * n;
	}
}

long dwumian(int n, int k){
	return silnia(n) / (silnia(k) * silnia(n - k));
}

long bella(int n){
	if(n == 0){
		return 1;
	}else{
		int k; int wynik = 0;
		for(k = 0; k < n; k++){
			wynik += dwumian(n - 1, k) * bella(k);
		}
		return wynik;
	}
}

int main(){
	printf("stiling 5, 2: %d\n", stiling(5, 2));
	printf("bella 4: %d\n", bella(5));
}  	
