#include "lifemainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LifeMainWindow w;
    w.show();
    return a.exec();
}
