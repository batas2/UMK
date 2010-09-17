/* 
 * File:   Vector.h
 * Author: batas2
 *
 * Created on 29 maj 2010, 13:10
 */

#ifndef _VECTOR_H
#define	_VECTOR_H

#include "Matrix.h"

class Vector : public Matrix {
public:

    Vector() : Matrix() {
    }

    Vector(int n);

    Vector(Vector a, Vector b);

    Vector(double x, double y);
    Vector(double x, double y, double z);
    Vector(double x, double y, double z, int W);


    void Init(int n);

    double at(const int x) {
        return _vector[x];
    }

    void set(int x, double v) {
        _vector[x] = v;
    }

    double& operator()(const int x) {
        return _vector[x];
    }

    double dot(Vector &a);
    Vector cross(Vector &a, Vector &b);

    double length();
};

#endif	/* _VECTOR_H */

