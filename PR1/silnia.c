#include<stdio.h>

long silnia(int n){
	if(n == 0){
		 return 1;
	}else{
		return silnia(n - 1) * n;
	}
}

int main(){
	printf("%d\n", silnia(5));
}
