#include "undomainwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UndoMainWin w;
    w.show();
    return a.exec();
}
