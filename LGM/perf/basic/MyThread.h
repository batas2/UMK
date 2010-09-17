/* 
 * File:   MyThread.h
 * Author: batas2
 *
 * Created on 29 kwiecień 2010, 11:38
 */

#include "main.h"

#ifndef _MYTHREAD_H
#define	_MYTHREAD_H

class MyThread : public QThread {
private:
    int _f, _t;
    bool stop;
    int max, min, suma, n;
public:
    MyThread();
    ~MyThread();

    void run();
    void halt();

    void setTime(int t);
};

#endif	/* _MYTHREAD_H */

