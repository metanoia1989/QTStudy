#include "eventthread.h"
#include <QDebug>
#include <QTimer>

EventThread::EventThread()
{

}

void EventThread::run()
{
    qDebug() << "线程开始运行了！";
    emit sendData("乌拉拉，黄金黄金哦！");

    QTimer timer;
    timer.setSingleShot(true);
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, [](){
        qDebug() << "线程超时了";
    });
    timer.start();
    exec();
}
