#include "imgprocessor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont f("ZYSong 18030", 12);
    a.setFont(f);
    ImgProcessor w;
    w.show();

    return a.exec();
}
