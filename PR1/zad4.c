#include<stdio.h>
#include<stdlib.h>

int main(){
	int a;
	scanf("%d", &a);
	switch(a){
		case 1: printf("Podano 1"); break;
		case 2: printf("Podano 2"); break;
		default : printf("Inny"); break;
	}
}
