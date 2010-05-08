/*
 * File:   MyWidget.cpp
 * Author: batas2
 *
 * Created on 1 kwiecień 2010, 18:02
 */

#include "MyWidget.h"

double MyWidget::Inter(double a, double b, double d) {
    return b * d + a * (1 - d);
}

void MyWidget::Interpolation(double x, double y, int *R, int *G, int *B) {

    int x0, y0, x1, y1;
    double dx, dy;

    if (x <= _PIC_X && x >= 0 && y >= 0 && y <= _PIC_Y) {
        x0 = x;
        y0 = y;

        x1 = x0 + 1;
        y1 = y0 + 1;

        dx = x - x0;
        dy = y - y0;

        *R = Inter(Inter(_bitsPic[AC[y0][x0] + 2], _bitsPic[AC[y0][x1] + 2], dx), Inter(_bitsPic[AC[y1][x0] + 2], _bitsPic[AC[y1][x1] + 2], dx), dy);
        *G = Inter(Inter(_bitsPic[AC[y0][x0] + 1], _bitsPic[AC[y0][x1] + 1], dx), Inter(_bitsPic[AC[y1][x0] + 1], _bitsPic[AC[y1][x1] + 1], dx), dy);
        *B = Inter(Inter(_bitsPic[AC[y0][x0]], _bitsPic[AC[y0][x1]], dx), Inter(_bitsPic[AC[y1][x0]], _bitsPic[AC[y1][x1]], dx), dy);
    } else {
        *R = 255;
        *G = 255;
        *B = 255;
    }
}

void MyWidget::TextureMap() {

    double alSrc = 1 / ((_pointsSrc->at(0).y() - _pointsSrc->at(1).y()) / (double) (_pointsSrc->at(0).x() - _pointsSrc->at(1).x()));
    double aRSrc = 1 / ((_pointsSrc->at(0).y() - _pointsSrc->at(2).y()) / (double) (_pointsSrc->at(0).x() - _pointsSrc->at(2).x()));

    double blSrc = (_pointsSrc->at(1).y() - _pointsSrc->at(0).y()) / (double) (_pointsDest->at(1).y() - _pointsDest->at(0).y());
    double bRSrc = (_pointsSrc->at(2).y() - _pointsSrc->at(0).y()) / (double) (_pointsDest->at(2).y() - _pointsDest->at(0).y());

    double alDest = 1 / ((_pointsDest->at(0).y() - _pointsDest->at(1).y()) / (double) (_pointsDest->at(0).x() - _pointsDest->at(1).x()));
    double aRDest = 1 / ((_pointsDest->at(0).y() - _pointsDest->at(2).y()) / (double) (_pointsDest->at(0).x() - _pointsDest->at(2).x()));

    double xlSrc = _pointsSrc->at(0).x();
    double xRSrc = _pointsSrc->at(0).x();

    double ylSrc = _pointsSrc->at(0).y();
    double yRSrc = _pointsSrc->at(0).y();

    double xlDest = _pointsDest->at(0).x();
    double xRDest = _pointsDest->at(0).x();

    for (int y = _YMin + 1; y < _YMax - 1; y++) {
        bool in = false;
        double p = (xRSrc - xlSrc) / (double) (xRDest - xlDest);
        double xSrc = xlSrc;
        for (int x = _XMin; x < _XMax; x++) {

            if (_bitsDest[AC[y][x] + 1] == 255 && _bitsDest[AC[y][x + 1] + 1] != 255) {
                in = !in;
            }

            if (in) {
                int R, G, B;
                Interpolation(xSrc, ylSrc, &R, &G, &B);
                SetPixel(_bitsDest, x, y, R, G, B);
                xSrc += p;
            }
        }
        xlSrc += alSrc;
        xRSrc += aRSrc;

        ylSrc += blSrc;
        yRSrc += bRSrc;

        xlDest += alDest;
        xRDest += aRDest;
    }
}

