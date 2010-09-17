/* 
 * File:   MyWidget.cpp
 * Author: batas2
 * 
 * Created on 2 kwiecień 2010, 18:04
 */

#include "MyWidget.h"
#include <stdio.h>
#include <math.h>

void MyWidget::setRSliderValue(int v) {
    char buf[18];
    sprintf(buf, "R: (%d/255)", v);
    lblR->setText(buf);
    RGB(SliderR->value(), 2);
    repaint();
}

void MyWidget::setGSliderValue(int v) {
    char buf[18];
    sprintf(buf, "G: (%d/255)", v);
    lblG->setText(buf);
    RGB(SliderG->value(), 1);
    repaint();
}

void MyWidget::setBSliderValue(int v) {
    char buf[18];
    sprintf(buf, "B: (%d/255)", v);
    lblB->setText(buf);
    RGB(SliderB->value(), 0);
    repaint();
}

void MyWidget::setHSliderValue(int v) {
    char buf[18];
    sprintf(buf, "H: (%d/360)", v);
    lblH->setText(buf);
    HSV(SliderH->value(), 0);
    repaint();
}

void MyWidget::setSSliderValue(int v) {
    char buf[18];
    sprintf(buf, "S: (%d/255)", v);
    lblS->setText(buf);
    HSV(SliderS->value(), 1);
    repaint();
}

void MyWidget::setVSliderValue(int v) {
    char buf[18];
    sprintf(buf, "V: (%d/255)", v);
    lblV->setText(buf);
    HSV(SliderV->value(), 2);
    repaint();
}

void MyWidget::setCSliderValue(int v) {
    char buf[18];
    _v = SliderC->value();
    _n = 0;
    sprintf(buf, "C: (%d/255)", v);
    lblC->setText(buf);
    CMYK(SliderC->value(), SliderK->value(), 0);
    repaint();
}

void MyWidget::setMSliderValue(int v) {
    char buf[18];
    _v = SliderM->value();
    _n = 1;
    sprintf(buf, "M: (%d/255)", v);
    lblM->setText(buf);
    CMYK(SliderM->value(), SliderK->value(), 1);
    repaint();
}

void MyWidget::setYSliderValue(int v) {
    char buf[18];
    _v = SliderY->value();
    _n = 2;
    sprintf(buf, "Y: (%d/255)", v);
    lblY->setText(buf);
    CMYK(SliderY->value(), SliderK->value(), 2);
    repaint();
}

void MyWidget::setKSliderValue(int v) {
    char buf[18];
    sprintf(buf, "K: (%d/255)", v);
    lblK->setText(buf);
    CMYK(_v, SliderK->value(), _n);
    repaint();
}

void MyWidget::setLSliderValue(int v) {
    char buf[18];
    sprintf(buf, "L: (%d/255)", v);
    lblL->setText(buf);
    Lab(SliderL->value(), 0);
    repaint();
}

void MyWidget::setaSliderValue(int v) {
    char buf[18];
    sprintf(buf, "a: (%d/100)", v);
    lbla->setText(buf);
    Lab(Slidera->value(), 1);
    repaint();
}

void MyWidget::setbSliderValue(int v) {
    char buf[18];
    sprintf(buf, "b: (%d/150)", v);
    lblb->setText(buf);
    Lab(Sliderb->value(), 2);
    repaint();
}

void MyWidget::RGB(int v, int n) {

    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < 255; j++) {
            int pos = (_w * i + j) << 2;
            _bits[pos] = n == 0 ? v : i;
            _bits[pos + 1] = n == 1 ? v : j;
            _bits[pos + 2] = n == 2 ? v : j;
        }
    }
}

void MyWidget::CMYK(int v, int k, int n) {

    int R, G, B;
    QColor c;

    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < 255; j++) {
            int pos = (_w * i + j) << 2;
            n == 0 ? c.setCmyk(v, i, j, k) : n == 1 ? c.setCmyk(i, v, j, k) : c.setCmyk(i, j, v, k);
            c.getRgb(&R, &G, &B);
            _bits[pos] = B;
            _bits[pos + 1] = G;
            _bits[pos + 2] = R;
        }
    }
}

void MyWidget::HSV(int v, int n) {

    QColor c;
    int R, G, B;

    if (n == 0) {
        for (int i = 0; i < 255; i++) {
            for (int j = 0; j < 255; j++) {
                c.setHsv(v, i, j);
                c.getRgb(&R, &G, &B);
                int pos = (_w * i + j) << 2;
                _bits[pos] = B;
                _bits[pos + 1] = G;
                _bits[pos + 2] = R;
            }
        }
    } else {
        for (int i = 0; i < 360; i++) {
            for (int j = 0; j < 255; j++) {
                n == 1 ? c.setHsv(i, v, j) : c.setHsv(i, j, v);
                c.getRgb(&R, &G, &B);
                int pos = (_w * (i * 256 / 360) + j) << 2;
                _bits[pos] = B;
                _bits[pos + 1] = G;
                _bits[pos + 2] = R;
            }
        }
    }
}

