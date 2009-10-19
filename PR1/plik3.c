#include<stdlib.h>
#include<stdio.h>

void kopiuj(FILE *fp, FILE *fp2){
	char c;
	while( (c = getc(fp)) != EOF){
		putc(c, fp2);
	}
}
int main(int argc, char *argv[]){
	FILE *fp, *fp2;
	char c;
	int i;
	fp2 = fopen("plik2.txt", "a"); 
	for(i = 0; i < argc; i++){
		fp = fopen(argv[i], "r");//r+w
		kopiuj(fp, fp2);
		fclose(fp);
	}
	fclose(fp2);
}
