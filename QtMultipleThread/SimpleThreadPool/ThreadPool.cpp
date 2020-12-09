#include "ThreadPool.h"

ThreadPool::ThreadPool(QObject *parent)
    : QObject(parent),
      m_stop(false)
{
    for(int i = 0; i < m_Threads.count(); i++)
        m_Threads.push_back(QSharedPointer<WorkThread>(new WorkThread(this)));
}

ThreadPool::~ThreadPool()
{
    Destroy();
}

void ThreadPool::PushTask(Task task)
{
    m_TaskMutex.lock();
    m_tasks.push_back(task);
    m_NotEmpty.wakeOne();
    m_TaskMutex.unlock();
}

void ThreadPool::Start()
{
    for (auto thread : m_Threads)
        thread->start();
}

void ThreadPool::Destroy()
{
    m_stop = true;
    m_NotEmpty.wakeAll();

    for (auto thread : m_Threads) {
        if (!thread->isFinished())
            thread->wait();
    }
    m_Threads.clear();
}
