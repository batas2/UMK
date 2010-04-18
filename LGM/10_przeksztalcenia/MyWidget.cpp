/*
 * File:   MyWidget.cpp
 * Author: batas2
 *
 * Created on 2 kwiecień 2010, 18:04
 */

#include "MyWidget.h"
#include <stdio.h>
#include <math.h>
#include <iostream>

void (*func[3])(double x, double y, int *X, int *Y);

void Interpolation(double x, double y, int *X, int *Y) {
    *X = x + 0.5;
    *Y = y + 0.5;
}

void Round(double x, double y, int *X, int *Y) {
    *X = x + 0.5;
    *Y = y + 0.5;
}

void Cut(double x, double y, int *X, int *Y) {
    *X = x;
    *Y = y;
}

void MyWidget::setComboValue(int v) {
    _func_index = v;
    p3();
    repaint();
}

void MyWidget::setSHXSliderValue(int) {
    Shx = SliderSHX->value() / (double) 50;
    p3();
    repaint();
}

void MyWidget::setSHYSliderValue(int) {
    Shy = SliderSHY->value() / (double) 50;
    p3();
    repaint();
}

void MyWidget::setSCXSliderValue(int) {
    Scx = SliderSCX->value() / (double) 50;
    p3();
    repaint();
}

void MyWidget::setSCYSliderValue(int) {
    Scy = SliderSCY->value() / (double) 50;
    p3();
    repaint();
}

void MyWidget::setObrotSliderValue(int) {
    alfa = SliderObrot->value() * 0.0174;
    //0,0174532925199 = Pi / 180
    p3();
    repaint();
}

void MyWidget::setTranXSliderValue(int) {
    Tx = SliderTranX->value();
    p3();
    repaint();
}

void MyWidget::setTranYSliderValue(int) {
    Ty = SliderTranY->value();
    p3();
    repaint();
}

void MyWidget::paintEvent(QPaintEvent * e) {
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_imageDest);
    memset(_bitsDest, 255, _maxDest);
}

void MyWidget::MatrixXVector(double **M, double *V) {
    double *B = new double[3];
    memcpy(B, V, sizeof (double) * 3);
    memset(V, 0, sizeof (double) * 3);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            V[i] += M[i][j] * B[j];
        }
    }
    delete []B;
}

double MyWidget::Det2x2(double **A, int i, int j) {

    int x0 = 0, x1 = 1;
    int y0 = 0, y1 = 1;

    if (i == 0) {
        x0++;
        x1++;
    } else if (i == 1) {
        x1++;
    }

    if (j == 0) {
        y0++;
        y1++;
    } else if (j == 1) {
        y1++;
    }

    return A[x0][y0] * A[x1][y1] - A[x0][y1] * A[x1][y0];
}

void MyWidget::Matrix_1(double** R) {
    double **B = new double*[3];
    for (int i = 0; i < 3; i++) {
        B[i] = new double[3];
        memcpy(B[i], R[i], sizeof (double) * 3);
    }

    double detB =
            B[0][0] * B[1][1] * B[2][2] +
            B[1][0] * B[2][1] * B[0][2] +
            B[2][0] * B[0][1] * B[1][2] -
            B[1][0] * B[0][1] * B[2][2] -
            B[0][0] * B[2][1] * B[1][2] -
            B[2][0] * B[1][1] * B[0][2];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            R[j][i] = Det2x2(B, i, j) / detB;
        }
    }
    delete []B;
}

void MyWidget::MatrixXMatix(double **A, double **R) {
    double **B = new double*[3];
    for (int i = 0; i < 3; i++) {
        B[i] = new double[3];
        memcpy(B[i], R[i], sizeof (double) * 3);
        memset(R[i], 0, sizeof (double) * 3);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    delete []B;
}

void MyWidget::p3() {

    for (int i = 0; i < 3; i++) {
        memset(M_1[i], 0, sizeof (double) * 3);
        memset(T_o[i], 0, sizeof (double) * 3);
        memset(Tr[i], 0, sizeof (double) * 3);
        memset(R[i], 0, sizeof (double) * 3);
        memset(Sc[i], 0, sizeof (double) * 3);
        memset(Sh[i], 0, sizeof (double) * 3);
    }

    M_1[0][0] = 1;
    M_1[1][1] = 1;
    M_1[2][2] = 1;
    M_1[0][2] = -150;
    M_1[1][2] = 200;

    T_o[0][0] = 1;
    T_o[1][1] = 1;
    T_o[2][2] = 1;
    T_o[1][2] = -200;
    T_o[0][2] = 150;

    Tr[0][0] = 1;
    Tr[1][1] = 1;
    Tr[2][2] = 1;
    Tr[1][2] = Ty;
    Tr[0][2] = -Tx;

    R[0][0] = cos(alfa);
    R[0][1] = -sin(alfa);
    R[1][0] = sin(alfa);
    R[1][1] = cos(alfa);
    R[2][2] = 1;

    Sc[0][0] = Scx;
    Sc[1][1] = Scy;
    Sc[2][2] = 1;

    Sh[0][0] = 1;
    Sh[1][1] = 1;
    Sh[2][2] = 1;
    Sh[0][1] = Shx;
    Sh[1][0] = Shy;

    Matrix_1(Sc);
    Matrix_1(Sh);

    MatrixXMatix(Tr, M_1);
    MatrixXMatix(R, M_1);
    MatrixXMatix(Sh, M_1);
    MatrixXMatix(Sc, M_1);
    MatrixXMatix(T_o, M_1);

    double *v = new double[3];

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {

            v[0] = i;
            v[1] = j;
            v[2] = 1;
//            std::cout << "Macierz:" << std::endl;
//            for (int a = 0; a < 3; a++) {
//                for (int b = 0; b < 3; b++) {
//                    std::cout << M_1[a][b] << "\t";
//                }
//                std::cout << std::endl;
//            }
//            std::cout << "\n";
//
//            std::cout << "wektor przed:" << std::endl;
//            for (int a = 0; a < 3; a++) {
//                std::cout << v[a] << "\t";
//            }
//            std::cout << "\n\n";
//            std::cout << "wektor po:" << std::endl;
            MatrixXVector(M_1, v);
//            for (int a = 0; a < 3; a++) {
//                std::cout << v[a] << "\t";
//            }
//            std::cout << "\n\n\n";

            int x, y;
            func[_func_index](v[0], v[1], &x, &y);
            Point p = GetPixel(x, y);

            SetPixel(i, j, p.R, p.G, p.B);
        }
    }
}

