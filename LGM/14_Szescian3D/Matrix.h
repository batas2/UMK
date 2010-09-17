/* 
 * File:   Matrix.h
 * Author: batas2
 *
 * Created on 23 maj 2010, 12:27
 */
#include <iostream>
#include <math.h>

#ifndef _MATRIX_H
#define	_MATRIX_H

#define X 0
#define Y 1
#define Z 2

class Matrix {
protected:
    int _n, _m, _max;
    double *_vector;
public:

    Matrix() {

    }

    Matrix(int n, int m);
    void Init(int n, int m);

    double at(const int x, const int y) {
        return _vector[x * _m + y];
    }

    void set(int x, int y, double v) {
        _vector[x * _m + y] = v;
    };

    int n() const {
        return _n;
    };

    int m() const {
        return _m;
    };

    double& operator()(const int x, const int y) {
        return _vector[x * _m + y];
    }

    Matrix multi(const Matrix &m);

    void print();
    void Diag(double v);
};

#endif	/* _MATRIX_H */

