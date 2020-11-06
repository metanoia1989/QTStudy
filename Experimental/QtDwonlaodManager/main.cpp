#include "widget.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.move(QApplication::screens().at(0)->geometry().center() - w.frameGeometry().center());
    return a.exec();
}
