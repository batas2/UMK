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
#include <vector>
#include <iostream>
using namespace std;

class Point {
public:
    int X, Y;
    int R, G, B;

    Point() {
        X = 0;
        Y = 0;
    }

    Point(int X, int Y, int R = 0, int G = 0, int B = 0) {
        this->X = X;
        this->Y = Y;
        this->R = R;
        this->G = G;
        this->B = B;
    }

    int GetColor() {
        return (B << 16) + (G << 8) + R;
    }
};

class MyWidget : public QWidget {
private:
    int _XMin, _XMax, _YMin, _YMax;
    int _w, _h, _i;
    long _max;

    bool _scan;

    int _point_size;

    QImage *_image;
    uchar *_bits;

    vector<Point> _points;
    vector<Point>::iterator _it;

    Point p;
    int tab[800][600];
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    int det(Point a, Point b, Point c);
    void fill(Point a, Point b, Point c);
public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void SetPixel(int x, int y, uchar R = 255, uchar G = 255, uchar B = 255) {
        int b = (_w * y + x) << 2;
        if (b > -1 && b < _max) {
            _bits[b] = B;
            _bits[b + 1] = G;
            _bits[b + 2] = R;
        }
    }

    Point GetPixel(int x, int y) {
        int b = (_w * y + x) << 2;
        if (b > -1 && b < _max) {
            return Point(x, y, _bits[b + 2], _bits[b + 1], _bits[b]);
        }
        return Point();
    }

    void Line(int x1, int y1, int x2, int y2, int R = 255, int G = 255, int B = 255);
    void scanLine();
};

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {

    _XMax = 0;
    _YMax = 0;
    _XMin = Width;
    _YMin = Height;

    _w = Width;
    _h = Height;

    _i = 0;
    _scan = false;

    _point_size = 3;
    _max = _w * _h << 2;

    setFixedSize(_w, _h);
    _image = new QImage(_w, _h, QImage::Format_RGB32);
    _bits = _image->bits();
    memset(_image->bits(), 0, _max);
}

void MyWidget::Line(int x1, int y1, int x2, int y2, int R, int G, int B) {
    if (x1 == x2) {
        int yMin = y1 < y2 ? y1 : y2;
        int yMax = y1 < y2 ? y2 : y1;

        for (int y = yMin; y < yMax; y++) {
            SetPixel(x1, y, R, G, B);
        }
    } else {
        double a = (double) (y2 - y1) / (double) (x2 - x1);
        double b = -a * x1 + y1;

        if (a >= -1 && a <= 1) {
            int xMin = x1 < x2 ? x1 : x2;
            int xMax = x1 < x2 ? x2 : x1;

            for (int x = xMin; x < xMax; x++) {
                double y = a * x + b;
                SetPixel(x, y);
            }
        } else {
            int yMin = y1 < y2 ? y1 : y2;
            int yMax = y1 < y2 ? y2 : y1;

            for (int y = yMin; y < yMax; y++) {
                double x = (y - b) / a;
                SetPixel(x, y, R, G, B);
            }
        }
    }
}

int MyWidget::det(Point a, Point b, Point c) {
    return a.Y * (c.X - b.X) + b.Y * (a.X - c.X) + c.Y * (b.X - a.X);
}

void MyWidget::fill(Point a, Point b, Point c) {

    double fA = (b.Y - a.Y) / (double) (b.X - a.X);
    double fB = -fA * a.X + a.Y;

    int kX = 1, kY = 1;
    if (det(a, b, c) < 0) {
        kX = c.X - b.X >= 0 ? 2 : -2;
        kY = c.Y - b.Y >= 0 ? 2 : -2;
    } else {
        kX = (p.Y - fB) / fA >= p.X ? kX = -2 : kX = 2;
        kY = fA * p.X + fB >= p.Y ? kY = -2 : kY = 2;
    }

    Point border;
    border.R = 255;
    border.G = 255;
    border.B = 255;


    if (fA >= -1 && fA <= 1) {
        int xMin = a.X < b.X ? a.X : b.X;
        int xMax = a.X < b.X ? b.X : a.X;

        double y = fA * xMin + fB;
        for (int x = xMin; x < xMax; x++) {
            y += fA;

            Point s = GetPixel(x + kX, y + kY);
            while (s.GetColor() != border.GetColor() && s.Y < _YMax && s.Y > _YMin) {
                tab[s.X][s.Y]++;
                kY > 0 ? s.Y++ : s.Y--;
                s = GetPixel(s.X, s.Y);
            }
        }
    } else {
        int yMin = a.Y < b.Y ? a.Y : b.Y;
        int yMax = a.Y < b.Y ? b.Y : a.Y;

        double x = (yMin - fB) / fA;
        double fA1 = 1 / fA;
        for (int y = yMin; y < yMax; y++) {
            x += fA1;
            Point s = GetPixel(x + kX, y + kY);
            while (s.GetColor() != border.GetColor() && s.X < _XMax && s.X > _XMin) {
                tab[s.X][s.Y]++;
                kX > 0 ? s.X++ : s.X--;
                s = GetPixel(s.X, s.Y);
            }
        }
    }

}

