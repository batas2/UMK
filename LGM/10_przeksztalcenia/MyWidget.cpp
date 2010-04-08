/*
 * File:   MyWidget.cpp
 * Author: batas2
 *
 * Created on 2 kwiecień 2010, 18:04
 */

#include "MyWidget.h"
#include <stdio.h>
#include <math.h>

void MyWidget::setSHXSliderValue(int) {
    Shx = SliderSHX->value() / (double) 50;
    repaint();
}

void MyWidget::setSHYSliderValue(int) {
    Shy = SliderSHY->value() / (double) 50;
    repaint();

}

void MyWidget::setSCXSliderValue(int) {
    Scx = SliderSCX->value() / (double) 50;
    repaint();

}

void MyWidget::setSCYSliderValue(int) {
    Scy = SliderSCY->value() / (double) 50;
    repaint();

}

void MyWidget::setObrotSliderValue(int) {
    alfa = SliderObrot->value();
    alfa *= M_PI / 180;
    repaint();
}

void MyWidget::setTranXSliderValue(int) {
    Tx = SliderTranX->value();
    repaint();

}

void MyWidget::setTranYSliderValue(int) {
    Ty = SliderTranY->value();
    repaint();

}

void MyWidget::paintEvent(QPaintEvent * e) {
    p();
    QPainter paint(this);
    paint.drawImage(QPoint(0, 0), *_imageDest);
    memset(_bitsDest, 255, _maxDest);
}

void MyWidget::p() {

    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 400; j++) {

            Point p = GetPixel(j, i);

            p.X -= 200;
            p.Y -= 150;

            //R
            p.X = p.X * cos(alfa) - p.Y * sin(alfa);
            p.Y = p.X * sin(alfa) + p.Y * cos(alfa);

            //Sc
            p.X *= Scx;
            p.Y *= Scy;

            //Sh
            p.X += p.Y * Shx;
            p.Y += p.X * Shy;

            p.X += 200;
            p.Y += 150;

            p.X += 50;
            p.Y += 100;

            p.X += Tx;
            p.Y += Ty;

            SetPixel(p);
        }
    }
}

MyWidget::MyWidget(int Width, int Height, QWidget * parent) : QWidget(parent) {

    alfa = 0;

    //Skalowanie
    Scx = 1;
    Scy = 1;

    Shx = 0;
    Shy = 0;

    setFixedSize(Width, Height);
    _imageSrc = new QImage("/home/batas2/UMK/LGM/10_przeksztalcenia/zuk.jpg");
    _imageDest = new QImage(500, 500, QImage::Format_RGB32);
    _maxDest = 500 * 500 * 4;
    _maxSrc = 400 * 300 * 4;
    _bitsSrc = _imageSrc->bits();
    _bitsDest = _imageDest->bits();
    memset(_bitsDest, 255, _maxDest);

    grpMain = new QGroupBox(this);
    grpMain->setGeometry(QRect(500, 0, 300, 500));
    grpSH = new QGroupBox(grpMain);
    grpSH->setGeometry(QRect(0, 105, 300, 110));
    grpSC = new QGroupBox(grpMain);
    grpSC->setGeometry(QRect(0, 220, 300, 110));
    grpObrot = new QGroupBox(grpMain);
    grpObrot->setGeometry(QRect(0, 25, 300, 80));
    grpTran = new QGroupBox(grpMain);
    grpTran->setGeometry(QRect(0, 340, 300, 110));

    SliderSHY = new QSlider(grpSH);
    SliderSHY->setGeometry(QRect(5, 80, 290, 23));
    SliderSHY->setRange(-100, 100);
    SliderSHY->setOrientation(Qt::Horizontal);
    SliderSHX = new QSlider(grpSH);
    SliderSHX->setGeometry(QRect(5, 40, 290, 23));
    SliderSHX->setRange(-100, 100);
    SliderSHX->setOrientation(Qt::Horizontal);
    lblSHX = new QLabel(grpSH);
    lblSHX->setGeometry(QRect(10, 25, 280, 16));
    lblSHY = new QLabel(grpSH);
    lblSHY->setGeometry(QRect(10, 65, 280, 15));

    SliderSCX = new QSlider(grpSC);
    SliderSCX->setGeometry(QRect(5, 40, 290, 23));
    SliderSCX->setRange(-100, 100);
    SliderSCX->setOrientation(Qt::Horizontal);
    SliderSCY = new QSlider(grpSC);
    SliderSCY->setGeometry(QRect(5, 80, 290, 23));
    SliderSCY->setRange(-100, 100);
    SliderSCY->setOrientation(Qt::Horizontal);
    lblSCX = new QLabel(grpSC);
    lblSCX->setGeometry(QRect(10, 25, 280, 15));
    lblSCY = new QLabel(grpSC);
    lblSCY->setGeometry(QRect(10, 65, 280, 15));

    SliderObrot = new QSlider(grpObrot);
    SliderObrot->setGeometry(QRect(5, 40, 290, 23));
    SliderObrot->setMaximum(360);
    SliderObrot->setOrientation(Qt::Horizontal);
    lblObrot = new QLabel(grpObrot);
    lblObrot->setGeometry(QRect(10, 20, 281, 16));

    SliderTranX = new QSlider(grpTran);
    SliderTranX->setGeometry(QRect(5, 40, 290, 23));
    SliderTranX->setRange(-100, 100);
    SliderTranX->setOrientation(Qt::Horizontal);
    SliderTranY = new QSlider(grpTran);
    SliderTranY->setGeometry(QRect(5, 80, 290, 23));
    SliderTranY->setRange(-100, 100);
    SliderTranY->setOrientation(Qt::Horizontal);
    lblTranX = new QLabel(grpTran);
    lblTranX->setGeometry(QRect(10, 25, 280, 15));
    lblTranY = new QLabel(grpTran);
    lblTranY->setGeometry(QRect(10, 65, 280, 15));

    grpMain->setTitle("Przeksztalcenia");
    grpSH->setTitle("SH");
    grpObrot->setTitle("Obot");
    grpSC->setTitle("SC");
    grpTran->setTitle("Transformacja");

    lblSHX->setText("X: (0 / 1)");
    lblSHY->setText("Y: (0 / 1)");

    lblSCX->setText("X: (0 / 100)");
    lblSCY->setText("Y: (0 / 100)");

    lblObrot->setText("Kat: (0 / 360)");

    lblTranX->setText("X: (0 / 100)");
    lblTranY->setText("Y: (0 / 100)");

    connect(SliderObrot, SIGNAL(sliderMoved(int)), this, SLOT(setObrotSliderValue(int)));
    connect(SliderSCX, SIGNAL(sliderMoved(int)), this, SLOT(setSCXSliderValue(int)));
    connect(SliderSCY, SIGNAL(sliderMoved(int)), this, SLOT(setSCYSliderValue(int)));
    connect(SliderSHX, SIGNAL(sliderMoved(int)), this, SLOT(setSHXSliderValue(int)));
    connect(SliderSHY, SIGNAL(sliderMoved(int)), this, SLOT(setSHYSliderValue(int)));
    connect(SliderTranX, SIGNAL(sliderMoved(int)), this, SLOT(setTranXSliderValue(int)));
    connect(SliderTranY, SIGNAL(sliderMoved(int)), this, SLOT(setTranYSliderValue(int)));

}
