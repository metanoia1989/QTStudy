#include "study.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Study w;
    w.show();
    return a.exec();
}
