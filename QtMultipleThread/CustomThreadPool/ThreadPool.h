#pragma once

#include "PriorityQueue.h"
#include "Task.h"

#include <QThread>
#include <QVector>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <QSharedPointer>
#include <QTimer>

class Thread;


using QueueType = PriorityQueue<Task>;
class ThreadPool : public QObject
{
public:
    ThreadPool(size_t threads_num = QThread::idealThreadCount(), QObject *parent = nullptr);
    ~ThreadPool();
    void enqueue(Task& t);
    void start();
    int tasksCount();

private:
    QVector<QSharedPointer<Thread>> m_threads;
    bool is_running = false;
    QueueType m_tasks;
    QMutex m_mutex;
    QWaitCondition m_cond;

    friend class Thread;
};
