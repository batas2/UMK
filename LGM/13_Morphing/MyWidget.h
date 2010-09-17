/*
 * File:   MyWidget.h
 * Author: batas2
 *
 * Created on 1 kwiecień 2010, 18:02
 */

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QGroupBox>
#include <QtGui/QSlider>
#include <QtGui/QPushButton>
#include <QPoint>
#include <vector>
#include <iostream>

#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

#define _PIC_X 400
#define _PIC_Y 300
#define _PIC_MAX 30000 << 4

using namespace std;

class MyWidget : public QWidget {
    Q_OBJECT
private:

    QImage *_imageAPic;
    QImage *_imageBPic;

    QImage *_imageA;
    QImage *_imageB;

    QImage *_imageDest;

    uchar *_bitsA;
    uchar *_bitsB;
    uchar *_bitsDest;

    vector<QPoint> *_pointsA;
    vector<QPoint> *_pointsB;

    vector<QPoint>::iterator _it;
    vector<QPoint>::iterator _moveIt;

    QGroupBox *_groupBox;
    QSlider *_slider;
    QPushButton *_button;

    bool _move;
    int _point_size;

    int AC[_PIC_Y][_PIC_X];


    double Inter(double a, double b, double d);
    void Interpolation(uchar *_bits, double x, double y, int *R, int *G, int *B);
    void Blend(double alfa);

    void Line(uchar *bits, QPoint &s, QPoint &t, uchar R = 0, uchar G = 0, uchar B = 0);
    void Square(uchar *bits, QPoint &p, uchar R = 0, uchar G = 0, uchar B = 0);

    void Paint(double v = 0);

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(uchar *bits, int x, int y, uchar R = 0, uchar G = 0, uchar B = 0) {
        if (x > 0 && y > 0 && x < _PIC_X && y < _PIC_Y) {
            bits[AC[y][x]] = B;
            bits[AC[y][x] + 1] = G;
            bits[AC[y][x] + 2] = R;
        }
    }

    int GetPixel(uchar *bits, int x, int y) {
        int r = 0;
        if (x > 0 && y > 0 && x < _PIC_X && y < _PIC_Y) {
            r = bits[AC[y][x]];
            r += bits[AC[y][x] + 1] << 8;
            r += bits[AC[y][x] + 2] << 16;
        }
        return r;
    }
    ~MyWidget();

public slots:
    void setSliderValue(int);
    void buttonClicked();
};

#endif	/* _MYWIDGET_H */

