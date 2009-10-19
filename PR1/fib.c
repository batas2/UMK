#include<stdlib.h>
#include<stdio.h>

int main(){
	const int n = 20;
	int i;
	int fib[n];
	fib[0] = 1;
	fib[1] = 1;
	for(i = 2; i < n; i++){
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	for(i = 0; i < n; i++){
		printf("%d, ", fib[i]);
	}
	printf("\n");
}
