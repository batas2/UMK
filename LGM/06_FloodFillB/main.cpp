/*
 * File:   main.cpp
 * Author: batas2
 *
 * Created on 2 marzec 2010, 21:49
 */

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <math.h>
#include <iostream>
#include <stack>

using namespace std;

class Point {
public:
    int X, Y;
    int R, G, B;

    Point() {
        this->X = 0;
        this->Y = 0;
    }

    Point(int X, int Y, int R = 0, int G = 0, int B = 0) {
        this->X = X;
        this->Y = Y;
        this->R = R;
        this->G = G;
        this->B = B;
    }
};

class MyWidget : public QWidget {
private:
    int _X, _Y;
    int _w, _h;
    long _max;

    bool _flood;

    QImage *_image;
    uchar *_bits;

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(int x, int y) {
        _image->setPixel(x, y, qRgb(255, 0, 0));
    }

    Point GetPixel(int x, int y) {
        QRgb c = _image->pixel(x, y);
        return Point(x, y, qRed(c), qGreen(c), qBlue(c));
    }

    void FloodFill(int x, int y);
};

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {

    _w = Width;
    _h = Height;

    _flood = false;

    setFixedSize(_w, _h);
    _image = new QImage(_w, _h, QImage::Format_RGB32);
    _image->load("/home/batas2/UMK/LGM/06_FloodFillB/kwiat.jpg");
    _max = _image->numBytes();

}

void MyWidget::FloodFill(int x, int y) {

    stack<Point> mystack;
    Point t[4];
    int delta = 5;

    double suma = 0;
    int n = 0;

    Point g = GetPixel(x, y);
    mystack.push(g);

    while (!mystack.empty()) {
        Point q = mystack.top();
        mystack.pop();
        SetPixel(q.X, q.Y);

        suma += (q.R + q.G + q.B) / (double) 3;
        double sr = suma / ++n;

        t[0] = GetPixel(q.X + 1, q.Y);
        t[1] = GetPixel(q.X - 1, q.Y);
        t[2] = GetPixel(q.X, q.Y - 1);
        t[3] = GetPixel(q.X, q.Y + 1);

        for (int i = 0; i < 4; i++) {
            double srA = (t[i].R + t[i].G + t[i].B) / (double) 3;
            if (srA < sr + delta && srA > sr - delta) {
                mystack.push(t[i]);
            }
        }
    }
}

void MyWidget::paintEvent(QPaintEvent * e) {
    if (_flood) {
        FloodFill(_X, _Y);
        _flood = false;
    }
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
}

void MyWidget::mousePressEvent(QMouseEvent * e) {
    _X = e->x();
    _Y = e->y();
    _flood = true;
    repaint();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(600, 500);
    widget.show();
    return app.exec();

}
