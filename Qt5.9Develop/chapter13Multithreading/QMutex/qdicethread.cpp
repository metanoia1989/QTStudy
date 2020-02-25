#include "qdicethread.h"
#include <QTime>

QDiceThread::QDiceThread()
{

}

// 开始掷骰子
void QDiceThread::diceBegin()
{
    m_Paused = false; // 一条语句，原子操作
}

// 暂停掷骰子
void QDiceThread::dicePause()
{
    m_Paused = true;
}

// 停止线程
void QDiceThread::stopThread()
{
    m_stop = true;
}

// 线程任务
void QDiceThread::run()
{
    m_stop = false; // 启动线程时令 m_stop = false
    m_seq = 0; // 掷骰子次数
    qsrand(QTime::currentTime().msec());	// 随机数初始化，qsrand是线程安全的

    while(!m_stop) {
        if (!m_Paused) {
            int temp = qrand(); // 获取随机数
            mutex.lock();
            m_diceValue = (temp % 6) + 1;
            m_seq++;
            mutex.unlock();
        }
        msleep(500);	// 线程休眠500ms
    }
    // 在 m_stop==true 时结束线程任务
//    quit();	// 相当于 exit(0)，退出线程的事件循环
}

bool QDiceThread::readValue(int *seq, int *diceValue)
{
    if (mutex.tryLock()) {
        *seq = m_seq;
        *diceValue = m_diceValue;
        mutex.unlock();
        return true;
    } else {
        return false;
    }
}
