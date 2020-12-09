#include "WorkThread.h"
#include "ThreadPool.h"

WorkThread::WorkThread(ThreadPool *parent)
{
    m_Pool = parent;
}

WorkThread::~WorkThread()
{
    qDebug() << __FUNCTION__  << m_Handle
             << "Thread quit: " << isFinished();
}

void WorkThread::run()
{
    m_Handle = QThread::currentThreadId();
    while (!m_Pool->m_stop) {
        m_Pool->m_TaskMutex.lock();
        while (m_Pool->m_tasks.isEmpty()) {
            qDebug() << QThread::currentThreadId() << QString("进入等待");
            m_Pool->m_NotEmpty.wait(&m_Pool->m_TaskMutex);
            qDebug() << QThread::currentThreadId() << QString("被唤醒");

            // 线程退出条件判断
            if (m_Pool->m_stop) {
                m_Pool->m_TaskMutex.unlock();
                return;
            }
        }

        // 取出任务
        Task task = m_Pool->m_tasks.front();
        m_Pool->m_tasks.pop_front();
        m_Pool->m_TaskMutex.unlock();

        if (task)
            task();
    }
}

