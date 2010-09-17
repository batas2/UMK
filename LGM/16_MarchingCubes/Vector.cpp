/* 
 * File:   Vector.cpp
 * Author: batas2
 * 
 * Created on 29 maj 2010, 13:10
 */

#include "Vector.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

Vector::Vector(int n) : Matrix(n, 1) {
}

Vector::Vector(Vector a, Vector b) : Matrix(a._n, 1) {
    for (int i = 0; i < a._n; i++) {
        set(i, a(i) - b(i));
    }
}

Vector::Vector(double x, double y) : Matrix(2, 1) {
    set(X, x);
    set(Y, y);
}

Vector::Vector(double x, double y, double z) : Matrix(3, 1) {
    set(X, x);
    set(Y, y);
    set(Z, z);
}

Vector::Vector(double x, double y, double z, int W) : Matrix(4, 1) {
    set(X, x);
    set(Y, y);
    set(Z, z);
    set(3, W);
}

void Vector::Init(int n) {
    _n = n;
    _m = 1;
    _max = _n;
    _vector = new double[_max];
    memset(_vector, 0, _max * sizeof (double));
}

void Vector::plus(Vector& a) {
    for (int i = 0; i < _n; i++) {
        set(i, at(i) + a(i));
    }
}

void Vector::norm() {
    double l = length();
    for (int i = 0; i < _n; i++) {
        set(i, at(i) / l);
    }
}

double Vector::dot(Vector &a) {
    double r = 0;
    for (int i = 0; i < _n; i++) {
        r += at(i) * a(i);
    }
    return r;
}

Vector Vector::cross(Vector &a, Vector &b) {
    Vector A(3);
    Vector B(3);
    for (int i = 0; i < 3; i++) {
        A(i) = at(i) - a(i);
        B(i) = at(i) - b(i);
    }
    Vector result(3);
    result(0) = A(Y) * B(Z) - A(Z) * B(Y);
    result(1) = -A(X) * B(Z) + A(Z) * B(X);
    result(2) = A(X) * B(Y) - A(Y) * B(X);
    return result;
}

double Vector::length() {
    double r = 0;
    for (int i = 0; i < _n; i++) {
        r += at(i) * at(i);
    }
    return sqrt(r);
}