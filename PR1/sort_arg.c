#include<stdlib.h>
#include<time.h>
#include<stdio.h>

int compare(char *x, char *y){
	while( (*x != '\0') && (*y != '\0') ){
		if( *x > *y){
			return -1;
		}else if(*y > *x){
			return 1;
		}
		x++; y++;
	}
}
int main(int argc, char *argv[]){
	int i, j; 
	for(i = 0; i < argc; i++){
		int m = i;
		for(j = i; j < argc; j++){
			if( compare( *(argv + j), *(argv + m) ) == 1){
				m = j;
			}
		}
		char *b = (char *)malloc(sizeof(*(argv + m)));
		b = *(argv + m);
		*(argv + m) = *(argv + i);
		*(argv + i) = b;
		
	}
	for(i = 0; i<argc;i++){
		printf("%s\n",*(argv + i));
	}	
}
