#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

/*
 * Funkcja przesowa zawartosc zmiennej str o n pozycji w lewo
 */
void move(char *str, int n)
{
	memmove(str, str + n, (strlen(str) - n) * sizeof(char));
	str[strlen(str) - n] = '\0';
	return;
}

/*
 * Funkcja rozdziela zmienna str poprzez znak spacji,
 * wynik zwraca w zmiennej result
 */
void split(char *str, char *result[])
{
	char *pos = NULL;
	int pos_i = 0, i = 0;
	
	/*
	 * Dopuki w str wystepuje spacja, do tablicy result kopiowana
	 * jest zawartosc str do zanku spacji oraz zmienn str 
	 * przesowana jest w lewo o liczbe pozycji rowna pozycji
	 * spacji
	 */
	while( (pos = strstr(str, " ")) != NULL ){
	
		pos_i = pos - str; //obliczam numer pozycji spacji
		strncpy(result[i], str, sizeof(char) * (pos_i));
		result[i++][pos_i] = '\0';
		move(str, pos_i + 1);
	}

		result[i] = str;
	result[i][strlen(result[i]) - 1] = '\0'; //zamienam znak konca lini na \0
	result[i + 1] = NULL; 
	return;
}
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	char *cmd;
	char *arg[10];

	while(1){
		printf("> ");

		cmd = (char *)malloc(sizeof(char) * 255);
		fgets(cmd, sizeof(char) * 255, stdin);
	
		int i = 0;
		for(i = 0; i < 10; i++){
			arg[i] = (char *)malloc(sizeof(char) * 25);
			arg[i][0] = '\0';
		}
	
		split(cmd, arg);
		
		int pid = 0;
		if( (pid = fork()) < 0 ){
			printf("Blad funkcji fork");
		}else{
			if(pid == 0){
				execvp(arg[0], arg);
				/*
				 * Jesli potomek dochodzi do tego miejsc oznacza to
				 * ze funkcja execvp nie wykona³a sie pomyslnie
				 */
				printf("Blad, nie ma takiego polecenia!\n");
				exit(0);
			}else{
				int status;
				wait(&status);
				
				if(WIFEXITED(status) == 0){
					WSTOPSIG(status) ?
						printf("Wyslano sygnal STOP do procesu potomka.") :
					WTERMSIG(status) ? 
						printf("Wyslano sygnal TERM do	procesu potomka.") :
					WIFSIGNALED(status) ? 
						printf("Potomek zakonczyl prace z powodu nie przechwyconego sygnalu.") : 
					WIFSTOPPED(status) ? 
						printf("Potomek zostal zatrzymany.") :
						printf("Potomek zakonczyl statusem: %d", status);
				}
			}
		}
	}
}
