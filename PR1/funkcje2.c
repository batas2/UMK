#include<stdio.h>

static int E = 10;

int nwd(int a, int b){
	while (a != b){
		if (a > b)
			{ a = a - b;}
		else
			b = b - a;
	}	
	return a;
}