//void MyWidget::p2() {
//
//    double **To = new double*[3];
//    for (int i = 0; i < 3; i++) {
//        To[i] = new double[3];
//        memset(To[i], 0, sizeof (double) * 3);
//    }
//
//    To[0][0] = 1;
//    To[1][1] = 1;
//    To[2][2] = 1;
//    To[1][2] = 250;
//    To[0][2] = 250;
//
//    double **T_o = new double*[3];
//    for (int i = 0; i < 3; i++) {
//        T_o[i] = new double[3];
//        memset(T_o[i], 0, sizeof (double) * 3);
//    }
//
//    T_o[0][0] = 1;
//    T_o[1][1] = 1;
//    T_o[2][2] = 1;
//    T_o[1][2] = -200;
//    T_o[0][2] = -150;
//
//    double **Tr = new double*[3];
//    for (int i = 0; i < 3; i++) {
//        Tr[i] = new double[3];
//        memset(Tr[i], 0, sizeof (double) * 3);
//    }
//
//    Tr[0][0] = 1;
//    Tr[1][1] = 1;
//    Tr[2][2] = 1;
//    Tr[1][2] = Tx;
//    Tr[0][2] = Ty;
//
//    double **R = new double*[3];
//    for (int i = 0; i < 3; i++) {
//        R[i] = new double[3];
//        memset(R[i], 0, sizeof (double) * 3);
//    }
//
//    R[0][0] = cos(alfa);
//    R[0][1] = -sin(alfa);
//    R[1][0] = sin(alfa);
//    R[1][1] = cos(alfa);
//    R[2][2] = 1;
//
//    double **Sc = new double*[3];
//    for (int i = 0; i < 3; i++) {
//        Sc[i] = new double[3];
//        memset(Sc[i], 0, sizeof (double) * 3);
//    }
//
//    Sc[0][0] = Scx;
//    Sc[1][1] = Scy;
//    Sc[2][2] = 1;
//
//    double **Sh = new double*[3];
//    for (int i = 0; i < 3; i++) {
//        Sh[i] = new double[3];
//        memset(Sh[i], 0, sizeof (double) * 3);
//    }
//
//    Sh[0][0] = 1;
//    Sh[1][1] = 1;
//    Sh[2][2] = 1;
//    Sh[0][1] = Shx;
//    Sh[1][0] = Shy;
//
//    double **A;
//    A = MatrixXMatix(T_o, Sc);
//    A = MatrixXMatix(Sh, A);
//    A = MatrixXMatix(R, A);
//    A = MatrixXMatix(To, A);
//    A = MatrixXMatix(Tr, A);
//
//    double *v = new double[3];
//
//    for (int i = 0; i < 300; i++) {
//        for (int j = 0; j < 400; j++) {
//
//            Point p = GetPixel(j, i);
//
//            v[0] = p.X;
//            v[1] = p.Y;
//            v[2] = 1;
//
//            v = MatrixXVector(A, v);
//
//            p.X = v[0];
//            p.Y = v[1];
//
//            SetPixel(p);
//        }
//    }
//}
//
//void MyWidget::p() {
//
//    for (int i = 0; i < 300; i++) {
//        for (int j = 0; j < 400; j++) {
//
//            Point p = GetPixel(j, i);
//
//            p.X -= 200;
//            p.Y -= 150;
//
//            //R
//            double x = p.X * cos(alfa) - p.Y * sin(alfa);
//            double y = p.X * sin(alfa) + p.Y * cos(alfa);
//
//            p.X = x;
//            p.Y = y;
//
//            //Sc
//            p.X *= Scx;
//            p.Y *= Scy;
//
//            //Sh
//            x = p.Y * Shx;
//            y = p.X * Shy;
//
//            p.X += x;
//            p.Y += y;
//
//            p.X += 200;
//            p.Y += 150;
//
//            p.X += 50;
//            p.Y += 100;
//
//            p.X += Tx;
//            p.Y += Ty;
//
//            SetPixel(p);
//        }
//    }
//}

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
    grpMode = new QGroupBox(grpMain);
    grpMode->setGeometry(QRect(0, 440, 300, 80));

    SliderSHY = new QSlider(grpSH);
    SliderSHY->setGeometry(QRect(5, 80, 290, 23));
    SliderSHY->setRange(-200, 200);
    SliderSHY->setOrientation(Qt::Horizontal);
    SliderSHX = new QSlider(grpSH);
    SliderSHX->setGeometry(QRect(5, 40, 290, 23));
    SliderSHX->setRange(-200, 200);
    SliderSHX->setOrientation(Qt::Horizontal);
    lblSHX = new QLabel(grpSH);
    lblSHX->setGeometry(QRect(10, 25, 280, 16));
    lblSHY = new QLabel(grpSH);
    lblSHY->setGeometry(QRect(10, 65, 280, 15));

    SliderSCX = new QSlider(grpSC);
    SliderSCX->setGeometry(QRect(5, 40, 290, 23));
    SliderSCX->setRange(-200, 200);
    SliderSCX->setOrientation(Qt::Horizontal);
    SliderSCY = new QSlider(grpSC);
    SliderSCY->setGeometry(QRect(5, 80, 290, 23));
    SliderSCY->setRange(-200, 200);
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
    SliderTranX->setRange(-200, 200);
    SliderTranX->setOrientation(Qt::Horizontal);
    SliderTranY = new QSlider(grpTran);
    SliderTranY->setGeometry(QRect(5, 80, 290, 23));
    SliderTranY->setRange(-200, 200);
    SliderTranY->setOrientation(Qt::Horizontal);
    lblTranX = new QLabel(grpTran);
    lblTranX->setGeometry(QRect(10, 25, 280, 15));
    lblTranY = new QLabel(grpTran);
    lblTranY->setGeometry(QRect(10, 65, 280, 15));

    _comboBox = new QComboBox(grpMode);
    _comboBox->setGeometry(QRect(10, 25, 280, 25));
    _comboBox->insertItems(0, QStringList()
            << "Odcinanie"
            << "Zaokraglanie"
            << "Interpolacja");

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
    connect(_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setComboValue(int)));

    M_1 = new double*[3];
    T_o = new double*[3];
    Tr = new double*[3];
    R = new double*[3];
    Sc = new double*[3];
    Sh = new double*[3];

    for (int i = 0; i < 3; i++) {
        M_1[i] = new double[3];
        T_o[i] = new double[3];
        Tr[i] = new double[3];
        R[i] = new double[3];
        Sc[i] = new double[3];
        Sh[i] = new double[3];
    }

    func[0] = Cut;
    func[1] = Round;
    func[2] = Interpolation;
    _func_index = 0;

    p3();
    //    double Tab[3][3];
    //    To = Tab;
    //
    //    std::cout << Tab;
    //
    //    for (int i = 0; i < 3; i++) {
    //        std::cout << Sh[i] << std::endl;
    //        for (int j = 0; j < 3; j++) {
    //            std::cout << Tab[i][j] << "\t";
    //        }
    //        std::cout << std::endl;
    //    }
    //
    //    std::cout << "\n\n";
    //    memset(Tab, 0, sizeof (double) * 9);
    //    std::cout << sizeof (Sh);
    //    for (int i = 0; i < 3; i++) {
    //        for (int j = 0; j < 3; j++) {
    //            std::cout << Tab[i][j] << "\t";
    //        }
    //        std::cout << std::endl;
    //    }
    //    std::cout << "\n\n";

    //    double **Sh = new double*[3];
    //    for (int i = 0; i < 3; i++) {
    //        Sh[i] = new double[3];
    //        memset(Sh[i], 0, sizeof (double) * 3);
    //    }
    //    Sh[0][0] = 2;
    //    Sh[1][0] = 0;
    //    Sh[2][0] = 0;
    //
    //    Sh[0][1] = 0;
    //    Sh[1][1] = 4;
    //    Sh[2][1] = 0;
    //
    //    Sh[0][2] = 0;
    //    Sh[1][2] = 0;
    //    Sh[2][2] = 8;
    //
    //    //Sh = Matrix_1(Sh);
    //    std::cout << Det2x2(Sh, 0, 0);
    //    std::cout << std::endl;
    //
    //    for (int i = 0; i < 3; i++) {
    //        for (int j = 0; j < 3; j++) {
    //            std::cout << Sh[i][j] << "\t";
    //        }
    //        std::cout << std::endl;
    //    }

}

