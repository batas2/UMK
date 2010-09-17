/*
 * File:   MyWidget.cpp
 * Author: batas2, http://www.batas2.boo.pl/
 *
 * Created on 2 kwiecień 2010, 18:04
 */

#include "MyWidget.h"
#include "FrameCounter.h"

double MyWidget::Inter(double a, double b, double d) {
    return b * d + a * (1 - d);
}

void MyWidget::Interpolation(double x, double y, int *R, int *G, int *B) {

    int x0, y0, x1, y1;
    double dx, dy;

    if (x > 0 && y > 0 && x < 400 && y < 300) {
        x0 = x;
        y0 = y;

        x1 = x0 + 1;
        y1 = y0 + 1;

        dx = x - x0;
        dy = y - y0;

        *R = Inter(Inter(_bitsSrc[AC[y0][x0] + 2], _bitsSrc[AC[y0][x1] + 2], dx), Inter(_bitsSrc[AC[y1][x0] + 2], _bitsSrc[AC[y1][x1] + 2], dx), dy);
        *G = Inter(Inter(_bitsSrc[AC[y0][x0] + 1], _bitsSrc[AC[y0][x1] + 1], dx), Inter(_bitsSrc[AC[y1][x0] + 1], _bitsSrc[AC[y1][x1] + 1], dx), dy);
        *B = Inter(Inter(_bitsSrc[AC[y0][x0]], _bitsSrc[AC[y0][x1]], dx), Inter(_bitsSrc[AC[y1][x0]], _bitsSrc[AC[y1][x1]], dx), dy);
    } else {
        *R = 255;
        *G = 255;
        *B = 255;
    }
}

void MyWidget::Round(double x, double y, int *R, int *G, int *B) {
    int X = (int) (x + 0.5);
    int Y = (int) (y + 0.5);
    if (x > 0 && y > 0 && x < 400 && y < 300) {
        *B = _bitsSrc[AC[Y][X]];
        *G = _bitsSrc[AC[Y][X] + 1];
        *R = _bitsSrc[AC[Y][X] + 2];
    } else {
        *R = 255;
        *G = 255;
        *B = 255;
    }
}

void MyWidget::Cut(double x, double y, int *R, int *G, int *B) {
    int X = (int) (x);
    int Y = (int) (y);
    if (x > 0 && y > 0 && x < 400 && y < 300) {
        *B = _bitsSrc[AC[Y][X]];
        *G = _bitsSrc[AC[Y][X] + 1];
        *R = _bitsSrc[AC[Y][X] + 2];
    } else {
        *R = 255;
        *G = 255;
        *B = 255;
    }
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

void MyWidget::Transform() {

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
    M_1[1][2] = -200;
    M_1[0][2] = -150;

    T_o[0][0] = 1;
    T_o[1][1] = 1;
    T_o[2][2] = 1;
    T_o[1][2] = 100;
    T_o[0][2] = 100;

    Tr[0][0] = 1;
    Tr[1][1] = 1;
    Tr[2][2] = 1;
    Tr[1][2] = -Ty;
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

    double x, y;
    int R, G, B;

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {

            x = M_1[0][0] * i + M_1[0][1] * j + M_1[0][2];
            y = M_1[1][0] * i + M_1[1][1] * j + M_1[1][2];

            (this->*func[_func_index])(x, y, &R, &G, &B);

            _bitsDest[BC[j][i]] = B;
            _bitsDest[BC[j][i] + 1] = G;
            _bitsDest[BC[j][i] + 2] = R;
        }
    }
}

void MyWidget::Start() {
    t = new MyThread();
    t->setTime(this->Time);
    t->start();
    while (!fc.Stoped()) {
        for (int i = 0; i < 360; i++) {
            alfa = alfaC[i];

            //Shx = ShxC[i];
            // Shy = ShyC[i];
            Scx = ScxC[i];
            Scy = ScyC[i];

            Transform();
            repaint();
            fc.Inc();
        }
    }
    t->halt();
}

void MyWidget::keyPressEvent(QKeyEvent * e) {
    switch (e->key()) {
        case 32:
            Start();
            break;
    }
}

MyWidget::MyWidget(int Width, int Height, int Time, QWidget * parent) : QWidget(parent) {

    alfa = 0;

    Scx = 1;
    Scy = 1;

    Shx = 0;
    Shy = 0;

    this->Time = Time;

    setFixedSize(Width, Height);
    _imageSrc = new QImage("/home/batas2/UMK/LGM/10_przeksztalcenia/zuk.jpg");
    //_imageSrc = new QImage("zuk.jpg");
    _imageDest = new QImage(500, 500, QImage::Format_RGB32);
    _maxDest = 500 * 500 * 4;
    _maxSrc = 400 * 300 * 4;
    _bitsSrc = _imageSrc->bits();
    _bitsDest = _imageDest->bits();
    memset(_bitsDest, 255, _maxDest);

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

    func[0] = &MyWidget::Cut;
    func[1] = &MyWidget::Round;
    func[2] = &MyWidget::Interpolation;
    _func_index = 0;

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            BC[i][j] = (500 * i + j) << 2;
        }
    }

    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 400; j++) {
            AC[i][j] = (400 * i + j) << 2;
        }
    }

    int z = 1;
    ShxC[0] = 0;
    ShyC[0] = 0;
    ScxC[0] = 0;
    ScyC[0] = 0;

    for (int i = 1; i < 360; i++) {
        alfaC[i] = i * 0.0174;

        if (i == 180) z = -1;
        ShxC[i] = ShxC[i - 1] + z * 0.01;
        ShyC[i] = ShyC[i - 1] + z * 0.01;
        ScxC[i] = ScxC[i - 1] + z * 0.01;
        ScyC[i] = ScyC[i - 1] + z * 0.01;
    }


}

