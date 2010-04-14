/*
 * File:   MyWidget.cpp
 * Author: batas2
 *
 * Created on 2 kwiecień 2010, 18:04
 */

#include "MyWidget.h"
#include <stdio.h>
#include <math.h>

void MyWidget::setSHXSliderValue(int) {
    Shx = SliderSHX->value() / (double) 50;
    p2();
    repaint();
}

void MyWidget::setSHYSliderValue(int) {
    Shy = SliderSHY->value() / (double) 50;
    p2();
    repaint();
}

void MyWidget::setSCXSliderValue(int) {
    Scx = SliderSCX->value() / (double) 50;
    p2();
    repaint();
}

void MyWidget::setSCYSliderValue(int) {
    Scy = SliderSCY->value() / (double) 50;
    p2();
    repaint();
}

void MyWidget::setObrotSliderValue(int) {
    alfa = SliderObrot->value() * 0.0174;
    //0,0174532925199 = Pi / 180
    p2();
    repaint();
}

void MyWidget::setTranXSliderValue(int) {
    Tx = SliderTranX->value();
    p2();
    repaint();
}

void MyWidget::setTranYSliderValue(int) {
    Ty = SliderTranY->value();
    p2();
    repaint();
}

void MyWidget::paintEvent(QPaintEvent * e) {

    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_imageDest);
    memset(_bitsDest, 255, _maxDest);
}

double* MyWidget::MatrixXVector(double **M, double *V) {
    double *R = new double[3];
    for (int i = 0; i < 3; i++) {
        R[i] = 0;
        for (int j = 0; j < 3; j++) {
            R[i] += M[i][j] * V[j];
        }
    }
    return R;
}

double** MyWidget::MatrixXMatix(double **A, double **B) {
    double **W = new double*[3];
    for (int i = 0; i < 3; i++) {
        W[i] = new double[3];
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            W[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                W[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return W;
}

void MyWidget::p2() {

    double **To = new double*[3];
    for (int i = 0; i < 3; i++) {
        To[i] = new double[3];
        memset(To[i], 0, sizeof (double) * 3);
    }

    To[0][0] = 1;
    To[1][1] = 1;
    To[2][2] = 1;
    To[1][2] = 250;
    To[0][2] = 250;

    double **T_o = new double*[3];
    for (int i = 0; i < 3; i++) {
        T_o[i] = new double[3];
        memset(T_o[i], 0, sizeof (double) * 3);
    }

    T_o[0][0] = 1;
    T_o[1][1] = 1;
    T_o[2][2] = 1;
    T_o[1][2] = -200;
    T_o[0][2] = -150;

    double **Tr = new double*[3];
    for (int i = 0; i < 3; i++) {
        Tr[i] = new double[3];
        memset(Tr[i], 0, sizeof (double) * 3);
    }

    Tr[0][0] = 1;
    Tr[1][1] = 1;
    Tr[2][2] = 1;
    Tr[1][2] = Tx;
    Tr[0][2] = Ty;

    double **R = new double*[3];
    for (int i = 0; i < 3; i++) {
        R[i] = new double[3];
        memset(R[i], 0, sizeof (double) * 3);
    }

    R[0][0] = cos(alfa);
    R[0][1] = -sin(alfa);
    R[1][0] = sin(alfa);
    R[1][1] = cos(alfa);
    R[2][2] = 1;

    double **Sc = new double*[3];
    for (int i = 0; i < 3; i++) {
        Sc[i] = new double[3];
        memset(Sc[i], 0, sizeof (double) * 3);
    }

    Sc[0][0] = Scx;
    Sc[1][1] = Scy;
    Sc[2][2] = 1;

    double **Sh = new double*[3];
    for (int i = 0; i < 3; i++) {
        Sh[i] = new double[3];
        memset(Sh[i], 0, sizeof (double) * 3);
    }

    Sh[0][0] = 1;
    Sh[1][1] = 1;
    Sh[2][2] = 1;
    Sh[0][1] = Shx;
    Sh[1][0] = Shy;

    double **A;
    A = MatrixXMatix(T_o, Sc);
    A = MatrixXMatix(Sh, A);
    A = MatrixXMatix(R, A);
    A = MatrixXMatix(To, A);
    A = MatrixXMatix(Tr, A);

    double *v = new double[3];

    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 400; j++) {

            Point p = GetPixel(j, i);

            v[0] = p.X;
            v[1] = p.Y;
            v[2] = 1;

            v = MatrixXVector(A, v);

            p.X = v[0];
            p.Y = v[1];

            SetPixel(p);
        }
    }
}

void MyWidget::p() {

    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 400; j++) {

            Point p = GetPixel(j, i);

            p.X -= 200;
            p.Y -= 150;

            //R
            double x = p.X * cos(alfa) - p.Y * sin(alfa);
            double y = p.X * sin(alfa) + p.Y * cos(alfa);

            p.X = x;
            p.Y = y;

            //Sc
            p.X *= Scx;
            p.Y *= Scy;

            //Sh
            x = p.Y * Shx;
            y = p.X * Shy;

            p.X += x;
            p.Y += y;

            p.X += 200;
            p.Y += 150;

            p.X += 50;
            p.Y += 100;

            p.X += Tx;
            p.Y += Ty;

            SetPixel(p);
        }
    }
}

