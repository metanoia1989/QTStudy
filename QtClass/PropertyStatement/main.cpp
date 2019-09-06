#include "widget.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    // 属性读写
    // 通过写函数、读函数
    w.setNickName("Wid");
    qDebug() << w.nickName();
    w.setCount(100);
    qDebug() << w.count();

    // 通过 setProperty() 函数 和 property() 函数
    w.setProperty("value", 2.3456);
    qDebug() << w.property("value").toDouble();

    w.show();

    return a.exec();
}
