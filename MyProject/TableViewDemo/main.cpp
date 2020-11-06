#include "delegatetableviewdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DelegateTableViewDialog w;
    w.show();
    return a.exec();
}
