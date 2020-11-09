#include <QCoreApplication>
#include "DownloadManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DownloadManager manager;
    manager.execute();
    return a.exec();
}
