/* 
 * File:   Matrix.cpp
 * Author: batas2
 * 
 * Created on 23 maj 2010, 12:27
 */

#include "Matrix.h"
#include <string.h>
#include <stdio.h>

Matrix::Matrix(int n, int m) {
    Init(n, m);
}

void Matrix::Init(int n, int m) {
    _n = n;
    _m = m;
    _max = n * m;
    _vector = new double[_max];
    memset(_vector, 0, _max * sizeof (double));
    _free = false;
}

void Matrix::Diag(double v) {
    if (_n == _m) {
        for (int i = 0; i < _n; i++) {
            _vector[i * _n + i] = v;
        }
    }
}

void Matrix::print() {
    std::cout << std::endl;
    for (int i = 0; i < _max; i++) {
        std::cout << _vector[i] << "\t";
        if ((i + 1) % _m == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

Matrix Matrix::multi(const Matrix &m) {

    Matrix result(_n, m._m);

    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < m._m; j++) {
            double v = 0;
            for (int k = 0; k < _m; k++) {
                v += _vector[i * _m + k] * m._vector[k * m._m + j];
            }
            result(i, j) = v;
        }
    }
    return result;
}