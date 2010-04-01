/*
 * File:   main.cpp
 * Author: batas2
 *
 * Created on 1 kwiecień 2010, 18:17
 */

#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(400, 350);
    widget.show();
    return app.exec();
}
