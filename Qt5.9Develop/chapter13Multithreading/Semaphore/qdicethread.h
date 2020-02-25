#ifndef QDICETHREAD_H
#define QDICETHREAD_H

#include <QThread>

class QThreadDAQ : public QThread
{
    Q_OBJECT
public:
    QThreadDAQ();
    void stopThread();	// 结束线程

protected:
    void run() override; // 线程任务

private:
    bool m_stop = false; // 停止线程
};

class QThreadShow : public QThread
{
    Q_OBJECT
public:
    QThreadShow();
    void stopThread();	// 结束线程

protected:
    void run() override; // 线程任务

signals:
    void newValue(int *data, int count, int seq);

private:
    bool m_stop = false; // 停止线程
};


#endif // QDICETHREAD_H
