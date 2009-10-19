#include<stdio.h>
#include<stdlib.h>

int main(){
	char c;
	int w, l, z;
	w = 0; l = 0; z = 0;

	int tab[10];
	int i;
  	for(i = 0; i<10; i++){
		tab[i] = 0;
	}	
	while( (c = getchar()) != EOF){
		switch(c){
			case ' ': w++; break;
			case '\t': w++; break;
			case '\n': l++; w++; break;
			case '0': tab[0]++; break;
			case '1': tab[1]++; break;
			case '2': tab[2]++; break;
			case '3': tab[3]++; break;
			case '4': tab[4]++; break;
			case '5': tab[5]++; break;
			case '6': tab[6]++; break;
			case '7': tab[7]++; break;
			case '8': tab[8]++; break;
			case '9': tab[9]++; break;
		}
		z++;
	}
	printf("liter: %d\n", z);
	printf("wyrazow: %d\n", w);
	printf("wierszy: %d\n", l);
	for(i = 0; i < 10; i++){
		printf("Cyfra %d wystawpila %d razy\n", i, tab[i]);
	} 
}
