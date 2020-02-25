#include "qdicethread.h"
#include <QTime>
#include <QMutex>
#include <QWaitCondition>

QMutex mutex;
QWaitCondition newdataAvailable;

int seq = 0;	// 序号
int diceValue;

// 生产者
QThreadProducer::QThreadProducer()
{

}

// 生产者 - 停止线程
void QThreadProducer::stopThread()
{
    QMutexLocker locker(&mutex);
    m_stop = true;
}

// 生产者 - 线程任务
void QThreadProducer::run()
{
    m_stop = false; // 启动线程时令 m_stop = false
    seq = 0; // 掷骰子次数
    qsrand(QTime::currentTime().msec());	// 随机数初始化，qsrand是线程安全的

    while(!m_stop) {
        int temp = qrand(); // 获取随机数
        mutex.lock();
        diceValue = (temp % 6) + 1;
        seq++;
        mutex.unlock();

        newdataAvailable.wakeAll(); // 唤醒所有线程，有新数据了
        msleep(500);	// 线程休眠500ms
    }
}


// 消费者
QThreadConsumer::QThreadConsumer()
{

}

// 消费者 - 线程任务
void QThreadConsumer::run()
{
    m_stop = false; // 启动线程时令 m_stop = false
    while (!m_stop) {
        mutex.lock();
        newdataAvailable.wait(&mutex);	// 等待可用锁
        emit newValue(seq, diceValue);
        mutex.unlock();
    }
}

void QThreadConsumer::stopThread()
{
    QMutexLocker locker(&mutex);
    m_stop = true;
}
