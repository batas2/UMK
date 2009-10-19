#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//isspac sprawdza czy bialy znak
void czytaj(FILE *fp){
	char c[1024];
	while( fgets(c, 1024, fp) != NULL ){
		if( c[0] != '#' ){
			printf("%s", c);
		}
	}
}

int main(){
	FILE *fp;
	fp = fopen("plik.txt", "r");
	czytaj(fp); 
	fclose(fp);
}
