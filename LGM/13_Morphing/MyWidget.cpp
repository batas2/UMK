/*
 * File:   MyWidget.cpp
 * Author: batas2
 *
 * Created on 1 kwiecień 2010, 18:02
 */

#include "MyWidget.h"
#include <stdio.h>

void MyWidget::setSliderValue(int v) {
    char buf[18];
    sprintf(buf, "Blending (%d/100)", v);
    _groupBox->setTitle(buf);
    Paint(_slider->value() / (double) 100);
    repaint();
}

void MyWidget::buttonClicked() {
    for (double v = 0; v <= 1; v += 0.01) {
        _slider->setValue(v * 100);
        char buf[18];
        sprintf(buf, "Blending (%d/100)", (int) (v * 100));
        _groupBox->setTitle(buf);
        Paint(v);
        repaint();
    }
}

double MyWidget::Inter(double a, double b, double d) {
    return b * d + a * (1 - d);
}

void MyWidget::Interpolation(uchar *_bits, double x, double y, int *R, int *G, int *B) {

    int x0, y0, x1, y1;
    double dx, dy;

    if (x < _PIC_X - 1 && x >= 0 && y >= 0 && y < _PIC_Y - 1) {
        x0 = x;
        y0 = y;

        x1 = x0 + 1;
        y1 = y0 + 1;

        dx = x - x0;
        dy = y - y0;

        *R = Inter(Inter(_bits[AC[y0][x0] + 2], _bits[AC[y0][x1] + 2], dx), Inter(_bits[AC[y1][x0] + 2], _bits[AC[y1][x1] + 2], dx), dy);
        *G = Inter(Inter(_bits[AC[y0][x0] + 1], _bits[AC[y0][x1] + 1], dx), Inter(_bits[AC[y1][x0] + 1], _bits[AC[y1][x1] + 1], dx), dy);
        *B = Inter(Inter(_bits[AC[y0][x0]], _bits[AC[y0][x1]], dx), Inter(_bits[AC[y1][x0]], _bits[AC[y1][x1]], dx), dy);
    } else {
        *R = 0;
        *G = 0;
        *B = 0;
    }
}

void MyWidget::Blend(double alfa) {

    QPoint pointsDest[3];

    int XMax = 0;
    int YMax = 0;
    int XMin = _PIC_X;
    int YMin = _PIC_Y;

    for (int i = 0; i < 3; i++) {
        pointsDest[i] = QPoint(Inter(_pointsA->at(i).x(), _pointsB->at(i).x(), alfa), Inter(_pointsA->at(i).y(), _pointsB->at(i).y(), alfa));
        if (pointsDest[i].x() > XMax) XMax = pointsDest[i].x();
        if (pointsDest[i].x() < XMin) XMin = pointsDest[i].x();
        if (pointsDest[i].y() > YMax) YMax = pointsDest[i].y();
        if (pointsDest[i].y() < YMin) YMin = pointsDest[i].y();
    }

    int Ar, Ag, Ab;
    int Br, Bg, Bb;
    double a = (pointsDest[0].x() - pointsDest[1].x()) * (pointsDest[0].y() - pointsDest[2].y()) - (pointsDest[0].y() - pointsDest[1].y()) * (pointsDest[0].x() - pointsDest[2].x());

    if (YMin >= 0 && XMin >= 0 && XMax < _PIC_X && YMax < _PIC_Y) {
        for (int y = YMin; y < YMax; y++) {
            for (int x = XMin; x < XMax; x++) {
                double v = ((x - pointsDest[1].x()) * (pointsDest[0].y() - pointsDest[1].y()) - (y - pointsDest[1].y()) * (pointsDest[0].x() - pointsDest[1].x())) / a;
                double w = ((pointsDest[2].x() - pointsDest[1].x())*(y - pointsDest[1].y()) - (pointsDest[2].y() - pointsDest[1].y())*(x - pointsDest[1].x())) / a;
                double u = 1 - w - v;

                if (u + v < 1 && u > 0 && v > 0) {
                    double PAx = u * _pointsA->at(2).x() + v * _pointsA->at(0).x() + w * _pointsA->at(1).x();
                    double PAy = u * _pointsA->at(2).y() + v * _pointsA->at(0).y() + w * _pointsA->at(1).y();

                    double PBx = u * _pointsB->at(2).x() + v * _pointsB->at(0).x() + w * _pointsB->at(1).x();
                    double PBy = u * _pointsB->at(2).y() + v * _pointsB->at(0).y() + w * _pointsB->at(1).y();

                    Interpolation(_bitsA, PAx, PAy, &Ar, &Ag, &Ab);
                    Interpolation(_bitsB, PBx, PBy, &Br, &Bg, &Bb);

                    int R = Inter(Ar, Br, alfa);
                    int G = Inter(Ag, Bg, alfa);
                    int B = Inter(Ab, Bb, alfa);

                    SetPixel(_bitsDest, x, y, R, G, B);
                }
            }
        }
    }
}

