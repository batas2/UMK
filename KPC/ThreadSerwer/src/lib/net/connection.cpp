/* 
 * File:   socket.cpp
 * Author: Bartosz Frackowiak
 * 
 * Created on 27 styczeń 2010, 19:02
 */

#include "../../../head/lib/net/connection.h"

connection::connection(int Domain, int Type, int Port)
{
	this->_domain = Domain;
	this->_type = Type;
	this->_port = Port;
}

int connection::getSocket()
{
	return this->_sd;
}

int connection::recv(int sd, char *str, int size)
{
	return -1;
}

void connection::send(int sd, const char *str, int size)
{
	return;
}

connection::~connection()
{
	close(this->_sd);
}

