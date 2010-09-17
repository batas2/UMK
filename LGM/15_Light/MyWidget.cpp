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

        *R = Inter(Inter(bits[_ac[y0][x0] + 2], bits[_ac[y0][x1] + 2], dx),
                Inter(bits[_ac[y1][x0] + 2], bits[_ac[y1][x1] + 2], dx), dy);
        *G = Inter(Inter(bits[_ac[y0][x0] + 1], bits[_ac[y0][x1] + 1], dx),
                Inter(bits[_ac[y1][x0] + 1], bits[_ac[y1][x1] + 1], dx), dy);
        *B = Inter(Inter(bits[_ac[y0][x0]], bits[_ac[y0][x1]], dx),
                Inter(bits[_ac[y1][x0]], bits[_ac[y1][x1]], dx), dy);
    } else {
        *R = 0;
        *G = 0;
        *B = 0;
    }
}

void MyWidget::TextureMapFlatLight(uchar *bitsSrc, uchar *bitsDest,
        int A, int B, int C, double Light, bool up) {

    Vector T[3];
    T[0] = _figure2D[A];
    T[1] = _figure2D[B];
    T[2] = _figure2D[C];

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
                if (Light != 0) {
                    r *= Light * _lightPow;
                    g *= Light * _lightPow;
                    b *= Light * _lightPow;

                    r = r < 0 ? 0 : r;
                    r = r > 255 ? 255 : r;
                    g = g < 0 ? 0 : g;
                    g = g > 255 ? 255 : g;
                    b = b < 0 ? 0 : b;
                    b = b > 255 ? 255 : b;
                }
                SetPixel(bitsDest, x, y, r, g, b);
            }
        }
    }
}

void MyWidget::TextureMapGouraudLight(uchar* bitsSrc, uchar* bitsDest, int a, int b, int c, double Light, bool up) {

    Vector T[3];

    T[0] = _figure2D[a];
    T[1] = _figure2D[b];
    T[2] = _figure2D[c];

    double L[3];
    L[0] = _pointNormal[a].dot(_light);
    L[1] = _pointNormal[b].dot(_light);
    L[2] = _pointNormal[c].dot(_light);


    int XMin, XMax, YMin, YMax;
    int A = 0, B = 0, C = 0;

    XMax = 0;
    YMax = 0;
    XMin = _PIC_X;
    YMin = _PIC_Y;

    for (int i = 0; i < 3; i++) {
        if (T[i](X) > XMax) XMax = T[i](X);
        if (T[i](X) < XMin) XMin = T[i](X);
        if (T[i](Y) >= YMax) {
            if (T[i](Y) == YMax) {
                if (T[i](X) < T[B](X)) {
                    B = i;
                    YMax = T[i](Y);
                }
            } else {
                B = i;
                YMax = T[i](Y);
            }

        }
        if (T[i](Y) <= YMin) {
            if (T[i](Y) == YMin) {
                if (T[i](X) < T[A](X)) {
                    A = i;
                    YMin = T[i](Y);
                }
            } else {
                A = i;
                YMin = T[i](Y);
            }
        }
    }

    switch (A) {
        case 0:
            switch (B) {
                case 1: C = 2;
                    break;
                case 2: C = 1;
                    break;
            }
            break;
        case 1:
            switch (B) {
                case 0: C = 2;
                    break;
                case 2: C = 0;
                    break;
            }
            break;
        case 2:
            switch (B) {
                case 1: C = 0;
                    break;
                case 0: C = 1;
                    break;
            }
            break;
    }


    int AL = A, BL = B, CL = C;
    if (!up) {
        AL = C, BL = B, CL = A;
    }

    double deltaXAB = (T[B](X) - T[A](X)) / (T[B](Y) - T[A](Y));
    double deltaXAC = (T[C](X) - T[A](X)) / (T[C](Y) - T[A](Y));
    double deltaXBC = (T[C](X) - T[B](X)) / (T[C](Y) - T[B](Y));

    double deltaLAB = (L[BL] - L[AL]) / (T[B](Y) - T[A](Y));
    double deltaLAC = (L[CL] - L[AL]) / (T[C](Y) - T[A](Y));
    double deltaLBC = (L[CL] - L[BL]) / (T[C](Y) - T[B](Y));

    double DZ = (T[0](X) - T[1](X)) * (T[0](Y) - T[2](Y)) - (T[0](Y) - T[1](Y)) * (T[0](X) - T[2](X));

    double Ax = T[A](X), Bx = T[A](X), Al = L[AL], Bl = L[AL];

    for (int y = YMin; y < YMax; y++) {

        double xMin, xMax;
        if (Ax > Bx) {
            xMin = Bx;
            xMax = Ax;
        } else {
            xMin = Ax;
            xMax = Bx;
        }
        if (xMin < XMin) xMin = XMin;
        if (xMax > XMax) xMax = XMax;
        double deltaL = (Bl - Al) / (xMax - xMin);
        double l = Al;
        for (int x = xMin; x < xMax; x++) {

            double v = ((x - T[1](X)) * (T[0](Y) - T[1](Y)) - (y - T[1](Y)) * (T[0](X) - T[1](X))) / DZ;
            double w = ((T[2](X) - T[1](X))*(y - T[1](Y)) - (T[2](Y) - T[1](Y))*(x - T[1](X))) / DZ;
            double u = 1 - w - v;

            double Px, Py;
            int r, g, b;

            if (!up) {
                Px = u * _PIC_X + v * 1 + w * 1;
                Py = u * _PIC_Y + v * 1 + w * _PIC_Y;
            } else {
                Px = u * _PIC_X + v * 1 + w * _PIC_X;
                Py = u * _PIC_Y + v * 1 + w * 1;
            }

            Interpolation(bitsSrc, Px, Py, &r, &g, &b);
            if (Light != 0) {
                r *= l * _lightPow;
                g *= l * _lightPow;
                b *= l * _lightPow;

                r = r < 0 ? 0 : r;
                r = r > 255 ? 255 : r;
                g = g < 0 ? 0 : g;
                g = g > 255 ? 255 : g;
                b = b < 0 ? 0 : b;
                b = b > 255 ? 255 : b;
            }
            SetPixel(bitsDest, x, y, r, g, b);
            l += deltaL;
        }

        Ax += deltaXAB;
        if (Ax > XMax) Ax = XMax;
        if (Ax < XMin) Ax = XMin;
        Al += deltaLAB;

        if (y < T[C](Y)) {
            Bx += deltaXAC;
            if (Bx > XMax) Bx = XMax;
            if (Bx < XMin) Bx = XMin;


            Bl += deltaLAC;
        } else {
            Bx += deltaXBC;
            if (Bx > XMax) Bx = XMax;
            if (Bx < XMin) Bx = XMin;


            Bl += deltaLBC;
        }
    }
}

