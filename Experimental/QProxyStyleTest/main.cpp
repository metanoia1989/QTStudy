#include "widget.h"
#include "menubtnstyle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(new MenuBtnStyle);
    Widget w;
    w.show();
    return a.exec();
}
