#include<stdlib.h>
#include<stdio.h>
struct dane{
	char *s;
	union unia{
		int i;
		int f;
	} u;
} d;

union{
	int i;
	float f;
} u;

int main(){

	d.u.i = 2;
	d.u.f = 3.5;

	u.i = 2;
	u.f = 3.5;
	printf("%f\n", u.f);
	printf("%d\n", u.i);
}
