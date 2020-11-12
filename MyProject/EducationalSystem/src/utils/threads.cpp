#include "Threads.h"
#include "Threads_p.h"

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDateTime>
#include <QTimer>

#include <deque>
#include <vector>
#include <map>

class CTaskWorkThread;
class CThreadPool;

typedef CTaskWorkThread* CreateThreadFunction(CThreadPool* pool, int threadIndex, QThread::Priority priority);


class CThreadPool : public IDelayedThreadPool
{
public:
    CThreadPool(int poolCount, CreateThreadFunction* createThreadFun, QThread::Priority priority);
    ~CThreadPool();
protected:
    std::deque<CTaskWorkThread*> m_threads;
    std::deque<IRunable*> m_tasks;

    QMutex m_cs;
    QMutex m_csEvent;
    QWaitCondition m_event;
    bool m_bShuttingDown;
    IThreadPoolEvents* m_pEvents;
public:
    virtual void addTask(IRunable* task);
    virtual void clearTasks();
    virtual IRunable* peekOne();    //execute on worker
    //
    virtual bool isShuttingDown();
    virtual void shutdown(int timeout);
    virtual bool isIdle();
    virtual void setEventsListener(IThreadPoolEvents* pEvents);
    virtual void getTaskCount(int* pnWorking, int* pnWaiting);
    //
    virtual void addDelayedTask(IRunable* task, int delayedSeconds) { Q_UNUSED(task); Q_UNUSED(delayedSeconds); }
    virtual void executeAllNow() {}
public:
    void beforeTask(IRunable* task);
    void afterTask(IRunable* task);
protected:
    int GetWorkingTaskCount();
    int GetWaitingTaskCount();
};


class CTaskWorkThread : public QThread
{
public:
    CTaskWorkThread(CThreadPool* pool, int threadIndex)
        : m_pool(pool)
        , m_nThreadIndex(threadIndex)
        , n_bWorking(false)
    {
    }
    virtual ~CTaskWorkThread()
    {
//        qDebug() << "CTaskWorkThread destruct";
    }
protected:
    CThreadPool* m_pool;
    int m_nThreadIndex;
    bool n_bWorking;
protected:
    virtual void run()
    {
        while (!m_pool->isShuttingDown())
        {            
            //
            IRunable* task = m_pool->peekOne();
            if (task)
            {
                m_pool->beforeTask(task);
                n_bWorking = true;
                task->run(m_nThreadIndex, m_pool, NULL);
                n_bWorking = false;
                m_pool->afterTask(task);
                task->destroy();
            }
        }
    }
    //
public:
    virtual IThreadPool* getThreadPool()
    {
        return m_pool;
    }
    //
    virtual bool IsAlive()
    {
        return isRunning();
    }
    //
    virtual bool IsWorking()
    {
        return n_bWorking;
    }
public:
    static CTaskWorkThread* Create(CThreadPool* pool, int threadIndex, QThread::Priority priority)
    {
        CTaskWorkThread* thread = new CTaskWorkThread(pool, threadIndex);
        thread->start(priority);
        return thread;
    }
};

CThreadPool::CThreadPool(int poolCount, CreateThreadFunction* createThreadFun, QThread::Priority priority)
    : m_cs(QMutex::Recursive)
    , m_csEvent(QMutex::NonRecursive)
    , m_bShuttingDown(false)
    , m_pEvents(NULL)
{
    //
    for (int i = 0; i < poolCount; i++)
    {
        CTaskWorkThread* thread = createThreadFun(this, i, priority);
        m_threads.push_back(thread);
    }
}

CThreadPool::~CThreadPool()
{
    //qDebug() << "CThreadPool destruct , threads : " << m_threads.size();
    for (CTaskWorkThread* thread : m_threads)
    {
        QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->quit();
    }
    m_threads.clear();
}
//
void CThreadPool::addTask(IRunable* task)
{
    QMutexLocker lock(&m_cs);
    //
    QString strTaskId = task->getTaskID();
    if (!strTaskId.isEmpty())
    {
        //remove exists tasks
        intptr_t count = m_tasks.size();
        for (intptr_t i = count - 1; i >= 0; i--)
        {
            IRunable* t = m_tasks[i];
            if (t->getTaskID() == strTaskId)
            {
                m_tasks.erase(m_tasks.begin() + i);
            }
        }
    }
    //
    m_tasks.push_back(task);
    //
    lock.unlock();
    //
    QMutexLocker lockEvent(&m_csEvent);
    m_event.wakeAll();
}

