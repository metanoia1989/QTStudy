#include <QCoreApplication>
#include <QDebug>
#include <QSemaphore>
#include "producer.h"
#include "consumer.h"
#include "myConstants.h"

char buffer[BufferSize];

QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Producer producer;
    Consumer consumer1;
    Consumer consumer2;
    qDebug() << "开始测试：";
    producer.start();
    consumer1.start();
    consumer2.start();
    qDebug() << "线程启动完毕：";

    producer.wait();
    consumer1.wait();
    consumer2.wait();
    return app.exec();
}
