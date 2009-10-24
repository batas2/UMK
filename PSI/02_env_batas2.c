#include<stdlib.h>
#include<stdio.h>

/*
 * Funkcja listuje tablice wskaznikow na tablice char
 */
int list(char **environ)
{
	int i = 0;
	while(environ[i] != '\0'){
		printf("%s\n", environ[i++]);
	}
}

int main(int argc, char *argv[])
{
	extern char **environ;	//tablica przechowujaca zmienne systemowe

	printf("\n\nZmienne przed zmiana\n\n");
	list(environ);

	printf("\n\nZmienne po zmianie \n\n");
	unsetenv("SHELL");	//usowamy zmienna systemowa
	putenv("MOJA=batas2");	//ustawiamy nowa zmienna systemowa
	list(environ);
}