void MyWidget::drawCross(Vector cross, int i) {
    if (SHOWCROSS) {
        int x1 = (_figure3D[i](X) * D) / (_figure3D[i](Z) + D);
        int y1 = (_figure3D[i](Y) * D) / (_figure3D[i](Z) + D);

        int x2 = ((_figure3D[i](X) + cross(X) * 100) * D) / ((_figure3D[i](Z) + cross(Z) * 100) + D);
        int y2 = ((_figure3D[i](Y) + cross(Y) * 100) * D) / ((_figure3D[i](Z) + cross(Z) * 100) + D);
        //cross.print();
        Line(_bitsDest, QPoint(x1, y1), QPoint(x2, y2), 0, 0, 255);
    }
}

void MyWidget::initFigure() {
    _figure3D[0] = Vector(0, 0, 0, W);
    _figure3D[1] = Vector(100, 0, 0, W);
    _figure3D[2] = Vector(100, 0, 100, W);
    _figure3D[3] = Vector(0, 0, 100, W);
    _figure3D[4] = Vector(0, 100, 0, W);
    _figure3D[5] = Vector(100, 100, 0, W);
    _figure3D[6] = Vector(100, 100, 100, W);
    _figure3D[7] = Vector(0, 100, 100, W);

}

void MyWidget::initFlat() {
    for (int i = 0; i < 6; i++) {
        _polygonNormal[i] = _figure3D[_trianglePolygon[i][0]].cross(_figure3D[_trianglePolygon[i][1]], _figure3D[_trianglePolygon[i][2]]);
        _polygonNormal[i].norm();
    }
}

void MyWidget::initGouraud() {
    int pos[8][3] = {
        {0, 1, 4},
        {0, 3, 4},
        {0, 2, 3},
        {0, 1, 2},
        {1, 4, 5},
        {3, 4, 5},
        {2, 3, 5},
        {1, 2, 5},
    };
    int pointNormalN[8];

    for (int i = 0; i < 8; i++) {
        _pointNormal[i].Init(3);
        pointNormalN[i] = 0;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            _pointNormal[i].plus(_polygonNormal[pos[i][j]]);

            pointNormalN[i]++;
        }

    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            _pointNormal[i](j) /= pointNormalN[i];
        }
        drawCross(_pointNormal[i], i);
    }
}

