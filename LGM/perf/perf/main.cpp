/*
 * File:   main.cpp
 * Author: batas2, http://www.batas2.boo.pl/
 *
 * Created on 2 kwiecień 2010, 18:04
 */

//#include "MyWidget.h"
//#include "MyThread.h"

#include "MyWidget.h"

int main(int argc, char *argv[]) {
    int time = 0;
    if (argc == 2) {
        time = atoi(argv[1]);
        if (time == 0) {
            time = 30;
        }
    } else {
        time = 30;
    }

    QApplication app(argc, argv);
    MyWidget widget(500, 500, time);
    widget.show();
    return app.exec();

}
