#include "keysequencelabel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeySequenceLabel w;
    w.show();
    return a.exec();
}
