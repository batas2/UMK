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
#include <QColor>
#include <QKeyEvent>
#include <iostream>

using namespace std;

class MyWidget : public QWidget {
private:
    int _R, _G, _B;
    int _S, _V, _H;

    int _w, _h;

    long _max;

    QImage *_image;
    uchar *_bits;

public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void paintEvent(QPaintEvent *e);

    void RGB(int v, int n);
    void HSV(int v, int n);

    void keyPressEvent(QKeyEvent * e);


};

void MyWidget::RGB(int v, int n) {

    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < 255; j++) {
            _bits[_w * 4 * i + 4 * j] = n == 0 ? v : i;
            _bits[_w * 4 * i + 4 * j + 1] = n == 1 ? v : j;
            _bits[_w * 4 * i + 4 * j + 2] = n == 2 ? v : j;
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
                _bits[_w * 4 * i + 4 * j] = B;
                _bits[_w * 4 * i + 4 * j + 1] = G;
                _bits[_w * 4 * i + 4 * j + 2] = R;
            }
        }
    } else {
        for (int i = 0; i < 360; i++) {
            for (int j = 0; j < 255; j++) {
                n == 1 ? c.setHsv(i, v, j) : c.setHsv(i, j, v);
                c.getRgb(&R, &G, &B);
                _bits[(int) (_w * 4 * (i * 256 / 360) + 4 * j + 0.5)] = B;
                _bits[(int) (_w * 4 * (i * 256 / 360) + 4 * j + 0.5) + 1] = G;
                _bits[(int) (_w * 4 * (i * 256 / 360) + 4 * j + 0.5) + 2] = R;
            }
        }
    }
}

void MyWidget::paintEvent(QPaintEvent *e) {
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
    memset(_bits, 255, _max);
}

void MyWidget::keyPressEvent(QKeyEvent * e) {
    cout << _R << " " << _G << " " << _B << endl;
    cout << _H << " " << _S << " " << _V << endl;

    cout << e->key() << endl;
    switch (e->key()) {
            /* - - - RGB - - -*/
        case 81: //Q
            _R++;
            if (_R > 255) _R = 0;
            RGB(_R, 2);
            repaint();
            break;
        case 65: //A
            _G++;
            if (_G > 255) _G = 0;
            RGB(_G, 1);
            repaint();
            break;
        case 90: //Z
            _B++;
            if (_B > 255) _B = 0;
            RGB(_B, 0);
            repaint();
            break;
            /* - - - HSV - - -*/
        case 87: //W
            _H += 1;
            if (_H > 360) _H = 0;
            HSV(_H, 0);
            repaint();
            break;
        case 83: //S
            _S++;
            if (_S > 255) _S = 0;
            HSV(_S, 1);
            repaint();
            break;
        case 88: //X
            _V++;
            if (_V > 255) _V = 0;
            HSV(_V, 2);
            repaint();
            break;
    }
}

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {

    _R = 0;
    _G = 0;
    _B = 0;
    _H = 0;
    _S = 0;
    _V = 0;

    _w = Width;
    _h = Height;


    setFixedSize(Width, Height);
    _image = new QImage(_w, _h, QImage::Format_RGB32);
    _max = _image->numBytes();
    _bits = _image->bits();
    memset(_bits, 255, _max);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(400, 400);
    widget.show();
    return app.exec();

}
