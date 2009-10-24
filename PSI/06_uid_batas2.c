#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	printf("UID: %d\nEUID: %d\n", getuid(), geteuid());
}
