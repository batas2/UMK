/*
 * File:   main.cpp
 * Author: batas2
 *
 * Created on 2 marzec 2010, 21:49
 */

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QKeyEvent>
#include <math.h>
#include <iostream>

class Point {
public:
    int X, Y, Z;

    Point() {
        this->X = 0;
        this->Y = 0;
        this->Z = 0;
    }

    Point(int X, int Y, int Z) {
        this->X = X;
        this->Y = Y;
        this->Z = Z;
    }
};

class MyWidget : public QWidget {
private:
    int _w, _h;
    int _Xs, _Ys, _Zs;

    int _n;
    int _i, _j;
    long _max;
    bool _Rotate;

    Point _C, _E;

    QImage *_image;
    uchar *_bits;

    Point _points[5][5];
    Point *_P;
    int _Newton[5];

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent * e);
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent * e);

public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(int x, int y, uchar R, uchar G, uchar B) {

        int b = this->_w * 4 * y + 4 * x;
        if (b > -1 && b < this->_max) {
            this->_bits[b] = B;
            this->_bits[b + 1] = G;
            this->_bits[b + 2] = R;
        }
    }

    void SetPixel(int x, int y, int z, uchar R, uchar G, uchar B) {

        int Dx = x - _C.X;
        int Dy = y - _C.Y;
        double Dz = z - _C.Z;

        int X = (Dx - _E.X) / (_E.Z / Dz);
        int Y = (Dy - _E.Y) / (_E.Z / Dz);

        this->SetPixel(X, Y, R, G, B);

    }

    //    void SetPixel(Point p) {
    //
    //        //        sin = 0
    //        //                cos = 1
    //        //        double Dx = cos(_O.Y) * (sin(_O.Z)*(y - _C.Y) + cos(_O.Z) * (x - _C.X)) - sin(_O.Y)*(z - _C.Z);
    //        //        double Dy = sin(_O.X) * (cos(_O.Y)*(z - _C.Z) + sin(_O.Y) * (sin(_O.Z * (y - _C.Y) + cos(_O.Z)*(x - _C.X)))) + cos(_O.X)*(cos(_O.Z)*(y - _C.Y) - sin(_O.Z)*(x - _C.X));
    //        //        double Dz = cos(_O.X) * (cos(_O.Y)*(z - _C.Z) + sin(_O.Y) * (sin(_O.Z * (y - _C.Y) + cos(_O.Z)*(x - _C.X)))) - sin(_O.X)*(cos(_O.Z)*(y - _C.Y) - sin(_O.Z)*(x - _C.X));
    //
    //        //        int X = (Dx - _E.X) / (_E.Z / Dz);
    //        //        int Y = (Dy - _E.Y) / (_E.Z / Dz);
    //        this->SetPixel(p.X, p.Y, p.Z);
    //
    //    }

    void Line(int x, int y, int z, int x1, int y1, int z1, uchar R, uchar G, uchar B);
    void Cube(int x, int y, int z, int a, uchar R, uchar G, uchar B);

    void Bezier();
    void Bezier1();
    void B_Sklejane(int i);
};

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {

    this->_w = Width;
    this->_h = Height;

    _Xs = Width / 2;
    _Ys = Height / 2;
    _Zs = -50;

    this->_n = 5;
    _i = 0;
    _j = 1;

    _Rotate = false;

    _C.Z = -745;
    _E.Z = 800;

    this->_max = this->_w * this->_h * 4;

    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _n; j++) {
            _points[i][j].X = 150 + i * 100;
            _points[i][j].Y = 600 - (i * i * 16);
            _points[i][j].Z = 200 + j * 80;
        }
    }


    _Newton[0] = 1;
    _Newton[1] = 4;
    _Newton[2] = 6;
    _Newton[3] = 4;
    _Newton[4] = 1;

    _points[1][0].Y -= 200;
    _points[1][1].Y -= 200;
    _points[1][2].Y -= 200;
    _points[1][3].Y -= 200;

    _points[2][0].Y += 200;
    _points[2][1].Y += 200;
    _points[2][2].Y += 200;
    _points[2][3].Y += 200;

    _points[3][0].Y -= 200;
    _points[3][1].Y -= 200;
    _points[3][2].Y -= 200;
    _points[3][3].Y -= 200;

    _P = &_points[0][0];

    setFixedSize(this->_w, this->_h);
    _image = new QImage(this->_w, this->_h, QImage::Format_RGB32);
    this->_bits = _image->bits();
    memset(_image->bits(), 255, this->_max);
}

