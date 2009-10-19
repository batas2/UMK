#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void kopiuj(FILE *fp, FILE *fp2){
	char c[1024];
	while( fgets(c, 1024, fp) != NULL ){
		if( strstr(c, "programowanie") != NULL ){
			fprintf(fp2, "%s ", &c);
		}
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
