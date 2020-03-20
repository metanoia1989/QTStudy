#include <QApplication>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QVariant>
#include <QDebug>
#include "fraction.h"

void createTest()
{
    static int fracType = QMetaType::type("Fraction");
    void *vp = QMetaType::construct(fracType);
//    Fraction *fp =
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    return a.exec();
}
