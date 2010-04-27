/* 
 * File:   Point.cpp
 * Author: batas2, http://www.batas2.boo.pl/
 * 
 * Created on 7 kwiecień 2010, 13:24
 */

#include "Point.h"

Point::Point() {
    X = 0;
    Y = 0;
}

Point::Point(int X, int Y, int R, int G, int B) {
    this->X = X;
    this->Y = Y;
    this->R = R;
    this->G = G;
    this->B = B;
}