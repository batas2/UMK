
#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyWidget widget(830, 400);
    widget.show();
    return app.exec();

}
