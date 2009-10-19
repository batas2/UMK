#include<stdlib.h>
#include<time.h>
#include<stdio.h>

int main(){
	int n;
	printf("Podaj rozmiar tablicy: ");
	scanf("%d", &n);
	int *tab = (int *)malloc(sizeof(int) * n);
	int i = 0; 
	srand(time(NULL));
	for(i = 0; i<n; i++){
		*(tab + i) = rand() % n;
	}
	int j = 0; 
	for(i = 0; i < n - 1; i++){
		int m = i;
		for(j = i; j < n; j++){
			if( *(tab + j) > *(tab + m)){
				m = j;
			}
		}	
		int b = *(tab + m);
		*(tab + m) = *(tab + i);
		*(tab + i) = b;
		
	}
	for(i = 0; i<n;i++){
		printf("%d\n",*(tab + i));
	}	
}
