/*
 * File:   MyWidget.h
 * Author: batas2
 *
 * Created on 2 kwiecień 2010, 18:04
 */

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QGroupBox>
#include "Point.h"

#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

class MyWidget : public QWidget {
    Q_OBJECT
private:

    QGroupBox *grpMain;
    QGroupBox *grpSH;
    QGroupBox *grpSC;
    QGroupBox *grpObrot;
    QGroupBox *grpTran;

    QSlider *SliderSHY;
    QSlider *SliderSHX;
    QLabel *lblSHX;
    QLabel *lblSHY;

    QSlider *SliderSCX;
    QSlider *SliderSCY;
    QLabel *lblSCX;
    QLabel *lblSCY;

    QSlider *SliderObrot;
    QLabel *lblObrot;

    QSlider *SliderTranX;
    QSlider *SliderTranY;
    QLabel *lblTranX;
    QLabel *lblTranY;

    double Tx, Ty;
    double Scx, Scy;
    double Shx, Shy;
    double alfa;

    double **M_1;
    double **T_o;
    double **Tr;
    double **R;
    double **Sc;
    double **Sh;

    long _maxSrc, _maxDest;

    QImage *_imageSrc, *_imageDest;
    uchar *_bitsSrc, *_bitsDest;

    void p();
    void p2();
    void p3();

    double Det2x2(double **A, int i, int j);
    void Matrix_1(double** R);
    void MatrixXMatix(double **A, double **R);
    void MatrixXVector(double **M, double *V);


    void paintEvent(QPaintEvent * e);
public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(Point p) {
        int b = (500 * p.Y + p.X) << 2;
        if (b > -1 && b < _maxDest && p.X < 500 && p.X > 0) {
            _bitsDest[b] = p.B;
            _bitsDest[b + 1] = p.G;
            _bitsDest[b + 2] = p.R;
        }
    }

    void SetPixel(int x, int y, uchar R, uchar G, uchar B) {
        int b = (500 * y + x) << 2;
        if (b > -1 && b < _maxDest && x < 500 && x > 0) {
            _bitsDest[b] = B;
            _bitsDest[b + 1] = G;
            _bitsDest[b + 2] = R;
        }
    }

    Point GetPixel(int x, int y) {
        int b = (400 * y + x) << 2;

        if (b > -1 && b < _maxSrc) {
            return Point(x, y, _bitsSrc[b + 2], _bitsSrc[b + 1], _bitsSrc[b]);
        }
        return Point();
    }

public slots:
    void setSHXSliderValue(int);
    void setSHYSliderValue(int);

    void setSCXSliderValue(int);
    void setSCYSliderValue(int);

    void setObrotSliderValue(int);

    void setTranXSliderValue(int);
    void setTranYSliderValue(int);

};

#endif	/* _MYWIDGET_H */

