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

inline int sqr(int x) {
    return x * x;
}

class MyWidget : public QWidget {
private:
    int x1, y1, x2, y2;
    int _w, _h;
    long _max;

    QImage *_image;
    uchar *_bits;

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(int x, int y, uchar R = 0, uchar G = 0, uchar B = 0) {
        int b = this->_w * 4 * y + 4 * x;
        if (b > -1 && b < this->_max) {
            this->_bits[b] = B;
            this->_bits[b + 1] = G;
            this->_bits[b + 2] = R;
        }
    }

    void Line(int x1, int y1, int x2, int y2);
    void Elipse(int x1, int y1, int x2, int y2);
};

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {
    this->x1 = 0;
    this->x2 = 0;
    this->y1 = 0;
    this->y2 = 0;

    this->_w = Width;
    this->_h = Height;

    this->_max = this->_w * this->_h * 4;

    setFixedSize(this->_w, this->_h);
    _image = new QImage(this->_w, this->_h, QImage::Format_RGB32);
    this->_bits = _image->bits();
    memset(_image->bits(), 255, this->_max);
}

void MyWidget::Elipse(int x1, int y1, int x2, int y2) {
    int a = sqr(abs(x1 - x2));
    int b = sqr(abs(y1 - y2));

    int xMax = abs(x1 - x2);
    for (int x = 0; x < xMax; x++) {
        int y = sqrt((a * b - sqr(x) * b) / a);
        this->SetPixel(x1 + x, y1 + y);
        this->SetPixel(x1 + x, y1 - y);
        this->SetPixel(x1 - x, y1 + y);
        this->SetPixel(x1 - x, y1 - y);
    }

    int yMax = abs(y1 - y2);
    for (int y = 0; y < yMax; y++) {
        int x = sqrt((a * b - sqr(y) * a) / b);
        this->SetPixel(x1 + x, y1 + y);
        this->SetPixel(x1 + x, y1 - y);
        this->SetPixel(x1 - x, y1 + y);
        this->SetPixel(x1 - x, y1 - y);
    }
}

void MyWidget::Line(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        int yMin = y1 < y2 ? y1 : y2;
        int yMax = y1 < y2 ? y2 : y1;

        for (int y = yMin; y < yMax; y++) {
            this->SetPixel(x1, y, 0, 0, 0);
        }
    } else {
        double a = (double) (y2 - y1) / (double) (x2 - x1);
        double b = -a * x1 + y1;

        if (a >= -1 && a <= 1) {
            int xMin = x1 < x2 ? x1 : x2;
            int xMax = x1 < x2 ? x2 : x1;

            for (int x = xMin; x < xMax; x++) {
                double y = a * x + b;
                this->SetPixel(x, y);
            }
        } else {
            int yMin = y1 < y2 ? y1 : y2;
            int yMax = y1 < y2 ? y2 : y1;

            for (int y = yMin; y < yMax; y++) {
                double x = (y - b) / a;
                this->SetPixel(x, y);
            }
        }
    }
}

void MyWidget::paintEvent(QPaintEvent *e) {
    this->Elipse(this->x1, this->y1, this->x2, this->y2);
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
}

void MyWidget::mousePressEvent(QMouseEvent *e) {
    this->x1 = e->x();
    this->y1 = e->y();
}

void MyWidget::mouseMoveEvent(QMouseEvent *e) {
    this->x2 = e->x();
    this->y2 = e->y();
    memset(_image->bits(), 255, this->_max);
    this->repaint();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(400, 300);
    widget.show();
    return app.exec();

}