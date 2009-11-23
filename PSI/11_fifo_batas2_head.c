#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define SERVER_FIFO "/tmp/serwer_fifo"
#define CLIENT_FIFO "/tmp/client_fifo"
