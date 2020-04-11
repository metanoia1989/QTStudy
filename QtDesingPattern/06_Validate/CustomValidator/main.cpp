#include "palidromeform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PalidromeForm w;
    w.show();
    return a.exec();
}
