#include "dtkmainwindow.h"

#include <DApplication>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    DTKMainWindow w;
    w.show();
    return a.exec();
}
