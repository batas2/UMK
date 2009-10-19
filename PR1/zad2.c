#include<stdio.h>
#include<stdlib.h>

int main(){
	int i, a;
	scanf("%d", &a);
	for(i = 0; i <= a; i++){
		if(i % 2 == 0 && i % 3 != 0){
			printf("%d\n", i);
		}
	}
}
