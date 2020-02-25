#ifndef QDICETHREAD_H
#define QDICETHREAD_H

#include <QThread>

class QThreadProducer : public QThread
{
    Q_OBJECT
public:
    QThreadProducer();
    void stopThread();	// 结束线程

protected:
    void run() override; // 线程任务

private:
    bool m_stop = false; // 停止线程
};

class QThreadConsumer : public QThread
{
    Q_OBJECT
public:
    QThreadConsumer();
    void stopThread();	// 结束线程

protected:
    void run() override; // 线程任务

signals:
    void newValue(int seq, int diceValue);

private:
    bool m_stop = false; // 停止线程
};


#endif // QDICETHREAD_H