void CThreadPool::clearTasks()
{
    QMutexLocker lock(&m_cs);
    //
    m_tasks.clear();
}

IRunable* CThreadPool::peekOne()    //execute on worker
{
    if (m_bShuttingDown)
        return nullptr;
    //
    IRunable* task = nullptr;
    //
    //
    //
    {
        QMutexLocker lock(&m_cs);
        if (m_bShuttingDown)
            return nullptr;
        //
        if (!m_tasks.empty())
        {
            task = *m_tasks.begin();
            m_tasks.pop_front();
        }
    }

    //
    if (task)
        return task;
    //
    {
        QMutexLocker locker(&m_csEvent);
        m_event.wait(&m_csEvent);
        //
        if (m_bShuttingDown)
            return nullptr;
    }
    //
    //
    {
        QMutexLocker lock(&m_cs);
        //
        if (!m_tasks.empty())
        {
            task = *m_tasks.begin();
            m_tasks.pop_front();
        }
        //
    }
    //
    return task;
}
//
bool CThreadPool::isShuttingDown()
{
    return m_bShuttingDown;
}
//
void CThreadPool::shutdown(int timeout)
{
    m_bShuttingDown = true;
    //
    //
    {
        QMutexLocker lock(&m_csEvent);
        m_event.wakeAll();
    }
    //
    //
    Q_UNUSED(timeout);
    //while ((int)GetTickCount() - start >= timeout)
    while (true)
    {
        int count = (int)m_threads.size();
        for (int i = count - 1; i >= 0; i--)
        {
            CTaskWorkThread* thread = m_threads[i];
            //
            if (!thread->IsAlive())
            {
                m_threads.erase(m_threads.begin() + i);
                thread->deleteLater();
            }
            else
            {
                thread->quit();
            }
        }
        //

        if (m_threads.empty())
        {
            delete this;
            return;
        }
        //
        //ProcessMessages();
#ifdef Q_OS_LINUX
        class WaitThread : public QThread
        {
         public :
             static void sleep(long iSleepTime)
             {
                  QThread::sleep(iSleepTime);
             }
             static void msleep(long iSleepTime)
             {
                  QThread::msleep(iSleepTime);
             }
        };
        WaitThread::msleep(100);
#else
        QThread::msleep(100);
#endif
    }
}
//
void CThreadPool::getTaskCount(int* pnWorking, int* pnWaiting)
{
    if (pnWorking)
    {
        *pnWorking = GetWorkingTaskCount();
    }
    if (pnWaiting)
    {
        *pnWaiting = GetWaitingTaskCount();
    }
}
//
int CThreadPool::GetWorkingTaskCount()
{
    int count = 0;
    //
    for (auto it = m_threads.begin(); it != m_threads.end(); it++)
    {
        CTaskWorkThread* thread = *it;
        if (thread->IsWorking())
        {
            count++;
        }
    }
    //
    return count;
}
//
bool CThreadPool::isIdle()
{
    if (GetWaitingTaskCount() > 0)
        return false;
    //
    for (auto it = m_threads.begin(); it != m_threads.end(); it++)
    {
        CTaskWorkThread* thread = *it;
        if (thread->IsWorking())
        {
            return false;
        }
    }
    return true;
}
void CThreadPool::setEventsListener(IThreadPoolEvents* pEvents)
{
    m_pEvents = pEvents;
}


//
int CThreadPool::GetWaitingTaskCount()
{
    QMutexLocker locker(&m_cs);
    int count = (int)m_tasks.size();
    //
    return count;
}

void CThreadPool::beforeTask(IRunable* task)
{
    if (!m_pEvents)
        return;
    m_pEvents->beforeTask(task);
}
void CThreadPool::afterTask(IRunable* task)
{
    if (!m_pEvents)
        return;
    m_pEvents->afterTask(task);
}



IThreadPool* CreateThreadPool(int threadCount, QThread::Priority priority)
{
    CThreadPool* pool = new CThreadPool(threadCount, CTaskWorkThread::Create, priority);
    return pool;
}

///////////////////////////////////////////////////////////////////////////////////