void MyWidget::Paint(double v) {
    memcpy(_bitsA, _imageAPic->bits(), _PIC_MAX);
    memcpy(_bitsB, _imageBPic->bits(), _PIC_MAX);
    memset(_bitsDest, 0, _PIC_MAX);

    if (_pointsA->size() == 3 && _pointsB->size() == 3) {
        Blend(v);
    }

    for (_it = _pointsA->begin(); _it != _pointsA->end(); _it++) {
        Square(_bitsA, *_it, 255);
    }

    for (_it = _pointsB->begin(); _it != _pointsB->end(); _it++) {
        Square(_bitsB, *_it, 255);
    }

    if (_pointsA->size() == 3) {
        Line(_bitsA, *(_pointsA->begin()), *(_pointsA->begin() + 1), 0, 255);
        Line(_bitsA, *(_pointsA->begin() + 1), *(_pointsA->begin() + 2), 0, 255);
        Line(_bitsA, *(_pointsA->begin() + 2), *(_pointsA->begin()), 0, 255);
    }

    if (_pointsB->size() == 3) {
        Line(_bitsB, *(_pointsB->begin()), *(_pointsB->begin() + 1), 0, 255);
        Line(_bitsB, *(_pointsB->begin() + 1), *(_pointsB->begin() + 2), 0, 255);
        Line(_bitsB, *(_pointsB->begin() + 2), *(_pointsB->begin()), 0, 255);
    }

}

void MyWidget::paintEvent(QPaintEvent * e) {
    QPainter paint(this);

    paint.drawImage(QPoint(0, 0), *_imageA);
    paint.drawImage(QPoint(_PIC_X, 0), *_imageB);
    paint.drawImage(QPoint(0, _PIC_Y), *_imageDest);
}

MyWidget::MyWidget(int Width, int Height, QWidget * parent) : QWidget(parent) {
    setFixedSize(Width, Height);

    _imageAPic = new QImage("zuk.jpg");
    _imageBPic = new QImage("ptok.jpg");

    _imageA = new QImage(_PIC_X, _PIC_Y, QImage::Format_RGB32);
    _imageB = new QImage(_PIC_X, _PIC_Y, QImage::Format_RGB32);
    _imageDest = new QImage(_PIC_X, _PIC_Y, QImage::Format_RGB32);

    _bitsA = _imageA->bits();
    _bitsB = _imageB->bits();
    _bitsDest = _imageDest->bits();


    _pointsA = new vector<QPoint > ();
    _pointsB = new vector<QPoint > ();

    _groupBox = new QGroupBox(this);
    _groupBox->setGeometry(QRect(_PIC_X, _PIC_Y, _PIC_X, _PIC_Y));
    _groupBox->setTitle("Blending (0/100)");
    _groupBox->setEnabled(false);

    _slider = new QSlider(_groupBox);
    _slider->setOrientation(Qt::Horizontal);
    _slider->setRange(0, 100);
    _slider->setGeometry(QRect(10, 60, 380, 25));

    _button = new QPushButton("Start", _groupBox);
    _button->setGeometry(QRect(10, 100, 380, 25));

    connect(_slider, SIGNAL(sliderMoved(int)), this, SLOT(setSliderValue(int)));
    connect(_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    _point_size = 3;

    memcpy(_bitsA, _imageAPic->bits(), _PIC_MAX);
    memcpy(_bitsB, _imageBPic->bits(), _PIC_MAX);
    memset(_bitsDest, 0, _PIC_MAX);

    for (int i = 0; i < _PIC_Y; i++) {
        for (int j = 0; j < _PIC_X; j++) {
            AC[i][j] = (_PIC_X * i + j) << 2;
        }
    }
    Paint();
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

void MyWidget::mouseMoveEvent(QMouseEvent * e) {
    if (_move) {
        if (e->x() > _PIC_X) {
            _moveIt->setX(e->x() - _PIC_X);
        } else {
            _moveIt->setX(e->x());
        }
        _moveIt->setY(e->y());
        Paint(_slider->value() / (double) 100);
        repaint();
    }
}

void MyWidget::mousePressEvent(QMouseEvent * e) {

    int x = e->x();
    int y = e->y();

    _move = false;

    for (_it = _pointsA->begin(); _it < _pointsA->end(); _it++) {
        if ((y >= _it->y() - _point_size) && (y <= _it->y() + _point_size) &&
                (x >= _it->x() - _point_size) && (x <= _it->x() + _point_size)) {
            _moveIt = _it;
            _move = true;
        }
    }

    if (!_move) {
        x -= _PIC_X;
        for (_it = _pointsB->begin(); _it < _pointsB->end(); _it++) {
            if ((y >= _it->y() - _point_size) && (y <= _it->y() + _point_size) &&
                    (x >= _it->x() - _point_size) && (x <= _it->x() + _point_size)) {
                _moveIt = _it;
                _move = true;
            }
        }
    }

    if (!_move) {
        if (e->x() / _PIC_X == 0 && _pointsA->size() < 3) {
            _pointsA->push_back(QPoint(e->x(), e->y()));
        } else if (e->x() / _PIC_X == 1 && _pointsB->size() < 3) {
            _pointsB->push_back(QPoint(e->x() - _PIC_X, e->y()));
        }
    }

    if (_pointsA->size() == 3 && _pointsB->size() == 3) {
        _groupBox->setEnabled(true);
    }
    Paint(_slider->value() / (double) 100);
    repaint();
}

MyWidget::~MyWidget() {
    delete _imageA;
    delete _imageAPic;
    delete _imageB;
    delete _imageBPic;
    delete _imageDest;
    delete _pointsA;
    delete _pointsB;
}