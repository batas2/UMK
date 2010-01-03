#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>

#define	D	+
#define M	*
#define O	-

#define PROJ	8

#define SIZE_IN		sizeof(float) * 2 + sizeof(int)
#define SIZE_OUT	sizeof(float)

struct msg_in{
	long msg_type;
	float a, b;
	int dzialanie;
};

struct msg_out{
	long msg_type;
	float wynik;
};