class CDelayedWorkThread : public CTaskWorkThread
{
public:
    CDelayedWorkThread(CThreadPool* pool, int threadIndex)
        : CTaskWorkThread(pool, threadIndex)
    {
    }
protected:
    virtual void run()
    {
        while (1)
        {
            if (m_pool->isShuttingDown())
                return;
            //
            IRunable* task = m_pool->peekOne();
            if (task)
            {
                m_pool->beforeTask(task);
                n_bWorking = true;
                task->run(m_nThreadIndex, m_pool, NULL);
                n_bWorking = false;
                m_pool->afterTask(task);
                task->destroy();
            }
            else
            {
                QThread::sleep(1);
            }
        }
    }
public:
    static CTaskWorkThread* Create(CThreadPool* pool, int threadIndex, QThread::Priority priority)
    {
        CDelayedWorkThread* thread = new CDelayedWorkThread(pool, threadIndex);
        thread->start(priority);
        return thread;
    }
};


class CDelayedThreadPool : public CThreadPool
{
public:
    CDelayedThreadPool(int poolCount, CreateThreadFunction* createThreadFunction, QThread::Priority priority)
        : CThreadPool(poolCount, createThreadFunction, priority)
    {
    }
protected:
    std::map<IRunable*, QDateTime> m_mapTasksTime;
public:
    //
    virtual void addTask(IRunable* task)
    {
        addDelayedTask(task, 0);
    }
    //
    virtual void addDelayedTask(IRunable* task, int delayedSeconds)
    {
        CThreadPool::addTask(task);
        //
        QMutexLocker lock(&m_cs);
        //
        QDateTime now = QDateTime::currentDateTime();
        QDateTime work = now.addSecs(delayedSeconds);
        //
        m_mapTasksTime[task] = work;
    }
    virtual void executeAllNow()
    {
        QMutexLocker lock(&m_cs);
        //
        m_mapTasksTime.clear();
        QDateTime now = QDateTime::currentDateTime();
        //
        for (auto it = m_tasks.begin();
            it != m_tasks.end();
            it++)
        {
            m_mapTasksTime[*it] = now;
        }
    }
    //
    virtual IRunable* peekOne()    //execute on worker
    {
        if (m_bShuttingDown)
            return nullptr;
        //
        QDateTime now = QDateTime::currentDateTime();
        //
        QMutexLocker lock(&m_cs);

        if (m_bShuttingDown)
            return nullptr;

        //
        if (m_tasks.empty())
            return nullptr;
        //
        size_t count = m_tasks.size();
        for (size_t i = 0; i < count; i++)
        {
            IRunable* task = m_tasks[i];
            //
            QDateTime t = m_mapTasksTime[task];
            //
            if (now >= t)
            {
                m_tasks.erase(m_tasks.begin() + i);
                return task;
            }
        }
        //
        return nullptr;
    }
};

IDelayedThreadPool* CreateDelayedThreadPool(int threadCount, QThread::Priority priority)
{
    CDelayedThreadPool* pool = new CDelayedThreadPool(threadCount, CDelayedWorkThread::Create, priority);
    return pool;
}
///////////////////////////////////////////////////////////////////////////////////

MainQueuedThread::MainQueuedThread()
    : m_bShutingDown(false)
{
    connect(this, SIGNAL(taskAdded()), this, SLOT(executeAllActions()), Qt::QueuedConnection);
}
void MainQueuedThread::addTask(IRunable* task)
{
    //
    {
        QMutexLocker lock(&m_cs);
        m_tasks.push_back(task);
    }
    //
    emit taskAdded();
}
//
void MainQueuedThread::clearTasks()
{
    QMutexLocker lock(&m_cs);
    m_tasks.clear();
}

//
void MainQueuedThread::getTaskCount(int* pnWorking, int* pnWaiting)
{
    QMutexLocker lock(&m_cs);
    //
    if (pnWaiting)
    {
        *pnWaiting = (int)m_tasks.size();
    }
    //
    if (pnWorking)
    {
        *pnWorking = 1;
    }
}
//
void MainQueuedThread::getAllTasks(std::deque<IRunable*>& tasks)
{
    QMutexLocker lock(&m_cs);
    tasks = m_tasks;
    m_tasks.clear();
}
void MainQueuedThread::executeAllActions()
{
    std::deque<IRunable*> tasks;
    getAllTasks(tasks);
    //
    for (auto it = tasks.begin();
        it != tasks.end();
        it++)
    {
        if (isShuttingDown())
            return;
        IRunable* pRunable = *it;
        pRunable->run(THREAD_MAIN, this, NULL);
        pRunable->destroy();

    }
}


