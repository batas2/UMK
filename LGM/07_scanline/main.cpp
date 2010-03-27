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
    int _w, _h;
    long _max;

    QImage *_image;
    uchar *_bits;

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

    Point GetPixel(int x, int y) {
        int b = this->_w * 4 * y + 4 * x;
        if (b > -1 && b < this->_max) {
            return Point(x, y, _bits[b], _bits[b + 1], _bits[b + 2]);
        }
        return Point();
    }
    void Line(int x1, int y1, int x2, int y2);
    void scanLine();
};

MyWidget::MyWidget(int Width, int Height, QWidget *parent) : QWidget(parent) {

    this->_w = Width;
    this->_h = Height;
    this->_max = this->_w * this->_h * 4;

    setFixedSize(this->_w, this->_h);
    _image = new QImage(this->_w, this->_h, QImage::Format_RGB32);
    this->_bits = _image->bits();
    memset(_image->bits(), 255, this->_max);
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

void MyWidget::paintEvent(QPaintEvent * e) {
    memset(_image->bits(), 255, this->_max);
    Line(100, 100, 150, 150);
    Line(150, 150, 200, 200);
    Line(200, 200, 400, 200);
    Line(400, 200, 350, 50);
    Line(350, 50, 300, 80);
    Line(300, 80, 250, 50);
    Line(250, 50, 200, 90);
    Line(200, 90, 100, 100);
    scanLine();
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_image);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(800, 600);
    widget.show();
    return app.exec();

}