void MyWidget::Lab(int v, int n) {

    int R, G, B;
    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < 255; j++) {
            int pos = (_w * i + j) << 2;
            if (n == 0) {
                Lab2RGB(v, i, j, &R, &G, &B);
            } else if (n == 1) {
                Lab2RGB(i, v, j, &R, &G, &B);
            } else {
                Lab2RGB(i, j, v, &R, &G, &B);
            }
            _bits[pos] = B;
            _bits[pos + 1] = G;
            _bits[pos + 2] = R;
        }
    }
}

double* MyWidget::MatrixXVector(const double M[3][3], double V[3]) {
    double *R = new double[3];
    for (int i = 0; i < 3; i++) {
        R[i] = 0;
        for (int j = 0; j < 3; j++) {
            R[i] += M[i][j] * V[j];
        }
    }
    return R;
}

void MyWidget::Lab2RGB(int L, int a, int b, int *R, int *G, int *B) {

    //Aktualny standart CIE
    const double epsilon = 0.008856;
    const double K = 903.3;

    //Zamierzany standart CIE
    //const double epsilon = 216 / 24389;
    //const double K = 24389 / 27;

    //Lab -> XYZ
    double Fy = (L + 16) / 116;
    double Fx = a / 500 + Fy;
    double Fz = Fy - b / 200;

    double Fx3 = Fx * Fx *Fx;
    double Fz3 = Fz * Fz *Fz;

    double xr = Fx3 > epsilon ? Fx3 : (116 * Fx - 16) / K;
    double yr = L > K * epsilon ? (L + 16 / 116)*(L + 16 / 116)*(L + 16 / 116) : L / K;
    double zr = Fz3 > epsilon ? Fz3 : (116 * Fz - 16) / K;

    double Xr = 1;
    double Yr = 1;
    double Zr = 1;

    double XYZ[3];
    XYZ[0] = xr * Xr;
    XYZ[1] = yr * Yr;
    XYZ[2] = zr * Zr;

    //XYZ -> RGB

    //CIE RGB
    const double gamma = 2.2;
    const double M[3][3] = {
        {2.3706743, -0.9000405, -0.4706338},
        {-0.5138850, 1.4253036, 0.0885814},
        {0.0052982, -0.0146949, 1.0093968}
    };

    double *rgb = MatrixXVector(M, XYZ);

    *R = pow(rgb[0], 1 / gamma);
    *G = pow(rgb[1], 1 / gamma);
    *B = pow(rgb[2], 1 / gamma);

    return;

}

void MyWidget::paintEvent(QPaintEvent * e) {
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
    memset(_bits, 255, _max);
}

