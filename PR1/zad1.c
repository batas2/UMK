#include<stdio.h>
#include<stdlib.h>

int main(){
	int a, b;
	scanf("%d", &a);
	scanf("%d", &b);
	while (a != b){
		if (a > b){ a -= b;}
		else{ b -= a;}
	}
	printf("%d", a);
}
