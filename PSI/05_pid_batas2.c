#include<stdlib.h>
#include<unistd.h>
/*
 * Autor: Bartosz Frąckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	printf("PID: %d\nPPID: %d\n", getpid(), getppid());
}
