#include<stdio.h>
#include<stdlib.h>

int main(){
	char c;
	/*c = getchar();
	while(c != EOF){
		putchar(c);
		c = getchar();
	}
	return 0;*/
	while( (c = getchar()) != EOF){
		if(c <= 'Z' && c >= 'A'){
			c = c + 'a' - 'A';
		}if(c <= 'z' && c >= 'a'){
			c = c - 'a' - 'A';
		}
		putchar(c);
	}
}
