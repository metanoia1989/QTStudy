#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(320, 240);
    w.setVisible(true);
    w.show();
    return a.exec();
}
