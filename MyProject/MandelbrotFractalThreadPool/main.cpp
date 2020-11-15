#include "MandelbrotWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MandelbrotWidget w;
    w.show();
    return a.exec();
}
