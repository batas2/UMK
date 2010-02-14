#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> 


#ifndef INET6_ADDRSTRLEN
# define INET6_ADDRSTRLEN 46
#endif /* INET6_ADDRSTRLEN */

#define SIZE_BUF 256
