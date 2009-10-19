#include<stdio.h>
#include<stdlib.h>

int main(){

	int *p = NULL;
	int i = 1, ilosc = 0, n; 
	while(i){
		scanf("%d", &n);
		ilosc++;
		p=(int *)realloc(p, ilosc*sizeof(int));
		p[ilosc - 1] = n;
		if (n == 0) i = 0;
	}	
}
