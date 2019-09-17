#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap("Qt.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();	// 使程序在显示启动动画的同时仍能响应鼠标等其他事件

    MainWindow w;
    w.show();

    splash.finish(&w);

    return a.exec();
}
