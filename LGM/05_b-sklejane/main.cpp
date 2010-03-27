/*
 * File:   05_b_sklejane.cpp
 * Author: Bartosz Frąckowiak
 *
 * Created on 2 marzec 2010, 21:49
 */

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <vector>

using namespace std;

class Point {
public:
    int X, Y;

    Point() {
        X = 0;
        Y = 0;
    }

    Point(int X, int Y) {
        this->X = X;
        this->Y = Y;
    }
};

class MyWidget : public QWidget {
private:
    int _w, _h;

    int _i;
    long _max;

    int _point_size;

    QImage *_image;
    uchar *_bits;
    vector<Point> _points;
    vector<Point>::iterator _it;

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

public:
    MyWidget(int Width, int Height, QWidget *parent = 0);
    ~MyWidget();

    void SetPixel(int x, int y, uchar R = 0, uchar G = 0, uchar B = 0) {
        int b = _w * 4 * y + 4 * x;
        if (b > -1 && b < _max) {
            _bits[b] = B;
            _bits[b + 1] = G;
            _bits[b + 2] = R;
        }
    }

    void Square(Point &p, uchar R = 0, uchar G = 0, uchar B = 0);
    void B_Sklejane(int i, uchar R = 0, uchar G = 0, uchar B = 0);
};

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {
    _w = Width;
    _h = Height;

    _i = 0;

    _point_size = 3;
    _max = _w * _h * 4;

    setFixedSize(_w, _h);
    _image = new QImage(_w, _h, QImage::Format_RGB32);
    _bits = _image->bits();
    memset(_image->bits(), 255, _max);
}

MyWidget::~MyWidget() {
    delete _image;
}

void MyWidget::B_Sklejane(int i, uchar R, uchar G, uchar B) {

    for (double t = 0; t < 1; t += 0.001) {
        int x = ((1 - t)*(1 - t)*(1 - t) / 6) * _points[i - 2].X + ((3 * t * t * t - (6 * t * t) + 4) / 6) * _points[i - 1].X + (((-3 * t * t * t) + (3 * t * t) + (3 * t) + 1) / 6) * _points[i].X + (t * t * t / 6) * _points[i + 1].X;
        int y = ((1 - t)*(1 - t)*(1 - t) / 6) * _points[i - 2].Y + ((3 * t * t * t - (6 * t * t) + 4) / 6) * _points[i - 1].Y + (((-3 * t * t * t) + (3 * t * t) + (3 * t) + 1) / 6) * _points[i].Y + (t * t * t / 6) * _points[i + 1].Y;
        SetPixel(x, y, R, G, B);
    }
}

void MyWidget::Square(Point &p, uchar R, uchar G, uchar B) {
    for (int i = p.Y - _point_size; i <= p.Y + _point_size; i++) {
        for (int j = p.X - _point_size; j <= p.X + _point_size; j++) {
            SetPixel(j, i, R, G, B);
        }
    }
}

void MyWidget::paintEvent(QPaintEvent *e) {
    memset(_image->bits(), 255, _max);

    for (_it = _points.begin(); _it < _points.end(); _it++) {
        Square(*_it, 255);
    }

    for (int i = 2; i < (int)(_points.size() - 1); i++) {
        B_Sklejane(i, 0, 255);
    }

    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
}

void MyWidget::mousePressEvent(QMouseEvent *e) {
    int x = e->x();
    int y = e->y();
    _i = -1;

    bool b = false;
    for (_it = _points.begin(); _it < _points.end(); _it++) {
        if (    (y >= _it->Y - _point_size) && (y <= _it->Y + _point_size) &&
                (x >= _it->X - _point_size) && (x <= _it->X + _point_size)) {
            b = true;
            break;
        }
    }

    if (b) {
        _i = _it - _points.begin() + 1;
    }

    if (e->button() == Qt::LeftButton) {
        if (_i == -1) {
            Point p(x, y);
            _points.push_back(p);
        }
    } else if (e->button() == Qt::RightButton) {
        if (_i != -1) {
            _points.erase(_points.begin() + _i - 1);
        }
    }
    repaint();
}

void MyWidget::mouseMoveEvent(QMouseEvent *e) {
    if (_i != -1) {
        _points[_i - 1].X = e->x();
        _points[_i - 1].Y = e->y();
    }
    repaint();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(800, 600);
    widget.show();
    return app.exec();
}