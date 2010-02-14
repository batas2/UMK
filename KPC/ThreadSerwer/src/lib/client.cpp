/* 
 * File:   client.cpp
 * Author: Bartosz Frackowiak
 * 
 * Created on 27 styczeń 2010, 19:06
 */

#include <iostream>
#include "../../head/lib/client.h"
#include "stdio.h"
#include <stdlib.h>

using namespace std;

client::client(network* Network)
{
	this->_endl = "\r\n";
	assignResponse("HTTP/1.0 200 OK");
	assignResponse("Server: Bartosz Frackowiak ThreadSerwer");
	assignResponse("Content-Type: text/html");
	assignResponse(this->_endl);
	assignResponse("<html>" + this->_endl +"<body>");
	assignResponse("<p><b>User-Agent: </b><!User-Agent!></p>");
	assignResponse("<p><b>Host: </b><!Host!></p>");
	assignResponse("<p><b>File: </b><!File!></p>");
	assignResponse("</body>" + this->_endl +"</html>");

	this->_network = Network;
	this->_socket = Network->getSocket();

	int sockd = -1;
	if ((sockd = accept(this->_socket, NULL, NULL)) == -1) {
		sockd = -1;
	} else {

		this->_socket = sockd;

		char request[SIZE_BUF];
		this->_network->recv(this->_socket, request, SIZE_BUF);

		string content;
		content.assign(request);

		this->Browser = this->getVal(content, "User-Agent: ");
		this->Host = this->getVal(content, "Host: ");
		this->File = this->getVal(content, "GET ");
	}
}

string client::getVal(string content, string key)
{
	int start = (int) content.find(key) + (int) key.length();
	int stop = (int) content.find(this->_endl, start);

	return content.substr(start, stop - start);
}

void client::assignResponse(string val)
{
	this->_formatResponse.append(val + this->_endl);
}

void client::assign(string key, string val)
{
	this->_values.insert(pair<string, string > (key, val));
}

void client::response()
{
	for (_valuesIt = _values.begin(); _valuesIt != _values.end(); _valuesIt++) {

		string key = "<!" + _valuesIt->first + "!>";
		int start = (int) _formatResponse.find(key);
		int stop = key.length();

		_formatResponse.replace(start, stop, _valuesIt->second);
	}

	_formatResponse.append(this->_endl);
	this->_network->send(this->_socket, _formatResponse.data(), _formatResponse.length());
}

client::~client()
{
	close(this->_socket);
}

