/* 
 * File:   head.h
 * Author: batas2
 *
 * Created on 29 styczeń 2010, 21:08
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#ifndef _HEAD_H
#define	_HEAD_H

#define SIZE_BUF 1024

#define DEFAULT_DOMAIN AF_INET
#define DEFAULT_TYPE SOCK_STREAM
#define DEFAULT_PORT 2608

#endif	/* _HEAD_H */