TimeoutRunable::TimeoutRunable(IRunable* pAction, int milliseconds, int nTimeoutThreadId, IRunable* pTimeoutAction)
    : m_pRunable(pAction)
    , m_nTimeoutThreadId(nTimeoutThreadId)
    , m_pTimeoutRunable(pTimeoutAction)
{
    m_timer = new QTimer(NULL);
    m_timer->setSingleShot(true);
    m_timer->setInterval(milliseconds);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
}
void TimeoutRunable::destroy()
{
    m_pRunable->destroy();
    delete this;
}
void TimeoutRunable::run(int threadIndex, IThreadPool* pThreadPool, IRunableEvents* pEvents)
{
    m_pRunable->run(threadIndex, pThreadPool, pEvents);
}
QString TimeoutRunable::getTaskID()
{
    return m_pRunable->getTaskID();
}


IRunable* TimeoutRunable::beforeTimeout()
{
    QMutexLocker lock(&m_cs);
    //
    IRunable* runable = m_pTimeoutRunable;
    m_pTimeoutRunable = NULL;
    //
    return runable;
}


void TimeoutRunable::timeout()
{
    if (IRunable* pRunable = beforeTimeout())
    {
        ExecuteOnThread<IRunable*>(m_nTimeoutThreadId, pRunable);
    }
}


class CQueuedThreads
{
private:
    static QMutex& GetCriticalSection()
    {
        static QMutex cs;
        return cs;
    }
    static std::map<int, IThreadPool*>& GetThreads()
    {
        static std::map<int, IThreadPool*> threads;
        return threads;
    }
    //
    static IThreadPool* GetMainThreadPool()
    {
        static IThreadPool* pool = new MainQueuedThread();
        return pool;
    }
public:
    static IThreadPool* getThreadPool(int threadID, int threadCount = 1)
    {
        QMutex& cs = GetCriticalSection();
        QMutexLocker lock(&cs);
        //
        std::map<int, IThreadPool*>& threads = GetThreads();
        //
        std::map<int, IThreadPool*>::const_iterator it = threads.find(threadID);
        if (it != threads.end())
            return it->second;
        //
        if (threadID == THREAD_MAIN)
        {
            IThreadPool* pool = GetMainThreadPool();
            threads[threadID] = pool;
            return pool;
        }
        //
        IThreadPool* pool = ::CreateThreadPool(threadCount);
        threads[threadID] = pool;
        return pool;
    }
    //

    static void ClearThreadPool()
    {
        QMutex& cs = GetCriticalSection();
        QMutexLocker lock(&cs);
        //
        std::map<int, IThreadPool*>& threads = GetThreads();
        qDebug() << "clear thread pool, threads count : " << threads.size();
        std::map<int, IThreadPool*>::const_iterator it;
        for (it = threads.begin(); it != threads.end(); it++)
        {
            IThreadPool* threadPool = it->second;
            threadPool->shutdown(5);
        }
        threads.clear();
    }
};

void QueuedThreadsInit()
{
    CQueuedThreads::getThreadPool(THREAD_MAIN);
    CQueuedThreads::getThreadPool(THREAD_DOWNLOAD_RESOURCES, 5);
    CQueuedThreads::getThreadPool(THREAD_NETWORK, 2);
}

void QueuedThreadAddAction(int threadID, IRunable* action)
{
    IThreadPool* thread = CQueuedThreads::getThreadPool(threadID);
    //
    thread->addTask(action);
}

void QueuedThreadAddAction(int threadID, IRunable* action, int milliseconds, int nTimeoutThreadId, IRunable* timeoutAction)
{
    IThreadPool* thread = CQueuedThreads::getThreadPool(threadID);
    //
    thread->addTask(new TimeoutRunable(action, milliseconds, nTimeoutThreadId, timeoutAction));
}


void QueuedThreadsShutdown()
{
//    CQueuedThreads::ShutdownAll();

    CQueuedThreads::ClearThreadPool();
}
