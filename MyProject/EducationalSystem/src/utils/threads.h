#ifndef THREADS_H
#define THREADS_H

#include <QObject>
#include <QThread>
#include <QDebug>

#define THREAD_MAIN				0
#define THREAD_DEFAULT			1
#define THREAD_NETWORK          2
#define THREAD_DOWNLOAD         3
#define THREAD_SEARCH         4
#define THREAD_DOWNLOAD_RESOURCES         5


void QueuedThreadsInit();
void QueuedThreadsShutdown();
int QueuedGetCurrentThreadId();

struct IThreadPool;
//
struct IRunableEvents
{
    virtual void reportProgress(int pos) = 0;
    virtual void reportStatus(const QString& strStatus) = 0;
};
//
struct IRunable
{
    virtual void destroy() {
//        qDebug() << "IRunable Destroy";
        delete this; }
    virtual void run(int threadIndex, IThreadPool* pThreadPool, IRunableEvents* pEvents) = 0;
    virtual QString getTaskID() { return QString(); }
    virtual ~IRunable() {
//        qDebug() << "IRunable desstruct";
    }
};

struct IThreadPoolEvents
{
    virtual void beforeTask(IRunable* task) = 0;
    virtual void afterTask(IRunable* task) = 0;
};

struct IThreadPool
{
    virtual void addTask(IRunable* task) = 0;
    virtual void clearTasks() = 0;
    virtual IRunable* peekOne() = 0;
    virtual void shutdown(int timeout) = 0;
    virtual bool isShuttingDown() = 0;
    virtual bool isIdle() = 0;
    virtual void getTaskCount(int* pnWorking, int* pnWaiting) = 0;
    virtual void setEventsListener(IThreadPoolEvents* pEvents) = 0;
    virtual void destroy() {
        //qDebug() << "IThreadPool Destroy";
        delete this; }
    virtual ~IThreadPool() {
        //qDebug() << "IThreadPool desstruct";
    }
};

struct IDelayedThreadPool : public IThreadPool
{
    virtual void addDelayedTask(IRunable* task, int delayedSeconds) = 0;
    virtual void executeAllNow() = 0;
};

IThreadPool* CreateThreadPool(int threadCount, QThread::Priority priority = QThread::NormalPriority);
IDelayedThreadPool* CreateDelayedThreadPool(int threadCount, QThread::Priority priority = QThread::NormalPriority);


// ***********************************************************************************
template<class TFun>
class FunctionalAction
    : public IRunable
{
public:
    FunctionalAction(TFun f)
        : m_fun(f)
    {
    }
    //
    virtual void run(int threadIndex, IThreadPool* pool, IRunableEvents* pEvents)
    {
        Q_UNUSED(threadIndex);
        Q_UNUSED(pool);
        Q_UNUSED(pEvents);
        m_fun();
    }
    //
private:
    TFun m_fun;
};

template <class TFun>
inline IRunable* CreateRunable(TFun f)
{
    IRunable* action = new FunctionalAction<TFun>(f);
    return action;
}

template<class TFun>
class FunctionalActionEx
    : public IRunable
{
public:
    FunctionalActionEx(TFun f)
        : m_fun(f)
    {
    }
    //
    virtual void run(int threadIndex, IThreadPool* pool, IRunableEvents* pEvents)
    {
        m_fun(threadIndex, pool, pEvents);
    }
    //
private:
    TFun m_fun;
};

template <class TFun>
inline IRunable* CreateRunableEx(TFun f)
{
    IRunable* action = new FunctionalActionEx<TFun>(f);
    return action;
}


void QueuedThreadAddAction(int threadID, IRunable* action);
void QueuedThreadAddAction(int threadID, IRunable* action, int milliseconds, int nTimeoutThreadId, IRunable* timeoutAction);

template <class TFun>
inline void ExecuteOnThread(int threadID, TFun f)
{
    IRunable* action = new FunctionalAction<TFun>(f);
    QueuedThreadAddAction(threadID, action);
}

template <class TFun>
inline void ExecuteOnThread(int threadID, IRunable* pRunable)
{
    QueuedThreadAddAction(threadID, pRunable);
}

template <class TFun, class TFunTimeout>
void ExecuteOnThread(int threadID, TFun f, int milliseconds, int nTimeoutThreadId, TFunTimeout fTimeout)
{
    IRunable* action = new FunctionalAction<TFun>(f);
    IRunable* actionTimeout = new FunctionalAction<TFunTimeout>(fTimeout);
    QueuedThreadAddAction(threadID, action, milliseconds, nTimeoutThreadId, actionTimeout);
}



#endif // THREADS_H