MyWidget::MyWidget(int Width, int Height, QWidget * parent) : QWidget(parent) {

    _w = 255;
    _h = 255;


    setFixedSize(Width, Height);
    _image = new QImage(_w, _h, QImage::Format_RGB32);
    _max = _image->numBytes();
    _bits = _image->bits();
    memset(_bits, 255, _max);

    grpBoxRGB = new QGroupBox(this);
    grpBoxRGB->setGeometry(QRect(270, 0, 275, 175));

    grpBoxCMYK = new QGroupBox(this);
    grpBoxCMYK->setGeometry(QRect(550, 0, 275, 220));

    grpBoxHSV = new QGroupBox(this);
    grpBoxHSV->setGeometry(QRect(270, 180, 275, 175));

    grpBoxLab = new QGroupBox(this);
    grpBoxLab->setGeometry(QRect(550, 220, 275, 175));

    lblR = new QLabel(grpBoxRGB);
    lblR->setGeometry(QRect(9, 32, 120, 16));
    SliderR = new QSlider(grpBoxRGB);
    SliderR->setGeometry(QRect(10, 50, 256, 23));
    SliderR->setMaximum(255);
    SliderR->setOrientation(Qt::Horizontal);

    lblG = new QLabel(grpBoxRGB);
    lblG->setGeometry(QRect(9, 78, 120, 16));
    SliderG = new QSlider(grpBoxRGB);
    SliderG->setGeometry(QRect(9, 97, 256, 23));
    SliderG->setMaximum(255);
    SliderG->setOrientation(Qt::Horizontal);

    lblB = new QLabel(grpBoxRGB);
    lblB->setGeometry(QRect(9, 124, 120, 16));
    SliderB = new QSlider(grpBoxRGB);
    SliderB->setGeometry(QRect(9, 143, 256, 23));
    SliderB->setMaximum(255);
    SliderB->setOrientation(Qt::Horizontal);

    lblC = new QLabel(grpBoxCMYK);
    lblC->setGeometry(QRect(9, 32, 120, 16));
    SliderC = new QSlider(grpBoxCMYK);
    SliderC->setGeometry(QRect(9, 51, 256, 23));
    SliderC->setMaximum(255);
    SliderC->setOrientation(Qt::Horizontal);

    lblM = new QLabel(grpBoxCMYK);
    lblM->setGeometry(QRect(9, 78, 120, 16));
    SliderM = new QSlider(grpBoxCMYK);
    SliderM->setGeometry(QRect(9, 97, 256, 23));
    SliderM->setMaximum(255);
    SliderM->setOrientation(Qt::Horizontal);

    lblY = new QLabel(grpBoxCMYK);
    lblY->setGeometry(QRect(9, 124, 120, 16));
    SliderY = new QSlider(grpBoxCMYK);
    SliderY->setGeometry(QRect(9, 143, 256, 23));
    SliderY->setMaximum(255);
    SliderY->setOrientation(Qt::Horizontal);

    lblK = new QLabel(grpBoxCMYK);
    lblK->setGeometry(QRect(10, 170, 120, 16));
    SliderK = new QSlider(grpBoxCMYK);
    SliderK->setGeometry(QRect(10, 190, 251, 23));
    SliderK->setMaximum(255);
    SliderK->setOrientation(Qt::Horizontal);

    lblH = new QLabel(grpBoxHSV);
    lblH->setGeometry(QRect(9, 32, 120, 16));
    SliderH = new QSlider(grpBoxHSV);
    SliderH->setGeometry(QRect(9, 51, 256, 23));
    SliderH->setMaximum(360);
    SliderH->setOrientation(Qt::Horizontal);

    lblS = new QLabel(grpBoxHSV);
    lblS->setGeometry(QRect(9, 78, 120, 16));
    SliderS = new QSlider(grpBoxHSV);
    SliderS->setGeometry(QRect(9, 97, 256, 23));
    SliderS->setMaximum(255);
    SliderS->setOrientation(Qt::Horizontal);

    lblV = new QLabel(grpBoxHSV);
    lblV->setGeometry(QRect(9, 124, 120, 16));
    SliderV = new QSlider(grpBoxHSV);
    SliderV->setGeometry(QRect(9, 143, 256, 23));
    SliderV->setMaximum(255);
    SliderV->setOrientation(Qt::Horizontal);

    lblL = new QLabel(grpBoxLab);
    lblL->setGeometry(QRect(9, 32, 120, 16));
    SliderL = new QSlider(grpBoxLab);
    SliderL->setGeometry(QRect(9, 51, 256, 23));
    SliderL->setMaximum(100);
    SliderL->setOrientation(Qt::Horizontal);

    lbla = new QLabel(grpBoxLab);
    lbla->setGeometry(QRect(9, 78, 120, 16));
    Slidera = new QSlider(grpBoxLab);
    Slidera->setGeometry(QRect(9, 97, 256, 23));
    Slidera->setRange(-150, 100);
    Slidera->setOrientation(Qt::Horizontal);

    lblb = new QLabel(grpBoxLab);
    lblb->setGeometry(QRect(9, 124, 120, 16));
    Sliderb = new QSlider(grpBoxLab);
    Sliderb->setGeometry(QRect(9, 143, 256, 23));
    Sliderb->setRange(-100, 150);
    Sliderb->setOrientation(Qt::Horizontal);

    grpBoxRGB->setTitle("RGB");
    lblR->setText("R: (0/255)");
    lblG->setText("G: (0/255)");
    lblB->setText("B: (0/255)");

    grpBoxCMYK->setTitle("CMYK");
    lblC->setText("C: (0/255)");
    lblM->setText("M: (0/255)");
    lblY->setText("Y: (0/255)");
    lblK->setText("K: (0/255)");

    grpBoxHSV->setTitle("HSV");
    lblH->setText("H: (0/360)");
    lblS->setText("S: (0/255)");
    lblV->setText("V: (0/255)");

    grpBoxLab->setTitle("Lab");
    lblL->setText("L: (0/100)");
    lbla->setText("a: (0/100)");
    lblb->setText("b: (0/150)");

    connect(SliderR, SIGNAL(sliderMoved(int)), this, SLOT(setRSliderValue(int)));
    connect(SliderG, SIGNAL(sliderMoved(int)), this, SLOT(setGSliderValue(int)));
    connect(SliderB, SIGNAL(sliderMoved(int)), this, SLOT(setBSliderValue(int)));
    connect(SliderH, SIGNAL(sliderMoved(int)), this, SLOT(setHSliderValue(int)));
    connect(SliderS, SIGNAL(sliderMoved(int)), this, SLOT(setSSliderValue(int)));
    connect(SliderV, SIGNAL(sliderMoved(int)), this, SLOT(setVSliderValue(int)));
    connect(SliderC, SIGNAL(sliderMoved(int)), this, SLOT(setCSliderValue(int)));
    connect(SliderM, SIGNAL(sliderMoved(int)), this, SLOT(setMSliderValue(int)));
    connect(SliderY, SIGNAL(sliderMoved(int)), this, SLOT(setYSliderValue(int)));
    connect(SliderK, SIGNAL(sliderMoved(int)), this, SLOT(setKSliderValue(int)));
    connect(SliderL, SIGNAL(sliderMoved(int)), this, SLOT(setLSliderValue(int)));
    connect(Slidera, SIGNAL(sliderMoved(int)), this, SLOT(setaSliderValue(int)));
    connect(Sliderb, SIGNAL(sliderMoved(int)), this, SLOT(setbSliderValue(int)));

}
