#include<stdlib.h>
#include<stdio.h>

/*
 * Funkcja listuje tablice wskaznikow na tablice char
 */
int list(char **environ)
{
	int i;
	for(i = 0; i < sizeof(environ); i++){
		printf("%s\n", environ[i]);
	}
}

int main(int argc, char *argv[])
{
	extern char **environ;	//tablica przechowujaca zmienne systemowe

	printf("\n\nZmienne przed zmiana\n\n");
	list(environ);

	printf("\n\nZmienne po zmianie \n\n");
	unsetenv("SHELL");	//usowamy zmienna systemowa
	putenv("MOJA=batas");	//ustawiamy nowa zmienna systemowa
	list(environ);
}