void MyWidget::Line(int x, int y, int z, int x1, int y1, int z1, uchar R, uchar G, uchar B) {

    int Vx = -(x - x1);
    int Vy = -(y - y1);
    int Vz = -(z - z1);

    for (double i = 0; i < 1; i += 0.03) {
        SetPixel(x + Vx*i, y + Vy*i, z + Vz * i, R, G, B);
    }
}

void MyWidget::Cube(int x, int y, int z, int a, uchar R, uchar G, uchar B) {

    for (int i = 0; i < a; i++) {
        this->SetPixel(x + i, y, z, R, G, B);
        this->SetPixel(x, y + i, z, R, G, B);
        this->SetPixel(x + i, y + a, z, R, G, B);
        this->SetPixel(x + a, y + i, z, R, G, B);

        this->SetPixel(x + i, y, z + a, R, G, B);
        this->SetPixel(x, y + i, z + a, R, G, B);
        this->SetPixel(x + i, y + a, z + a, R, G, B);
        this->SetPixel(x + a, y + i, z + a, R, G, B);

        this->SetPixel(x, y, z + i, R, G, B);
        this->SetPixel(x, y + a, z + i, R, G, B);
        this->SetPixel(x + a, y, z + i, R, G, B);
        this->SetPixel(x + a, y + a, z + i, R, G, B);
    }
}

