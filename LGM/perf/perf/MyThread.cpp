/* 
 * File:   MyThread.cpp
 * Author: batas2
 * 
 * Created on 29 kwiecień 2010, 11:38
 */

#include "MyThread.h"
#include "FrameCounter.h"

MyThread::MyThread() {
    _f = 0;
    stop = false;
    min = 999999;
    max = 0;
    suma = 0;
    n = 0;
}

MyThread::~MyThread() {
    stop = true;
}

void MyThread::halt() {
    stop = true;
    std::cout << "Total: " << suma << " Time: " << n << std::endl;
    std::cout << "Min: " << min << " Max: " << max << "Avg: " << suma / (double) n << std::endl;
}

void MyThread::run() {
    while (!stop) {
        this->msleep(1000);

        FrameCounter fc;

        int v = fc.Value() - _f;
        _f = fc.Value();

        std::cout << v << std::endl;
        if (max < v) {
            max = v;
        }
        if (min > v) {
            min = v;
        }


        suma += v;
        n++;

        if (n > _t) {
            fc.CounterStop();
        }
    }
}

void MyThread::setTime(int t) {
    _t = t;
}
