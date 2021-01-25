#include "widget.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(QString("Anzhuo"));
    QCoreApplication::setApplicationName(QString("WechatDuplicate"));

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
