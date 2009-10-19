#include<stdio.h>
#include<time.h>

int main(){
	const int n = 5, m = 3, k=5;
	int i, j;
	int tab1[n][m];
	int tab2[m][k];
	int tab3[n][k];
	srand(time(NULL));

	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			tab1[i][j] = rand()%5;
			printf("%d, ", tab1[i][j]);
		}
		printf("\n");
	}
	printf("\n"); 
	for(i = 0; i < m; i++){
		for(j = 0; j < k; j++){
			tab2[i][j] = rand()%5;
			printf("%d, ", tab2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i = 0; i < n; i++){
		for(j = 0; j < k; j++){
			tab3[i][j] = 0;
		}
	}
	int l;
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			for(l = 0; l < m; l++){
				tab3[i][j] += tab1[i][l] * tab2[l][j];
			}
		}
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			printf("%d, ", tab3[i][j]);
		}		
		printf("\n");
	}  
}
