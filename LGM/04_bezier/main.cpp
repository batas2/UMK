/*
 * File:   04_bezier.cpp
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

    void Line(Point *a, Point *b, bool v = false, uchar R = 0, uchar G = 0, uchar B = 0);
    void Square(Point &p, uchar R = 0, uchar G = 0, uchar B = 0);
    void Bezier(int i, uchar R = 0, uchar G = 0, uchar B = 0);
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

void MyWidget::Bezier(int i, uchar R, uchar G, uchar B) {
    for (double t = 0; t < 1; t += 0.001) {
        int x = _points[i].X * (1 - t)*(1 - t)*(1 - t) + 3 * _points[i + 1].X * t * (1 - t)*(1 - t) + 3 * _points[i + 2].X * t * t * (1 - t) + _points[i + 3].X * t * t*t;
        int y = _points[i].Y * (1 - t)*(1 - t)*(1 - t) + 3 * _points[i + 1].Y * t * (1 - t)*(1 - t) + 3 * _points[i + 2].Y * t * t * (1 - t) + _points[i + 3].Y * t * t*t;
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

void MyWidget::Line(Point *a, Point *b, bool v, uchar R, uchar G, uchar B) {
    if (a->X == b->X) {
        int yMin = a->Y < b->Y ? a->Y : b->Y;
        int yMax = a->Y < b->Y ? b->Y : a->Y;

        for (int y = yMin; y < yMax; y++) {
            if ((!v) || (v && ((int) (y / 10 + 0.5) % 2 == 1))) {
                SetPixel(a->X, y, R, G, B);
            }
        }
    } else {
        double A = (double) (b->Y - a->Y) / (double) (b->X - a->X);
        double B = -A * a->X + a->Y;

        if (A >= -1 && A <= 1) {
            int xMin = a->X < b->X ? a->X : b->X;
            int xMax = a->X < b->X ? b->X : a->X;

            for (int x = xMin; x < xMax; x++) {
                double y = A * x + B;
                if ((!v) || (v && ((int) (x / 10 + 0.5) % 2 == 1))) {
                    SetPixel(x, y, R, G, B);
                }
            }
        } else {
            int yMin = a->Y < b->Y ? a->Y : b->Y;
            int yMax = a->Y < b->Y ? b->Y : a->Y;

            for (int y = yMin; y < yMax; y++) {
                double x = (y - B) / A;
                if ((!v) || (v && ((int) (y / 10 + 0.5) % 2 == 1))) {
                    SetPixel(x, y, R, G, B);
                }
            }
        }
    }
}

void MyWidget::paintEvent(QPaintEvent *e) {
    memset(_image->bits(), 255, _max);

    for (_it = _points.begin(); _it < _points.end(); _it++) {
        Square(*_it, 255);
    }

    if (_points.size() > 3) {
        for (unsigned int i = 0; i < (_points.size() - 1) / 3; i++) {
            Bezier(i * 3, 0, 0, 255);
            Line(&_points[i * 3], &_points[i * 3 + 1], true, 0, 255);
            Line(&_points[i * 3 + 2], &_points[i * 3 + 3], true, 0, 255);
        }
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