#include "workthread.h"
#include <QtDebug>

WorkThread::WorkThread()
{

}

void WorkThread::run()
{
    while (true) {
        for (int n=0;n<100;n++) {
            qDebug() << n << n << n << n << n << n << n << n;
        }
    }
}
