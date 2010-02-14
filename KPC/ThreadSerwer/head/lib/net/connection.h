/* 
 * File:   socket.h
 * Author: Bartosz Frackowiak
 *
 * Created on 27 styczeń 2010, 19:02
 */
#include "head.h"

#ifndef _SOCKET_H
#define	_SOCKET_H

class connection {
public:
    connection(int Domain, int Type, int Port);

    int getSocket();
    
    virtual int recv(int sd, char *str, int size);
    virtual void send(int sd, const char *str, int size);

    virtual ~connection();
protected:
    int _sd; //deskryptor gniazda
    int _domain, _type, _port;
};

#endif	/* _SOCKET_H */

