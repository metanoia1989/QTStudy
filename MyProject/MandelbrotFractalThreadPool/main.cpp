#include "MandelbrotWidget.h"
#include "JobResult.h"
#include <QApplication>
#include <QList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<JobResult>();
    qRegisterMetaType<QList<JobResult>>();

    MandelbrotWidget w;
    w.show();
    return a.exec();
}
