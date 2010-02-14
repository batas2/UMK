#include <stdlib.h>
#include <xti.h>
#include <stropts.h>
#include <fcntl.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdarg.h>

#define DEV_XTI		"/dev/tcp"
#define SIZE_BUF	32

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
