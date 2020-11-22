#pragma once

#include <QObject>
#include <QThread>
#include <thread>
#include "Task.h"

class ThreadPool;

class Thread : public QObject
{
    Q_OBJECT
public:
    explicit Thread(int id = 0, ThreadPool *pool = nullptr, QObject *parent= nullptr);
    virtual ~Thread();
    virtual int id() const;
    virtual bool start();
    virtual bool stop();
    virtual bool isStarted() const;
    virtual void run();

signals:
    void threadStarted();
    void threadStoped();

private:
    QThread m_thread;
    Task m_task;
    ThreadPool *m_threadPool;
    int m_id;
};

