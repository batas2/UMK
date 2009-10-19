#include<stdio.h>
#define true 1
#define false 0
#define minus(a, b) (a - b)
#define wiekszy(a, b) ( (a > b) ? (a) : (b) )
#define mniejszy(a, b) ( (a > b) ? (b) : (a) )
#define rowny(a, b)  ( (a == b) ?  true : false )
#define petla(x) while(x)
#define przypisz(x, v) (x = v)
#define NWD(a, b) petla( rowny(rowny(a, b), false) ){ przypisz(wiekszy(a, b),  wiekszy(a, b) - miniejsz(a, b)) }

int main(){
	NWD(18, 8); 
}
