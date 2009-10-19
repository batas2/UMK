#include<stdio.h>

void clear_bit(int *p, int n){
	n = 1 << n;
	*p = *p & ~n;
}

void set_bit(int *p, int n){
	n = 1 << n;
	*p = *p | n;
}

int test_bit(int a, int n){
	n = 1 << n;
	if(a & n)
		return 1;
	else
		return 0;
}

int main(){
	int p = 22;
	int n = 2;
	clear_bit(&p, n);
	printf("%d\n", p);
	set_bit(&p, n);
	printf("%d\n", p);
	printf("%d\n", test_bit(p, n));
}
