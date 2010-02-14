/* 
 * File:   MainThread.cpp
 * Author: Bartosz Frackowiak
 * 
 * Created on 27 styczeń 2010, 19:05
 */

#include "../../head/lib/MainThread.h"

#include <iostream>
#include <stdio.h>
#include <boost/thread/thread.hpp>

MainThread::MainThread(client* c)
{
	this->_client = c;
}

void MainThread::operator ()()
{

	std::cout << "User-Agent: " << this->_client->Browser << std::endl;
	std::cout << "Host: " << this->_client->Host << std::endl;
	std::cout << "File: " << this->_client->File << std::endl;
	std::cout << std::endl;
	
	this->_client->assign("User-Agent", this->_client->Browser);
	this->_client->assign("Host", this->_client->Host);
	this->_client->assign("File", this->_client->File);

	this->_client->response();

}

MainThread::~MainThread()
{

}

