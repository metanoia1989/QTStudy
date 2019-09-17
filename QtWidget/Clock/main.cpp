#include "dialog.h"
#include <QApplication>
#include "digiclock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Dialog w;
//    w.show();
    DigiClock clock;
    clock.show();


    return a.exec();
}
