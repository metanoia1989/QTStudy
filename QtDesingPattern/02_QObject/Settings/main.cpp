#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("objectlerning");
    a.setOrganizationDomain("objectlearning.net");
    a.setApplicationName("mainwindow-test");

    MainWindow w;
    w.show();
    return a.exec();
}
