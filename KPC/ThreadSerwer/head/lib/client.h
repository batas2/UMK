/* 
 * File:   client.h
 * Author: Bartosz Frackowiak
 *
 * Created on 27 styczeń 2010, 19:06
 */

#include "head.h"
#include "net/head.h"
#include "network.h"
#include <map>

#ifndef _CLIENT_H
#define	_CLIENT_H

using namespace std;

class client {
public:
    string Browser;
    string Host;
    string File;

    client(network* Network);

    void assign(string key, string val);
    void response();

    virtual ~client();
private:
    network* _network;
    int _socket;

    map<string, string> _values;
    map<string, string>::iterator _valuesIt;
    
    string _endl;
    string _formatResponse;
    void assignResponse(string val);

    string getVal(string content, string key);
};

#endif	/* _CLIENT_H */

