#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	struct tm *ptm;
	time_t tp;
	time(&tp);
	ptm=localtime(&tp);
	printf("dzien %d, miesiac(0..11) %d, Rok %d, Dzien tyg(0..6) %d\n", ptm->tm_mday, ptm->tm_mon, ptm->tm_year, ptm->tm_wday);
}