void MyWidget::paintEvent(QPaintEvent * e) {
    QPainter paint(this);

    memcpy(_bitsSrc, _imagePic->bits(), _PIC_MAX);
    memset(_bitsDest, 0, _PIC_MAX);

    for (_it = _pointsSrc->begin(); _it != _pointsSrc->end(); _it++) {
        Square(_bitsSrc, *_it, 255);
    }

    for (_it = _pointsDest->begin(); _it != _pointsDest->end(); _it++) {
        Square(_bitsDest, *_it, 255);
    }

    if (_pointsSrc->size() == 3) {
        Line(_bitsSrc, *(_pointsSrc->begin()), *(_pointsSrc->begin() + 1), 0, 255);
        Line(_bitsSrc, *(_pointsSrc->begin() + 1), *(_pointsSrc->begin() + 2), 0, 255);
        Line(_bitsSrc, *(_pointsSrc->begin() + 2), *(_pointsSrc->begin()), 0, 255);
    }

    if (_pointsDest->size() == 3) {
        Line(_bitsDest, *(_pointsDest->begin()), *(_pointsDest->begin() + 1), 0, 255);
        Line(_bitsDest, *(_pointsDest->begin() + 1), *(_pointsDest->begin() + 2), 0, 255);
        Line(_bitsDest, *(_pointsDest->begin() + 2), *(_pointsDest->begin()), 0, 255);
    }

    if (_pointsSrc->size() == 3 && _pointsDest->size() == 3) {
        TextureMap();
    }
    paint.drawImage(QPoint(0, 0), *_imageSrc);
    paint.drawImage(QPoint(_PIC_X, 0), *_imageDest);
}

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {
    setFixedSize(Width, Height);

    _imagePic = new QImage("zuk.jpg");

    _imageDest = new QImage(_PIC_X, _PIC_Y, QImage::Format_RGB32);
    _imageSrc = new QImage(_PIC_X, _PIC_Y, QImage::Format_RGB32);

    _bitsPic = _imagePic->bits();

    _bitsDest = _imageDest->bits();
    _bitsSrc = _imageSrc->bits();

    _pointsDest = new vector<QPoint > ();
    _pointsSrc = new vector<QPoint > ();

    _point_size = 3;
    _XMax = 0;
    _YMax = 0;
    _XMin = _PIC_X;
    _YMin = _PIC_Y;

    memcpy(_bitsSrc, _imagePic->bits(), _PIC_MAX);
    memset(_bitsDest, 0, _PIC_MAX);

    for (int i = 0; i < _PIC_Y; i++) {
        for (int j = 0; j < _PIC_X; j++) {
            AC[i][j] = (_PIC_X * i + j) << 2;
        }
    }
}

void MyWidget::Square(uchar *bits, QPoint &p, uchar R, uchar G, uchar B) {
    for (int i = p.y() - _point_size; i <= p.y() + _point_size; i++) {
        for (int j = p.x() - _point_size; j <= p.x() + _point_size; j++) {
            SetPixel(bits, j, i, R, G, B);
        }
    }
}

void MyWidget::Line(uchar *bits, QPoint &s, QPoint &t, uchar R, uchar G, uchar B) {
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

void MyWidget::mouseMoveEvent(QMouseEvent *e) {
    if (_move) {
        if (e->x() > _PIC_X) {
            _moveIt->setX(e->x() - _PIC_X);
            if (e->x() - _PIC_X > _XMax) _XMax = e->x() - _PIC_X;
            if (e->x() - _PIC_X < _XMin) _XMin = e->x() - _PIC_X;
            if (e->y() > _YMax) _YMax = e->y();
            if (e->y() < _YMin) _YMin = e->y();
        } else {
            _moveIt->setX(e->x());
        }
        _moveIt->setY(e->y());
        repaint();
    }
}

void MyWidget::mousePressEvent(QMouseEvent *e) {

    int x = e->x();
    int y = e->y();

    _move = false;

    for (_it = _pointsSrc->begin(); _it < _pointsSrc->end(); _it++) {
        if ((y >= _it->y() - _point_size) && (y <= _it->y() + _point_size) &&
                (x >= _it->x() - _point_size) && (x <= _it->x() + _point_size)) {
            _moveIt = _it;
            _move = true;
        }
    }

    if (!_move) {
        x -= _PIC_X;
        for (_it = _pointsDest->begin(); _it < _pointsDest->end(); _it++) {
            if ((y >= _it->y() - _point_size) && (y <= _it->y() + _point_size) &&
                    (x >= _it->x() - _point_size) && (x <= _it->x() + _point_size)) {
                _moveIt = _it;
                _move = true;
            }
        }
    }

    if (!_move) {
        if (e->x() > _PIC_X) {
            if (e->x() - _PIC_X > _XMax) _XMax = e->x() - _PIC_X;
            if (e->x() - _PIC_X < _XMin) _XMin = e->x() - _PIC_X;
            if (e->y() > _YMax) _YMax = e->y();
            if (e->y() < _YMin) _YMin = e->y();
        }
        if (e->x() / _PIC_X == 0 && _pointsSrc->size() < 3) {
            _pointsSrc->push_back(QPoint(e->x(), e->y()));
        } else if (e->x() / _PIC_X == 1 && _pointsDest->size() < 3) {
            _pointsDest->push_back(QPoint(e->x() - _PIC_X, e->y()));
        }
    }

    repaint();
}

MyWidget::~MyWidget() {
    delete _imagePic;
    delete _imageDest;
    delete _imageSrc;
    delete _pointsDest;
    delete _pointsSrc;
}