void MyWidget::Bezier1() {
    double u = 0, t = 0;
    while (t <= 1) {
        u = 0;
        while (u <= 1) {

            double x =
                    (_points[0][0].X * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][0].X * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][0].X * u * u * (1 - u)*(1 - u) + 4 * _points[3][0].X * u * u * u * (1 - u) + _points[4][0].X * u * u * u * u) * (1 - t)* (1 - t)* (1 - t)* (1 - t)
                    + 4 * (_points[0][1].X * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][1].X * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][1].X * u * u * (1 - u)*(1 - u) + 4 * _points[3][1].X * u * u * u * (1 - u) + _points[4][1].X * u * u * u * u) * t * (1 - t)* (1 - t)* (1 - t)
                    + 6 * (_points[0][2].X * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][2].X * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][2].X * u * u * (1 - u)*(1 - u) + 4 * _points[3][2].X * u * u * u * (1 - u) + _points[4][2].X * u * u * u * u) * t * t * (1 - t)* (1 - t)
                    + 4 * (_points[0][3].X * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][3].X * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][3].X * u * u * (1 - u)*(1 - u) + 4 * _points[3][3].X * u * u * u * (1 - u) + _points[4][3].X * u * u * u * u) * t * t * t * (1 - t)
                    + (_points[0][4].X * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][4].X * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][4].X * u * u * (1 - u)*(1 - u) + 4 * _points[3][4].X * u * u * u * (1 - u) + _points[4][4].X * u * u * u * u) * t * t * t*t;

            double y =
                    (_points[0][0].Y * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][0].Y * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][0].Y * u * u * (1 - u)*(1 - u) + 4 * _points[3][0].Y * u * u * u * (1 - u) + _points[4][0].Y * u * u * u * u) * (1 - t)* (1 - t)* (1 - t)* (1 - t)
                    + 4 * (_points[0][1].Y * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][1].Y * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][1].Y * u * u * (1 - u)*(1 - u) + 4 * _points[3][1].Y * u * u * u * (1 - u) + _points[4][1].Y * u * u * u * u) * t * (1 - t)* (1 - t)* (1 - t)
                    + 6 * (_points[0][2].Y * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][2].Y * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][2].Y * u * u * (1 - u)*(1 - u) + 4 * _points[3][2].Y * u * u * u * (1 - u) + _points[4][2].Y * u * u * u * u) * t * t * (1 - t)* (1 - t)
                    + 4 * (_points[0][3].Y * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][3].Y * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][3].Y * u * u * (1 - u)*(1 - u) + 4 * _points[3][3].Y * u * u * u * (1 - u) + _points[4][3].Y * u * u * u * u) * t * t * t * (1 - t)
                    + (_points[0][4].Y * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][4].Y * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][4].Y * u * u * (1 - u)*(1 - u) + 4 * _points[3][4].Y * u * u * u * (1 - u) + _points[4][4].Y * u * u * u * u) * t * t * t*t;

            double z =
                    (_points[0][0].Z * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][0].Z * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][0].Z * u * u * (1 - u)*(1 - u) + 4 * _points[3][0].Z * u * u * u * (1 - u) + _points[4][0].Z * u * u * u * u) * (1 - t)* (1 - t)* (1 - t)* (1 - t)
                    + 4 * (_points[0][1].Z * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][1].Z * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][1].Z * u * u * (1 - u)*(1 - u) + 4 * _points[3][1].Z * u * u * u * (1 - u) + _points[4][1].Z * u * u * u * u) * t * (1 - t)* (1 - t)* (1 - t)
                    + 6 * (_points[0][2].Z * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][2].Z * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][2].Z * u * u * (1 - u)*(1 - u) + 4 * _points[3][2].Z * u * u * u * (1 - u) + _points[4][2].Z * u * u * u * u) * t * t * (1 - t)* (1 - t)
                    + 4 * (_points[0][3].Z * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][3].Z * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][3].Z * u * u * (1 - u)*(1 - u) + 4 * _points[3][3].Z * u * u * u * (1 - u) + _points[4][3].Z * u * u * u * u) * t * t * t * (1 - t)
                    + (_points[0][4].Z * (1 - u)*(1 - u)*(1 - u)*(1 - u) + 4 * _points[1][4].Z * u * (1 - u)*(1 - u)*(1 - u) + 6 * _points[2][4].Z * u * u * (1 - u)*(1 - u) + 4 * _points[3][4].Z * u * u * u * (1 - u) + _points[4][4].Z * u * u * u * u) * t * t * t*t;

            SetPixel(x, y, -z, 0, 255, 0);
            u += 0.01;
        }
        t += 0.01;
    }
}

void MyWidget::Bezier() {

    double dv = 0.01, du = 0.01;
    double u = 0, v = 0;

    while (u <= 1) {
        v = 0;
        while (v <= 1) {

            double x = 0, y = 0, z = 0;

            for (int i = 0; i < _n; i++) {
                double x1 = 0, y1 = 0, z1 = 0;

                for (int j = 0; j < _n; j++) {
                    double b = _Newton[j] * pow(v, j) * pow(1 - v, _n - j - 1);
                    x1 += b * _points[i][j].X;
                    y1 += b * _points[i][j].Y;
                    z1 += b * _points[i][j].Z;

                }
                double b = _Newton[i] * pow(u, i) * pow(1 - u, _n - i - 1);
                x += x1 * b;
                y += y1 * b;
                z += z1 * b;
            }
            v += dv;

            SetPixel(x, y, -z, 0, 255, 0);
        }
        u += du;
    }
}

