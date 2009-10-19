#include<stdio.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

char zamien(char c){
	return toupper(c);
}

int main(){
	char slowo[20];
	scanf("%s", slowo);
	int i = 0;
	for(i = 0; i < strlen(slowo); i++){
		slowo[i] = zamien(slowo[i]);
	}
	printf("%s\n", slowo);
}	
