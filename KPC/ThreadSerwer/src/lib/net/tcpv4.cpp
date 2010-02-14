/* 
 * File:   tcpv4.cpp
 * Author: Bartosz Frackowiak
 * 
 * Created on 27 styczeń 2010, 19:02
 */

#include "../../../head/lib/net/tcpv4.h"
#include "stdio.h"

tcpv4::tcpv4(int Domain, int Type, int Port) : connection(Domain, Type, Port)
{
	
	this->_addr.sin_family = this->_domain;
	this->_addr.sin_port = htons(this->_port);
	this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	this->_sd = socket(this->_domain, this->_type, 0);

	if (bind(this->_sd, (struct sockaddr *)&this->_addr, sizeof(struct sockaddr_in)) == -1) {
		this->_sd = -1;
		perror("TCPv4:Bind");
	}

	if ( (this->_sd != -1) && (listen(this->_sd, 256) == -1) ) {
		this->_sd = -1;
		perror("TCPv4:Listen");
	}

}

int tcpv4::recv(int sd, char *str, int size)
{
	return read(sd, str, size);
}

void tcpv4::send(int sd, const char *str, int size)
{
	write(sd, str, size);
}

tcpv4::~tcpv4()
{
	close(this->_sd);
}

