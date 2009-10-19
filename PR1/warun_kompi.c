#include "pomoc.h"
#if !define(M) <==> #ifndef
	#define M 10
	#include pomoc1.h
#endif

#ifndef M
	#define M 10
#endif

#if (warunek)
	#define ...
#elif 
	#define ...
#elif
	#define ...
#endif

int main(){

}
