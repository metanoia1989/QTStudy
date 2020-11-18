#pragma once
#include <QThread>

class ThreadPool;

class WorkThread : public QThread
{
public:
    WorkThread(ThreadPool *parent);
    ~WorkThread();

protected:
    virtual void run() override;

private:
    ThreadPool *m_Pool;
    Qt::HANDLE m_Handle;
};

