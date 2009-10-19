#include<stdio.h>
int nwd(int, int);
int nww(int, int, int);

int main(){
	int a = 20;
	int b = 25;
	printf("NWD: %d\n", nwd(a, b)); 
	printf("NWW: %d\n", nww(a, b, nwd(a, b)));
}

int nww(int a, int b, int xnwd){
	return (a*b) / xnwd;
}

int nwd(int a, int b){
	if(a%b == 0){
		return b;
	}else{
		nwd(b, a % b);  
	}
}
