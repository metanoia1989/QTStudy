#include "inputform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int ibot{5}, itop{20};
    double dbot{6.50}, dtop{25.00};
    InputForm w(ibot, itop, dbot, dtop);
    w.show();
    return a.exec();
}
