/*
 * File:   MyWidget.h
 * Author: batas2, http://www.batas2.boo.pl/
 *
 * Created on 2 kwiecień 2010, 18:04
 */

#include "main.h"
#include "FrameCounter.h"


#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

class MyWidget : public QWidget {
private:
    int Time;

    double Tx, Ty;
    double Scx, Scy;
    double Shx, Shy;
    double alfa;

    double alfaC[360];

    double ShxC[360];
    double ShyC[360];
    double ScxC[360];
    double ScyC[360];

    double **M_1;
    double **T_o;
    double **Tr;
    double **R;
    double **Sc;
    double **Sh;

    int _func_index;
    long _maxSrc, _maxDest;

    int AC[300][400];
    int BC[500][500];

    QImage *_imageSrc, *_imageDest;
    uchar *_bitsSrc, *_bitsDest;

    void Transform();

    double Det2x2(double **A, int i, int j);
    void Matrix_1(double** R);
    void MatrixXMatix(double **A, double **R);
    void MatrixXVector(double **M, double *V);

    void (MyWidget::*(func[3]))(double x, double y, int *R, int *G, int *B);

    double Inter(double a, double b, double d);

    void Interpolation(double x, double y, int *R, int *G, int *B);
    void Round(double x, double y, int *R, int *G, int *B);
    void Cut(double x, double y, int *R, int *G, int *B);

    MyThread *t;
    FrameCounter fc;

    void paintEvent(QPaintEvent * e);
    void keyPressEvent(QKeyEvent * e);
public:
    MyWidget(int Width, int Height, int Time, QWidget *parent = 0);
    void Start();
};


#endif	/* _MYWIDGET_H */

