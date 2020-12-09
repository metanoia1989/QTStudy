#include <QCoreApplication>
#include "eventthread.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    EventThread *t = new EventThread;
    t->start();
    QObject::connect(t, &EventThread::sendData,
        QThread::currentThread(), [](QString content){
        qDebug() << "接收到的数据为" << content;
    }, Qt::QueuedConnection);

    return a.exec();
}