//void MyWidget::scanLine() {
//
//    for (int i = 0; i < _w; i++) {
//        for (int j = 0; j < _h; j++) {
//            tab[i][j] = 0;
//        }
//    }
//    for (int i = 1; i < _points.size() - 1; i++) {
//        fill(_points.at(i - 1), _points.at(i), _points.at(i + 1));
//    }
//    fill(_points.at(_points.size() - 2), _points.at(_points.size() - 1), _points.at(0));
//    fill(_points.at(_points.size() - 1), _points.at(0), _points.at(1));
//
//    for (int i = 0; i < _w; i++) {
//        for (int j = 0; j < _h; j++) {
//            if (tab[i][j] > 1) {
//                SetPixel(i, j, 255, 0, 0);
//            }
//        }
//    }
//}

void MyWidget::scanLine() {
    Point border;
    border.R = 255;
    border.G = 255;
    border.B = 255;

    for (int i = 0; i < _w; i++) {
        for (int j = 0; j < _h; j++) {
            tab[i][j] = 0;
        }
    }
    for (int y = _YMin; y < _YMax; y++) {
        bool in = false;
        for (int x = _XMin; x < _XMax; x++) {

            Point l = GetPixel(x - 1, y);
            Point ll = GetPixel(x + 1, y);
            Point r = GetPixel(x, y);

            if ((l.GetColor() == border.GetColor() && r.GetColor() != border.GetColor()) && !(l.GetColor() != border.GetColor() && r.GetColor() == border.GetColor() && l.GetColor() != border.GetColor())) {
                in = !in;
            }
            if (in) {
                tab[x - 1][y]++;
            }
        }
    }

    for (int x = _XMin; x < _XMax; x++) {
        bool in = false;
        for (int y = _YMin; y < _YMax; y++) {

            Point l = GetPixel(x, y - 1);
            Point ll = GetPixel(x, y + 1);
            Point r = GetPixel(x, y);

            if ((l.GetColor() == border.GetColor() && r.GetColor() != border.GetColor()) && !(l.GetColor() != border.GetColor() && r.GetColor() == border.GetColor() && l.GetColor() != border.GetColor())) {
                in = !in;
            }
            if (in) {
                tab[x][y - 1]++;
            }
        }
    }
    for (int i = 0; i < _w; i++) {
        for (int j = 0; j < _h; j++) {
            if (tab[i][j] > 1) {
                SetPixel(i, j, 255, 0, 0);
            }
        }
    }
}

void MyWidget::mousePressEvent(QMouseEvent * e) {
    int x = e->x();
    int y = e->y();
    _i = -1;

    bool b = false;
    for (_it = _points.begin(); _it < _points.end(); _it++) {
        if ((y >= _it->Y - _point_size) && (y <= _it->Y + _point_size) &&
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
            if (x > _XMax) _XMax = x;
            if (x < _XMin) _XMin = x;
            if (y > _YMax) _YMax = y;
            if (y < _YMin) _YMin = y;
            Point p(x, y);
            _points.push_back(p);
        }
    } else if (e->button() == Qt::RightButton) {
        _scan = true;
        p.X = x;
        p.Y = y;
        scanLine();
    }
    repaint();
}

void MyWidget::mouseMoveEvent(QMouseEvent * e) {
    if (_i != -1) {
        _points[_i - 1].X = e->x();
        _points[_i - 1].Y = e->y();
    }
    repaint();
}

void MyWidget::paintEvent(QPaintEvent * e) {
    if (!_scan) {
        memset(_image->bits(), 0, _max);

        for (int i = 0; i < (int) (_points.size() - 1); i++) {
            Line(_points[i].X, _points[i].Y, _points[i + 1].X, _points[i + 1].Y);
        }

        if (_points.size() > 2) {
            Line(_points[0].X, _points[0].Y, _points[_points.size() - 1].X, _points[_points.size() - 1].Y);
        }
    }
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
    e->accept();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(800, 600);
    widget.show();
    return app.exec();

}