#include "consumer.h"
#include "common.h"
#include <QDebug>

Consumer::Consumer(QObject *parent) : QThread(parent)
{

}

void Consumer::run()
{
    qDebug() << "消费者启动：";
    for (int i = 0; i < DataSize; ++i) {
        usedBytes.acquire();
        qDebug() << buffer[i % BufferSize];
        freeBytes.release();
    }
    qDebug() << "\n";
}
