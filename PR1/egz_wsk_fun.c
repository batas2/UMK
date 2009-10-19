#include<stdio.h>
#include<math.h>

double kwadrat(double x){return x*x;};
	
int main(){
	double (*tab[4])(double);
	int wybor = 1;
	double x = 0;
	tab[0] = &sin;
	tab[1] = &cos;
	tab[2] = &exp;
	tab[3] = &kwadrat;
	while(wybor){
		printf("1 - sin\n2 - cos\n3 - exp\n4 - kwadrat\n");
		scanf("%d", &wybor);
		if(wybor){
			printf("Podaj arg: ");
			scanf("%lf", &x);
			printf("%lf\n", tab[wybor - 1](x));
		}
	}
}
