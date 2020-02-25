#ifndef QDICETHREAD_H
#define QDICETHREAD_H

#include <QThread>
#include <QMutex>

class QDiceThread : public QThread
{
    Q_OBJECT
public:
    QDiceThread();
    void diceBegin(); // 掷一次骰子
    void dicePause();	// 暂停
    void stopThread();	// 结束线程

    bool readValue(int *seq, int *diceValue);	// 用于主线程读取数据的函数

protected:
    void run() override; // 线程任务

private:
    QMutex mutex;	// 互斥量
    int m_seq = 0; 	// 掷骰子次数序号
    int m_diceValue; // 骰子点数
    bool m_Paused = true; // 掷一次骰子
    bool m_stop = false; // 停止线程
};

#endif // QDICETHREAD_H
