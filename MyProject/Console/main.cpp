#include "widget.h"

#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font = a.font();
    font.setFamily("微软雅黑");
    a.setFont(font);
    Widget w;
    w.show();
    return a.exec();
}
