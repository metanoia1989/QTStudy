#include "ThreadPool.h"
#include "Thread.h"
#include <QDebug>

ThreadPool::ThreadPool(size_t threads_num, QObject *parent)
    : QObject(parent)
{
    for (size_t i = 0; i < threads_num; i++) {
        m_threads.push_back(QSharedPointer<Thread>(new Thread(i, this)));
    }
}

ThreadPool::~ThreadPool()
{
    {
        QMutexLocker lock(&m_mutex);
        is_running = false;
    }
    m_cond.wakeAll();
    // 等待线程退出
    for (auto thread : m_threads) {
            thread->stop();
    }
    m_threads.clear(); // 智能指针自动释放内存
}

void ThreadPool::enqueue(Task &t)
{
    QMutexLocker lock(&m_mutex);
    if (!is_running)
        return;
    m_tasks.push(qMove(t));
    m_cond.wakeOne();
    qDebug() << "测试唤醒";
}

void ThreadPool::start()
{
    for (auto thread : m_threads) {
            thread->start();
    }
}
