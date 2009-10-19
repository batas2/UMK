#include<stdlib.h>
#include<stdio.h>

int main(){
	FILE *fp;
	char c;
	fp = fopen("plik.txt", "r"); //w - zapis; r - odczyt; a - append; b - binary
	while( (c=getc(fp)) != EOF){
		putc(c, stdout);
	}	
	fclose(fp);
}
