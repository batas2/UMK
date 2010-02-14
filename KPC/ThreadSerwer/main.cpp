/* 
 * File:   main.cpp
 * Author: batas2
 *
 * Created on 29 styczeń 2010, 21:18
 */

#include <iostream>
#include <boost/thread/thread.hpp>
#include "head/lib/MainThread.h"

int main(int argc, char** argv)
{
	network n;
	if (n.getSocket() != -1) {
		while (1) {
			client c(&n);
			MainThread m(&c);
			boost::thread thrd(m);
			std::cout << "Watek: " << thrd.get_id() << std::endl;
		}
	}
	return(0);
}

