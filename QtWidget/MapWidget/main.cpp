#include "mainwindow.h"
#include <QApplication>
#include <QFont>
#include "mapwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("ARRL KaitiM GB", 12);
    font.setBold(true);
    a.setFont(font);
    MapWidget mapWidget;
    mapWidget.show();

    return a.exec();
}
