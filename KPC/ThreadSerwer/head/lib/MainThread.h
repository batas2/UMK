/* 
 * File:   MainThread.h
 * Author: Bartosz Frackowiak
 *
 * Created on 27 styczeń 2010, 19:05
 */

#include "head.h"
#include "client.h"
#include "network.h"

#ifndef _MAINTHREAD_H
#define	_MAINTHREAD_H

class MainThread {
public:
    MainThread(client* c);

    void operator()();
    virtual ~MainThread();
private:
    client* _client;
};

#endif	/* _MAINTHREAD_H */

