/*
 * File:   main.cpp
 * Author: batas2, http://www.batas2.boo.pl/
 *
 * Created on 5 maj 2010, 16:16
 */

#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(_PIC_X << 1, _PIC_Y << 1);
    widget.show();
    return app.exec();
}
