#include<stdlib.h>
#include<stdio.h>

int main(){
	FILE *fp;
	fp = fopen("plik.txt", "r"); //w - zapis; r - odczyt; a - append; b - binary
	char s1[20], s2[20];
	fscanf(fp, "%s %s", &s1, &s2);
	printf("%s  %s\n", s1, s2);
	//fprintf(fp, "%s", "tekst1 tekst2");
	fclose(fp);
}
