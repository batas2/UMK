#include<stdlib.h>
#include<unistd.h>
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	printf("PID: %d\nPPID: %d\n", getpid(), getppid());
}
