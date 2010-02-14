#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	printf("UID: %d\nEUID: %d\n", getuid(), geteuid());
}
