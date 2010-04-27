/*
 * File:   Point.h
 * Author: batas2, http://www.batas2.boo.pl/
 *
 * Created on 7 kwiecień 2010, 13:24
 */

#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(800, 500);
    widget.show();
    return app.exec();

}
