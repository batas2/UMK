/* 
 * File:   tcpv4.h
 * Author: Bartosz Frackowiak
 *
 * Created on 27 styczeń 2010, 19:02
 */

#include "head.h"
#include "connection.h"

#ifndef _TCPV4_H
#define	_TCPV4_H

class tcpv4 : public connection {
public:
    tcpv4(int Domain, int Type, int Port);

    int recv(int sd, char *str, int size);
    void send(int sd, const char *str, int size);

    virtual ~tcpv4();
private:
    struct sockaddr_in _addr;
};

#endif	/* _TCPV4_H */




