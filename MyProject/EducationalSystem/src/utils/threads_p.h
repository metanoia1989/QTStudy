#ifndef THREADS_P_H
#define THREADS_P_H

#include <deque>
#include <QMutex>
#include "threads.h"

class QTimer;

class MainQueuedThread
    : public QObject
    , public IThreadPool
{
    Q_OBJECT
public:
    MainQueuedThread();
private:
    QMutex m_cs;
    std::deque<IRunable*> m_tasks;
    bool m_bShutingDown;
public:
    virtual void addTask(IRunable* task);
    virtual void clearTasks();
    virtual bool isIdle() { return false; }
    virtual IRunable* peekOne() { return NULL; }
    virtual void shutdown(int timeout)  { Q_UNUSED(timeout);  m_bShutingDown = true; }
    virtual bool isShuttingDown()  { return m_bShutingDown; }
    virtual void setEventsListener(IThreadPoolEvents* pEvents) { Q_UNUSED(pEvents); }
    //
    virtual void getTaskCount(int* pnWorking, int* pnWaiting);
    //
    virtual IThreadPool* getThreadPool() { return this; }
    //
    void getAllTasks(std::deque<IRunable*>& tasks);
protected slots:
    void executeAllActions();
Q_SIGNALS:
    void taskAdded();
};

class TimeoutRunable
        : public QObject
        , public IRunable

{
    Q_OBJECT
public:
    TimeoutRunable(IRunable* pAction, int milliseconds, int nTimeoutThreadId, IRunable* pTimeoutAction);
private:
    IRunable* m_pRunable;
    int m_nTimeoutThreadId;
    IRunable* m_pTimeoutRunable;
    QTimer* m_timer;
    //
    QMutex m_cs;
public:
    virtual void destroy();
    virtual void run(int threadIndex, IThreadPool* pThreadPool, IRunableEvents* pEvents);
    virtual QString getTaskID();
private:
    IRunable* beforeTimeout();
protected slots:
    void timeout();
};


#endif // THREADS_P_H
