/* 
 * File:   Point.h
 * Author: batas2, http://www.batas2.boo.pl/
 *
 * Created on 7 kwiecień 2010, 13:24
 */

#ifndef _POINT_H
#define	_POINT_H

class Point {
public:
    int X, Y;
    int R, G, B;

    Point();
    Point(int X, int Y, int R = 0, int G = 0, int B = 0);
};

#endif	/* _POINT_H */