void MyWidget::paintEvent(QPaintEvent * e) {

    memset(_image->bits(), 255, this->_max);

    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _n; j++) {
            Cube(_points[i][j].X, _points[i][j].Y, -_points[i][j].Z, 5, 0, 0, 255);
        }
    }

    Cube(_P->X, _P->Y, -_P->Z, 5, 0, 0, 0);

    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _n - 1; j++) {
            Line(_points[i][j].X + 2, _points[i][j].Y + 2, -_points[i][j].Z + 2, _points[i][j + 1].X + 2, _points[i][j + 1].Y + 2, -_points[i][j + 1].Z, 255, 0, 0);
        }
    }

    for (int i = 0; i < _n - 1; i++) {
        for (int j = 0; j < _n; j++) {
            Line(_points[i][j].X + 2, _points[i][j].Y + 2, -_points[i][j].Z + 2, _points[i + 1][j].X + 2, _points[i + 1][j].Y + 2, -_points[i + 1][j].Z, 255, 0, 0);
        }
    }

    Bezier1();
    //Bezier();
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
}

void MyWidget::mousePressEvent(QMouseEvent * e) {
    if (e->button() == Qt::RightButton) {
        this->_Rotate = true;
    }
}

void MyWidget::mouseMoveEvent(QMouseEvent * e) {

    if (this->_Rotate) {
        _C.X = -(e->x() - _Xs);
        _C.Y = _Ys - e->y();

        //std::cout << "C: " << _C.X << "," << _C.Y << "," << _C.Z << std::endl;
        //std::cout << "E: " << _E.X << "," << _E.Y << "," << _E.Z << std::endl;
        //std::cout << /*e->key() <<*/ std::endl;

    }
    this->repaint();

}

void MyWidget::keyPressEvent(QKeyEvent * e) {
    //std::cout << "C: " << _C.X << "," << _C.Y << "," << _C.Z << std::endl;
    //std::cout << "E: " << _E.X << "," << _E.Y << "," << _E.Z << std::endl;
    //std::cout << e->key() << std::endl;
    int s = 15;
    switch (e->key()) {
        case 82:
            _C.X = 0;
            _C.Y = 0;
            _C.Z = -745;
            _E.X = 0;
            _E.Y = 0;
            _E.Z = 800;

            for (int i = 0; i < _n; i++) {
                for (int j = 0; j < _n; j++) {
                    _points[i][j].X = 150 + i * 100;
                    _points[i][j].Y = 600 - (i * i * 16);
                    _points[i][j].Z = 200 + j * 80;
                }
            }



            _points[1][0].Y -= 200;
            _points[1][1].Y -= 200;
            _points[1][2].Y -= 200;
            _points[1][3].Y -= 200;

            _points[2][0].Y += 200;
            _points[2][1].Y += 200;
            _points[2][2].Y += 200;
            _points[2][3].Y += 200;

            _points[3][0].Y -= 200;
            _points[3][1].Y -= 200;
            _points[3][2].Y -= 200;
            _points[3][3].Y -= 200;

            _P = &_points[0][0];

            break;
        case 84:
            _i++;
            if (_i > 25) {
                _P = &_points[0][0];
                _i = 0;
            } else {
                _P++;
            }
            break;
        case 85:
            _j *= -1;
            break;
        case 89: //OS X  Y
            _P->X = _P->X + (_j * s);
            break;
        case 72: //OS Y  H
            _P->Y = _P->Y + (_j * s);
            break;
        case 71: //OS Z  G
            _P->Z = _P->Z + (_j * s);
            break;
        case 81: _C.X += s;
            break;
        case 87: _C.Y += s;
            break;
        case 69: _C.Z += s;
            break;
        case 73: _C.X -= s;
            break;
        case 79: _C.Y -= s;
            break;
        case 80: _C.Z -= s;
            break;
        case 90: _E.X += s;
            break;
        case 88: _E.Y += s;
            break;
        case 67: _E.Z += s;
            break;
        case 66: _E.X -= s;
            break;
        case 78: _E.Y -= s;
            break;
        case 77: _E.Z -= s;
            break;
    }
    this->repaint();
}

void MyWidget::mouseReleaseEvent(QMouseEvent * e) {
    this->_Rotate = false;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(800, 600);
    widget.show();
    return app.exec();

}