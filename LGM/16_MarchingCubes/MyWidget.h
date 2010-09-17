/* 
 * File:   MyWidget.h
 * Author: batas2
 *
 * Created on 23 maj 2010, 12:04
 */

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QGroupBox>
#include <QtGui/QSlider>
#include <QtGui/QPushButton>
#include <QPoint>
#include "Matrix.h"
#include "Vector.h"
#include <math.h>

#define _PIC_X 400
#define _PIC_Y 300
#define _PIC_MAX 480000

#define X 0
#define Y 1
#define Z 2

#define fR 25
#define fR2 50

#define LIGHT_FLAT 0
#define LIGHT_GOURAUD 1

#define SHOWCROSS false

#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

class MyWidget : public QWidget {
private:
    QImage *_imageTexture;
    QImage *_imageDest;

    uchar *_bitsTexture;
    uchar *_bitsDest;

    int _ac[_PIC_Y][_PIC_X];
    Vector _figure3D[fR2][fR2][fR2];
    Vector _figure2D[fR2][fR2][fR2];
    int _val[fR2][fR2][fR2];

    int _S;

    int w;

    int _func_index;

    double D, W;

    double ScX, ScY, ScZ;
    double AlfaX, AlfaY, AlfaZ;
    int Tx, Ty, Tz;

    Vector _POV;

    double Inter(double a, double b, double d);
    void Interpolation(uchar *bits, double x, double y, int *R, int *G, int *B);

    void initFigure();

    void ScalarField();
    void MarchingCubes();

    void Line(uchar *bits, QPoint s, QPoint t, uchar R = 0, uchar G = 0, uchar B = 0);
    void Triangle(uchar *bits, Vector &A, Vector &B, Vector &C);

    int Polygonise(int x, int y, int z, double isolevel, Vector **&triangles);
    Vector VertexInterp(double isolevel, Vector &p1, Vector &p2, double valp1, double valp2);

    void paintEvent(QPaintEvent * e);
    void keyPressEvent(QKeyEvent * e);

public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(uchar *bits, int x, int y, uchar R = 0, uchar G = 0, uchar B = 0) {

        if (x > 0 && y > 0 && x < _PIC_X && y < _PIC_Y) {
            bits[_ac[y][x]] = B;
            bits[_ac[y][x] + 1] = G;
            bits[_ac[y][x] + 2] = R;
        }
    }

    int GetPixel(uchar *bits, int x, int y) {
        int r = 0;
        if (x > 0 && y > 0 && x < _PIC_X && y < _PIC_Y) {
            r = bits[_ac[y][x]];
            r += bits[_ac[y][x] + 1] << 8;
            r += bits[_ac[y][x] + 2] << 16;
        }
        return r;
    }

    virtual ~MyWidget();
private:

};

#endif	/* _MYWIDGET_H */