MyWidget::MyWidget(int Width, int Height, QWidget * parent) : QWidget(parent) {

    alfa = 0;

    //Skalowanie
    Scx = 1;
    Scy = 1;

    Shx = 0;
    Shy = 0;

    setFixedSize(Width, Height);
    _imageSrc = new QImage("/home/batas2/UMK/LGM/10_przeksztalcenia/zuk.jpg");
    _imageDest = new QImage(500, 500, QImage::Format_RGB32);
    _maxDest = 500 * 500 * 4;
    _maxSrc = 400 * 300 * 4;
    _bitsSrc = _imageSrc->bits();
    _bitsDest = _imageDest->bits();
    memset(_bitsDest, 255, _maxDest);

    grpMain = new QGroupBox(this);
    grpMain->setGeometry(QRect(500, 0, 300, 500));
    grpSH = new QGroupBox(grpMain);
    grpSH->setGeometry(QRect(0, 105, 300, 110));
    grpSC = new QGroupBox(grpMain);
    grpSC->setGeometry(QRect(0, 220, 300, 110));
    grpObrot = new QGroupBox(grpMain);
    grpObrot->setGeometry(QRect(0, 25, 300, 80));
    grpTran = new QGroupBox(grpMain);
    grpTran->setGeometry(QRect(0, 340, 300, 110));

    SliderSHY = new QSlider(grpSH);
    SliderSHY->setGeometry(QRect(5, 80, 290, 23));
    SliderSHY->setRange(-100, 100);
    SliderSHY->setOrientation(Qt::Horizontal);
    SliderSHX = new QSlider(grpSH);
    SliderSHX->setGeometry(QRect(5, 40, 290, 23));
    SliderSHX->setRange(-100, 100);
    SliderSHX->setOrientation(Qt::Horizontal);
    lblSHX = new QLabel(grpSH);
    lblSHX->setGeometry(QRect(10, 25, 280, 16));
    lblSHY = new QLabel(grpSH);
    lblSHY->setGeometry(QRect(10, 65, 280, 15));

    SliderSCX = new QSlider(grpSC);
    SliderSCX->setGeometry(QRect(5, 40, 290, 23));
    SliderSCX->setRange(-100, 100);
    SliderSCX->setOrientation(Qt::Horizontal);
    SliderSCY = new QSlider(grpSC);
    SliderSCY->setGeometry(QRect(5, 80, 290, 23));
    SliderSCY->setRange(-100, 100);
    SliderSCY->setOrientation(Qt::Horizontal);
    lblSCX = new QLabel(grpSC);
    lblSCX->setGeometry(QRect(10, 25, 280, 15));
    lblSCY = new QLabel(grpSC);
    lblSCY->setGeometry(QRect(10, 65, 280, 15));

    SliderObrot = new QSlider(grpObrot);
    SliderObrot->setGeometry(QRect(5, 40, 290, 23));
    SliderObrot->setMaximum(360);
    SliderObrot->setOrientation(Qt::Horizontal);
    lblObrot = new QLabel(grpObrot);
    lblObrot->setGeometry(QRect(10, 20, 281, 16));

    SliderTranX = new QSlider(grpTran);
    SliderTranX->setGeometry(QRect(5, 40, 290, 23));
    SliderTranX->setRange(-100, 100);
    SliderTranX->setOrientation(Qt::Horizontal);
    SliderTranY = new QSlider(grpTran);
    SliderTranY->setGeometry(QRect(5, 80, 290, 23));
    SliderTranY->setRange(-100, 100);
    SliderTranY->setOrientation(Qt::Horizontal);
    lblTranX = new QLabel(grpTran);
    lblTranX->setGeometry(QRect(10, 25, 280, 15));
    lblTranY = new QLabel(grpTran);
    lblTranY->setGeometry(QRect(10, 65, 280, 15));

    grpMain->setTitle("Przeksztalcenia");
    grpSH->setTitle("SH");
    grpObrot->setTitle("Obot");
    grpSC->setTitle("SC");
    grpTran->setTitle("Transformacja");

    lblSHX->setText("X: (0 / 1)");
    lblSHY->setText("Y: (0 / 1)");

    lblSCX->setText("X: (0 / 100)");
    lblSCY->setText("Y: (0 / 100)");

    lblObrot->setText("Kat: (0 / 360)");

    lblTranX->setText("X: (0 / 100)");
    lblTranY->setText("Y: (0 / 100)");

    connect(SliderObrot, SIGNAL(sliderMoved(int)), this, SLOT(setObrotSliderValue(int)));
    connect(SliderSCX, SIGNAL(sliderMoved(int)), this, SLOT(setSCXSliderValue(int)));
    connect(SliderSCY, SIGNAL(sliderMoved(int)), this, SLOT(setSCYSliderValue(int)));
    connect(SliderSHX, SIGNAL(sliderMoved(int)), this, SLOT(setSHXSliderValue(int)));
    connect(SliderSHY, SIGNAL(sliderMoved(int)), this, SLOT(setSHYSliderValue(int)));
    connect(SliderTranX, SIGNAL(sliderMoved(int)), this, SLOT(setTranXSliderValue(int)));
    connect(SliderTranY, SIGNAL(sliderMoved(int)), this, SLOT(setTranYSliderValue(int)));

}
