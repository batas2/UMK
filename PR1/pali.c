#include<stdio.h>
#include<string.h>

int palindrom(char slowo[]){
	int i = 0;
	for(i = 0; i < strlen(slowo) / 2; i++){
		if (slowo[i] != slowo[strlen(slowo) - i - 1]){
			return 0;
		}
	}
	return 1;
}

int main(){
	char slowo[10];
	scanf("%s", slowo);
	printf("%d\n", palindrom(slowo));
} 
