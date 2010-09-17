/* 
 * File:   MyWidget.cpp
 * Author: batas2
 * 
 * Created on 23 maj 2010, 12:04
 */

#include "MyWidget.h"

double MyWidget::Inter(double a, double b, double d) {
    return b * d + a * (1 - d);
}

void MyWidget::Interpolation(uchar *bits, double x, double y, int *R, int *G, int *B) {

    int x0, y0, x1, y1;
    double dx, dy;

    if (x < _PIC_X - 1 && x >= 0 && y >= 0 && y < _PIC_Y - 1) {
        x0 = x;
        y0 = y;

        x1 = x0 + 1;
        y1 = y0 + 1;

        dx = x - x0;
        dy = y - y0;

        *R = Inter(Inter(bits[AC[y0][x0] + 2], bits[AC[y0][x1] + 2], dx),
                Inter(bits[AC[y1][x0] + 2], bits[AC[y1][x1] + 2], dx), dy);
        *G = Inter(Inter(bits[AC[y0][x0] + 1], bits[AC[y0][x1] + 1], dx),
                Inter(bits[AC[y1][x0] + 1], bits[AC[y1][x1] + 1], dx), dy);
        *B = Inter(Inter(bits[AC[y0][x0]], bits[AC[y0][x1]], dx),
                Inter(bits[AC[y1][x0]], bits[AC[y1][x1]], dx), dy);
    } else {
        *R = 0;
        *G = 0;
        *B = 0;
    }
}

void MyWidget::TextureMap(uchar *bitsSrc, uchar *bitsDest, int A, int B, int C, bool up) {

    Vector T[3];
    T[0] = _cube2D[A];
    T[1] = _cube2D[B];
    T[2] = _cube2D[C];

    int XMin, XMax, YMin, YMax;

    XMax = 0;
    YMax = 0;
    XMin = _PIC_X;
    YMin = _PIC_Y;

    for (int i = 0; i < 3; i++) {
        if (T[i](X) > XMax) XMax = T[i](X);
        if (T[i](X) < XMin) XMin = T[i](X);
        if (T[i](Y) > YMax) YMax = T[i](Y);
        if (T[i](Y) < YMin) YMin = T[i](Y);
    }

    int r, g, b;
    double a = (T[0](X) - T[1](X)) * (T[0](Y) - T[2](Y)) - (T[0](Y) - T[1](Y)) * (T[0](X) - T[2](X));

    for (int y = YMin; y <= YMax; y++) {
        for (int x = XMin; x <= XMax; x++) {
            double v = ((x - T[1](X)) * (T[0](Y) - T[1](Y)) - (y - T[1](Y)) * (T[0](X) - T[1](X))) / a;
            double w = ((T[2](X) - T[1](X))*(y - T[1](Y)) - (T[2](Y) - T[1](Y))*(x - T[1](X))) / a;
            double u = 1 - w - v;

            if (u + v < 1 && u > 0 && v > 0) {
                double Px;
                double Py;

                if (!up) {
                    Px = u * _PIC_X + v * 1 + w * 1;
                    Py = u * _PIC_Y + v * 1 + w * _PIC_Y;
                } else {
                    Px = u * _PIC_X + v * 1 + w * _PIC_X;
                    Py = u * _PIC_Y + v * 1 + w * 1;
                }

                Interpolation(bitsSrc, Px, Py, &r, &g, &b);
                SetPixel(bitsDest, x, y, r, g, b);
            }
        }
    }
}

void MyWidget::paintEvent(QPaintEvent * e) {

    QPainter paint(this);
    memset(_bitsDest, 0, _PIC_MAX);

    _cube3D[0] = Vector(0, 0, 0, W);
    _cube3D[1] = Vector(A, 0, 0, W);
    _cube3D[2] = Vector(A, 0, A, W);
    _cube3D[3] = Vector(0, 0, A, W);
    _cube3D[4] = Vector(0, A, 0, W);
    _cube3D[5] = Vector(A, A, 0, W);
    _cube3D[6] = Vector(A, A, A, W);
    _cube3D[7] = Vector(0, A, A, W);

    Matrix T_l(4, 4);
    T_l.Diag(1);
    T_l(0, 3) = -(A / 2);
    T_l(1, 3) = -(A / 2);
    T_l(2, 3) = -(A / 2);

    Matrix T_r(4, 4);
    T_r.Diag(1);
    T_r(0, 3) = (A / 2);
    T_r(1, 3) = (A / 2);
    T_r(2, 3) = (A / 2);

    Matrix T(4, 4);
    T.Diag(1);
    T(0, 3) = Tx + 200;
    T(1, 3) = Ty + 150;
    T(2, 3) = Tz + 200;

    Matrix Sc(4, 4);
    Sc(0, 0) = ScX;
    Sc(1, 1) = ScY;
    Sc(2, 2) = ScZ;
    Sc(3, 3) = 1;

    Matrix RX(4, 4);
    RX.Diag(1);
    RX(1, 1) = cos(AlfaX);
    RX(1, 2) = sin(AlfaX);
    RX(2, 1) = -sin(AlfaX);
    RX(2, 2) = cos(AlfaX);

    Matrix RY(4, 4);
    RY.Diag(1);
    RY(0, 0) = cos(AlfaY);
    RY(0, 2) = -sin(AlfaY);
    RY(2, 0) = sin(AlfaY);
    RY(2, 2) = cos(AlfaY);

    Matrix RZ(4, 4);
    RZ.Diag(1);
    RZ(0, 0) = cos(AlfaZ);
    RZ(0, 1) = sin(AlfaZ);
    RZ(1, 0) = -sin(AlfaZ);
    RZ(1, 1) = cos(AlfaZ);

    for (int i = 0; i < 8; i++) {
        Matrix p = T.multi(T_r.multi(Sc.multi(RX.multi(RY.multi(RZ.multi(T_l.multi(_cube3D[i])))))));
        _cube3D[i] = Vector(p(X, 0), p(Y, 0), p(Z, 0));
        _cube2D[i] = Vector((_cube3D[i](X) * D) / (_cube3D[i](Z) + D), (_cube3D[i](Y) * D) / (_cube3D[i](Z) + D));
    }

    for (int i = 0; i < 6; i++) {
        Vector cross = _cube2D[_tri[i][0]].cross(_cube2D[_tri[i][2]], _cube2D[_tri[i][1]]);
        if (cross.dot(POV) > 0) {
            Line(_bitsDest, QPoint(_cube2D[_tri[i][0]](X), _cube2D[_tri[i][0]](Y)), QPoint(_cube2D[_tri[i][1]](X), _cube2D[_tri[i][1]](Y)), 255);
            Line(_bitsDest, QPoint(_cube2D[_tri[i][2]](X), _cube2D[_tri[i][2]](Y)), QPoint(_cube2D[_tri[i][3]](X), _cube2D[_tri[i][3]](Y)), 255);
            Line(_bitsDest, QPoint(_cube2D[_tri[i][1]](X), _cube2D[_tri[i][1]](Y)), QPoint(_cube2D[_tri[i][3]](X), _cube2D[_tri[i][3]](Y)), 255);
            Line(_bitsDest, QPoint(_cube2D[_tri[i][0]](X), _cube2D[_tri[i][0]](Y)), QPoint(_cube2D[_tri[i][2]](X), _cube2D[_tri[i][2]](Y)), 255);
            TextureMap(_bitsTexture, _bitsDest, _tri[i][0], _tri[i][1], _tri[i][2], true);
            TextureMap(_bitsTexture, _bitsDest, _tri[i][3], _tri[i][1], _tri[i][2], false);
        }
    }

    paint.drawImage(QPoint(0, 0), *_imageDest);
    e->accept();
}

