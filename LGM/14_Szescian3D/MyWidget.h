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

#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

class MyWidget : public QWidget {
private:
    QImage *_imageTexture;
    QImage *_imageDest;

    uchar *_bitsTexture;
    uchar *_bitsDest;

    int AC[_PIC_Y][_PIC_X];
    Vector _cube3D[8];
    Vector _cube2D[8];
    int _tri[6][4];

    int w;

    Vector POV;

    double A;
    double D, W;

    double ScX, ScY, ScZ;
    double AlfaX, AlfaY, AlfaZ;
    int Tx, Ty, Tz;

    double Inter(double a, double b, double d);
    void Interpolation(uchar *bits, double x, double y, int *R, int *G, int *B);

    void TextureMap(uchar *bitsSrc, uchar *bitsDest, int A, int B, int C, bool up = false);

    void Line(uchar *bits, QPoint s, QPoint t, uchar R = 0, uchar G = 0, uchar B = 0);

    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent * e);
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

    virtual ~MyWidget();
private:

};

#endif	/* _MYWIDGET_H */