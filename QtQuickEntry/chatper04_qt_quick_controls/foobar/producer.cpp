#include "producer.h"
#include "common.h"
#include <QDebug>

Producer::Producer(QObject *parent) : QThread(parent)
{

}

void Producer::run()
{
    qDebug() << "生产者启动：";
    for (int i = 0; i < DataSize; ++i) {
        freeBytes.acquire();
        buffer[i % BufferSize] = "ACGT"[(int)qrand() % 4];
        usedBytes.release();
    }
}
