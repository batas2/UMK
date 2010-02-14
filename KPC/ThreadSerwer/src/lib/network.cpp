/* 
 * File:   net.cpp
 * Author: Bartosz Frackowiak
 * 
 * Created on 27 styczeń 2010, 19:06
 */

#include "../../head/lib/network.h"

network::network()
{
	this->_connection = new tcpv4(DEFAULT_DOMAIN, DEFAULT_TYPE, DEFAULT_PORT);
}

int network::getSocket()
{
	return this->_connection->getSocket();
}

int network::recv(int sd, char *str, int size)
{
	return this->_connection->recv(sd, str, size);
}

void network::send(int sd, const char *str, int size)
{
	this->_connection->send(sd, str, size);
}

network::~network()
{
	//delete this->_connection;
}

