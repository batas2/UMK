#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stropts.h>
#include <xti.h>
#include <time.h>

#define DEV_XTI		"/dev/inet/tcp"
#define SIZE_BUF	256

char line[SIZE_BUF];

void error(char *msg, int sd, ...)
{
	va_list arg;
	int i;
	va_start(arg, sd);
	for (i = sd; i; i = va_arg(arg, int)) {
		t_close(i);
	}
	va_end(arg);
	t_error(msg);
	exit(1);
}