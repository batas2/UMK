/* 
 * File:   net.h
 * Author: Bartosz Frackowiak
 *
 * Created on 27 styczeń 2010, 19:06
 */

#include "net/connection.h"
#include "net/tcpv4.h"

#ifndef _NET_H
#define	_NET_H

class network {
public:
    network();

    int getSocket();
    
    int recv(int sd, char *str, int size);
    void send(int sd, const char *str, int size);

    virtual ~network();
private:
    connection* _connection;
};

#endif	/* _NET_H */

