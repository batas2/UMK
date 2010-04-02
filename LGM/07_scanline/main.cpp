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
};

class MyWidget : public QWidget {
private:
    int _w, _h, _i;
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

    void SetPixel(int x, int y, uchar R = 0, uchar G = 0, uchar B = 0) {
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
            return Point(x, y, _bits[b], _bits[b + 1], _bits[b + 2]);
        }
        return Point();
    }

    void Square(Point &p, uchar R = 0, uchar G = 0, uchar B = 0);
    void Line(int x1, int y1, int x2, int y2);
    void scanLine();
};

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {

    _w = Width;
    _h = Height;

    _i = 0;

    _point_size = 3;
    _max = _w * _h << 2;

    setFixedSize(_w, _h);
    _image = new QImage(_w, _h, QImage::Format_RGB32);
    _bits = _image->bits();
    memset(_image->bits(), 255, _max);
}

void MyWidget::Line(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        int yMin = y1 < y2 ? y1 : y2;
        int yMax = y1 < y2 ? y2 : y1;

        for (int y = yMin; y < yMax; y++) {
            SetPixel(x1, y, 0, 0, 0);
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
                SetPixel(x, y);
            }
        }
    }
}

void MyWidget::scanLine() {
    bool x = false, y = false;
    int R = 0, G = 0, B = 0;

    for (int i = 0; i < _h; i++) {
        for (int j = 0; j < _w; j++) {

            Point p = GetPixel(j, i);

            Point l = GetPixel(j - 1, i);
            Point t = GetPixel(j, i - 1);
            Point r = GetPixel(j + 1, i);
            Point b = GetPixel(j, i + 1);



            //            if ((p.R != l.R && p.G != l.G && p.B != l.B) && (R == l.R && G == l.G && B == l.B) ) {
            //                x = !x;
            //            }
            //            if ( (p.R != t.R && p.G != t.G && p.B != t.B) && (R == t.R && G == t.G && B == t.B)) {
            //                y = !y;
            //            }
            //            if(p.R == R && p.G == G && p.B == B){
            //                x = !x;
            //            }
            if ((p.R != l.R && p.G != l.G && p.B != l.B) && (p.R == R && p.G == G && p.B == B)) {
                x = !x;
            }

            //            if ((p.R != r.R && p.G != r.G && p.B != r.B) && (p.R == R && p.G == G && p.B == B)) {
            //                x = !x;
            //            }

            if ((p.R != t.R && p.G != t.G && p.B != t.B) && (p.R == R && p.G == G && p.B == B)) {
                y = !y;
            }
            //
            //            if ((p.R != b.R && p.G != b.G && p.B != b.B) && (p.R == R && p.G == G && p.B == B)) {
            //                y = !y;
            //            }

            if (x && y) {
                SetPixel(j, i, 255, 0, 0);
            }

        }
    }
}

void MyWidget::Square(Point &p, uchar R, uchar G, uchar B) {
    for (int i = p.Y - _point_size; i <= p.Y + _point_size; i++) {
        for (int j = p.X - _point_size; j <= p.X + _point_size; j++) {
            SetPixel(j, i, R, G, B);
        }
    }
}

void MyWidget::mousePressEvent(QMouseEvent *e) {
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
            Point p(x, y);
            _points.push_back(p);
        }
    } else if (e->button() == Qt::RightButton) {
        scanLine();
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

void MyWidget::paintEvent(QPaintEvent * e) {
    memset(_image->bits(), 255, _max);

    for (_it = _points.begin(); _it < _points.end(); _it++) {
        Square(*_it, 255);
    }

    for (int i = 0; i < (int) (_points.size() - 1); i++) {
        Line(_points[i].X, _points[i].Y, _points[i + 1].X, _points[i + 1].Y);
    }

    if (_points.size() > 2) {
        Line(_points[0].X, _points[0].Y, _points[_points.size() - 1].X, _points[_points.size() - 1].Y);
    }

    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(800, 600);
    widget.show();
    return app.exec();

}