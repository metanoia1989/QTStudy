#include "Thread.h"
#include "ThreadPool.h"
#include <QtAlgorithms>
#include <QDebug>

Thread::Thread(int id, ThreadPool *pool, QObject *parent) :
    QObject(parent),
    m_threadPool(pool),
    m_id(id)
{

    moveToThread(&m_thread);
    connect(&m_thread, &QThread::started, [this](){
        emit threadStarted();
        run();
    });
    connect(&m_thread, &QThread::finished, [this](){
        emit threadStoped();
    });
}

Thread::~Thread()
{
    if (isStarted())
        stop();
}

int Thread::id() const
{
    return m_id;
}

bool Thread::start()
{
    bool ok = false;
    if (!isStarted()) {
        m_thread.start();
        ok = true;
    }
    return ok;
}

bool Thread::stop()
{
    bool ok = false;
    if (isStarted()) {
        m_thread.quit();
        m_thread.wait();
        emit threadStoped();
        ok = true;
    }
    return ok;
}

bool Thread::isStarted() const
{
    return m_thread.isRunning();
}

void Thread::run()
{
    while (true) {
        m_threadPool->m_mutex.lock();
        qDebug() << QString("线程%1 进入等待！").arg(m_id);
        m_threadPool->m_cond.wait(&m_threadPool->m_mutex);
        qDebug() << QString("线程%1 被唤醒！").arg(m_id);
        if (!m_threadPool->is_running && m_threadPool->m_tasks.empty()) {
            m_threadPool->m_mutex.unlock();
            return;
        }
        m_task = m_threadPool->m_tasks.front();
        m_threadPool->m_tasks.pop();
        m_threadPool->m_mutex.unlock();
        m_task.run();
    }
}