void MyWidget::paintEvent(QPaintEvent * e) {

    QPainter paint(this);
    memset(_bitsDest, 0, _PIC_MAX);

    initFigure();

    Matrix T_l(4, 4);
    T_l.Diag(1);
    T_l(0, 3) = -50;
    T_l(1, 3) = -50;
    T_l(2, 3) = -50;

    Matrix T_r(4, 4);
    T_r.Diag(1);
    T_r(0, 3) = 50;
    T_r(1, 3) = 50;
    T_r(2, 3) = 50;

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
        Matrix p = T.multi(T_r.multi(Sc.multi(RX.multi(RY.multi(RZ.multi(T_l.multi(_figure3D[i])))))));

        _figure3D[i](X) = p(X, 0);
        _figure3D[i](Y) = p(Y, 0);
        _figure3D[i](Z) = p(Z, 0);

        _figure2D[i] = Vector((p(X, 0) * D) / (p(Z, 0) + D), (p(Y, 0) * D) / (p(Z, 0) + D));
    }

    initFlat();
    initGouraud();

    for (int i = 0; i < 6; i++) {

        Vector cross = _figure2D[_trianglePolygon[i][0]].cross(_figure2D[_trianglePolygon[i][2]], _figure2D[_trianglePolygon[i][1]]);
        if (cross.dot(_POV) > 0) {
            Line(_bitsDest, QPoint(_figure2D[_trianglePolygon[i][0]](X), _figure2D[_trianglePolygon[i][0]](Y)), QPoint(_figure2D[_trianglePolygon[i][1]](X), _figure2D[_trianglePolygon[i][1]](Y)), 255);
            Line(_bitsDest, QPoint(_figure2D[_trianglePolygon[i][2]](X), _figure2D[_trianglePolygon[i][2]](Y)), QPoint(_figure2D[_trianglePolygon[i][3]](X), _figure2D[_trianglePolygon[i][3]](Y)), 255);
            Line(_bitsDest, QPoint(_figure2D[_trianglePolygon[i][1]](X), _figure2D[_trianglePolygon[i][1]](Y)), QPoint(_figure2D[_trianglePolygon[i][3]](X), _figure2D[_trianglePolygon[i][3]](Y)), 255);
            Line(_bitsDest, QPoint(_figure2D[_trianglePolygon[i][0]](X), _figure2D[_trianglePolygon[i][0]](Y)), QPoint(_figure2D[_trianglePolygon[i][2]](X), _figure2D[_trianglePolygon[i][2]](Y)), 255);

            if (_lightMethod == 0) {
                double dotLight = _polygonNormal[_trianglePolygon[i][0]].dot(_light);
                TextureMapFlatLight(_bitsTexture, _bitsDest, _trianglePolygon[i][0], _trianglePolygon[i][1], _trianglePolygon[i][2], (dotLight + 1) / 2, true);
                TextureMapFlatLight(_bitsTexture, _bitsDest, _trianglePolygon[i][3], _trianglePolygon[i][1], _trianglePolygon[i][2], (dotLight + 1) / 2, false);
            } else {
                TextureMapGouraudLight(_bitsTexture, _bitsDest, _trianglePolygon[i][0], _trianglePolygon[i][1], _trianglePolygon[i][2], 1, true);
                TextureMapGouraudLight(_bitsTexture, _bitsDest, _trianglePolygon[i][3], _trianglePolygon[i][1], _trianglePolygon[i][2], 1, false);
            }
        }
    }

    paint.drawImage(QPoint(0, 0), *_imageDest);
    e->accept();
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
            _ac[i][j] = (_PIC_X * i + j) << 2;
        }
    }
    D = 500;

    _light = Vector(0, 0, D);
    _light.norm();
    _lightPow = 1;
    _lightMethod = 1;

    _POV = Vector(0, 0, D);
    _POV.norm();

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

    _trianglePolygon = {
        {0, 1, 3, 2},
        {3, 7, 0, 4},

        {2, 6, 3, 7},
        {1, 5, 2, 6},

        {0, 4, 1, 5},
        {4, 7, 5, 6}
    };
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

void MyWidget::keyPressEvent(QKeyEvent * e) {
    // std::cout << e->key() << std::endl;
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

            _lightPow = 1;

            break;
        case 87:
            D += w * s; //W
            _POV(Z) = D;
            _light(Z) = D;
            _POV.norm();
            _light.norm();
            break;
        case 69: _lightPow += w * q; //e
            if (_lightPow > 5) _lightPow = 5;
            if (_lightPow < 0) _lightPow = 0;
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
        case 70: _lightMethod = _lightMethod == 0 ? 1: 0; //f
            break;
        case 73: Tx += w * s; //i
            break;
        case 79: Ty += w * s; //o
            break;
        case 80: Tz += w * s; //p
            break;
    }
    repaint();
}

void MyWidget::mouseMoveEvent(QMouseEvent * e) {
    _light(X) = e->x();
    _light(Y) = e->y();
    _light.norm();
    repaint();
}

MyWidget::~MyWidget() {
    delete _imageDest;
    delete _imageTexture;
}

