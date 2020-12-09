#pragma once

#include <QObject>
#include <QList>
#include <QMutex>
#include <QWaitCondition>
#include "Task.h"
#include "WorkThread.h"

class ThreadPool : public QObject
{
    Q_OBJECT
public:
    explicit ThreadPool(QObject *parent = nullptr);
    ~ThreadPool();

    void PushTask(Task task);
    void Start();
    void Destroy();

private:
    QList<Task> m_tasks; // 任务队列
    QList<QSharedPointer<WorkThread>> m_Threads; // 运行的线程
    bool m_stop; // 停止线程

    QMutex m_TaskMutex;
    QWaitCondition m_NotEmpty;

    friend class WorkThread;
};