void MyWidget::Line(uchar *bits, QPoint s, QPoint t, uchar R, uchar G, uchar B) {
    if (s.x() == t.x()) {
        int yMin = s.y() < t.y() ? s.y() : t.y();
        int yMax = s.y() < t.y() ? t.y() : s.y();

        for (int y = yMin; y < yMax; y++) {
            SetPixel(bits, s.x(), y, R, G, B);
        }
    } else {
        double a = (t.y() - s.y()) / (double) (t.x() - s.x());
        double b = -a * s.x() + s.y();

        if (a >= -1 && a <= 1) {
            int xMin = s.x() < t.x() ? s.x() : t.x();
            int xMax = s.x() < t.x() ? t.x() : s.x();

            double y = a * xMin + b;
            for (int x = xMin; x < xMax; x++) {
                SetPixel(bits, x, y, R, G, B);
                y += a;
            }
        } else {
            int yMin = s.y() < t.y() ? s.y() : t.y();
            int yMax = s.y() < t.y() ? t.y() : s.y();

            double x = (yMin - b) / a;
            double a1 = 1 / a;
            for (int y = yMin; y < yMax; y++) {

                SetPixel(bits, x, y, R, G, B);
                x += a1;
            }
        }
    }
}

MyWidget::MyWidget(int Width, int Height, QWidget * parent) : QWidget(parent) {
    setFixedSize(Width, Height);

    _imageTexture = new QImage("zuk.jpg");
    _imageDest = new QImage(_PIC_X, _PIC_Y, QImage::Format_RGB32);

    _bitsTexture = _imageTexture->bits();
    _bitsDest = _imageDest->bits();

    memset(_bitsDest, 0, _PIC_MAX);

    for (int i = 0; i < _PIC_Y; i++) {
        for (int j = 0; j < _PIC_X; j++) {
            AC[i][j] = (_PIC_X * i + j) << 2;
        }
    }

    D = 500;
    A = 100;

    POV = Vector(0, 0, D);

    ScX = 1;
    ScY = 1;
    ScZ = 1;

    AlfaX = 0;
    AlfaY = 0;
    AlfaZ = 0;

    Tx = 0;
    Ty = 0;
    Tz = 0;

    W = 1;

    w = 1;

    _tri = {
        {0, 1, 3, 2},
        {3, 7, 0, 4},
        {2, 6, 3, 7},
        {1, 5, 2, 6},
        {0, 4, 1, 5},
        {4, 7, 5, 6}
    };
}

void MyWidget::keyPressEvent(QKeyEvent * e) {
    //std::cout << e->key() << std::endl;
    int s = 15;
    double q = 0.1;

    switch (e->key()) {
        case 81: //Q
            if (w == 1) {
                w = -1;
            } else {
                w = 1;
            }
            break;
        case 82: //R
            D = 500;

            ScX = 1;
            ScY = 1;
            ScZ = 1;

            AlfaX = 0;
            AlfaY = 0;
            AlfaZ = 0;

            Tx = 0;
            Ty = 0;
            Tz = 0;

            break;
        case 87: D += w * s; //W
            break;
        case 69: W += w * q; //W
            break;
        case 65: ScX += w * q; //A
            break;
        case 83: ScY += w * q; //s
            break;
        case 68: ScZ += w * q; //d
            break;
        case 90: AlfaX += w * q; //z
            break;
        case 88: AlfaY += w * q; //x
            break;
        case 67: AlfaZ += w * q; //c
            break;
        case 73: Tx += w * s;
            break;
        case 79: Ty += w * s;
            break;
        case 80: Tz += w * s;

            break;
    }
    repaint();
}

MyWidget::~MyWidget() {
    delete _imageDest;
    delete _imageTexture;
}

