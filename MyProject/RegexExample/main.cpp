#include "regexpdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("微软雅黑", 9));
    RegExpDialog w;
    w.show();
    return a.exec();
}
