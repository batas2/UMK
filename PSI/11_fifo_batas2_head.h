#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define SIZE_LINE	1024 * 10
#define SIZE_CMD	256 * 4
#define SIZE_FIFO	256 * 4

#define SERWER_FIFO	"/tmp/serwer_fifo"
#define CLIENT_FIFO	"/tmp/client_fifo"
