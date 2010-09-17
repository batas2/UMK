/*
 * File:   main.cpp
 * Author: batas2, http://www.batas2.boo.pl/
 *
 * Created on 30 maj 2010, 12:27
 */

#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(_PIC_X, _PIC_Y);
    widget.show();
    return app.exec();
}

