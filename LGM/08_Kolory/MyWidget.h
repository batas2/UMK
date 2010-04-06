/* 
 * File:   MyWidget.h
 * Author: batas2
 *
 * Created on 2 kwiecień 2010, 18:04
 */

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QGroupBox>

#ifndef _MYWIDGET_H
#define	_MYWIDGET_H

class MyWidget : public QWidget {
    Q_OBJECT
private:
    int _v, _n;
    int _w, _h;

    long _max;

    QImage *_image;
    uchar *_bits;

    QGroupBox *grpBoxPreview;
    QGroupBox *grpBoxRGB;
    QGroupBox *grpBoxCMYK;
    QGroupBox *grpBoxHSV;
    QGroupBox *grpBoxLab;

    QLabel *lblR;
    QSlider *SliderR;
    QLabel *lblG;
    QSlider *SliderG;
    QLabel *lblB;
    QSlider *SliderB;

    QLabel *lblC;
    QSlider *SliderC;
    QLabel *lblM;
    QSlider *SliderM;
    QLabel *lblY;
    QSlider *SliderY;
    QLabel *lblK;
    QSlider *SliderK;

    QLabel *lblH;
    QSlider *SliderH;
    QLabel *lblS;
    QSlider *SliderS;
    QLabel *lblV;
    QSlider *SliderV;

    QLabel *lblL;
    QSlider *SliderL;
    QLabel *lbla;
    QSlider *Slidera;
    QLabel *lblb;
    QSlider *Sliderb;

    double* MatrixXVector(const double M[3][3], double V[3]);

public:
    MyWidget(int Width, int Height, QWidget *parent = 0);

    void paintEvent(QPaintEvent * e);

    void Lab2RGB(int L, int a, int b, int *R, int *G, int *B);

    void RGB(int v, int n);
    void HSV(int v, int n);
    void CMYK(int v, int k, int n);
    void Lab(int v, int n);

public slots:
    void setRSliderValue(int);
    void setGSliderValue(int);
    void setBSliderValue(int);
    void setHSliderValue(int);
    void setSSliderValue(int);
    void setVSliderValue(int);
    void setCSliderValue(int);
    void setMSliderValue(int);
    void setYSliderValue(int);
    void setKSliderValue(int);
    void setLSliderValue(int);
    void setaSliderValue(int);
    void setbSliderValue(int);
};

#endif	/* _MYWIDGET_H */

