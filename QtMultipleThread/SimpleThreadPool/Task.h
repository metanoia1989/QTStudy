#pragma once
#include <QThread>
#include <QDebug>

class Task
{
public:
    Task(int a, int b) : m_a(a), m_b(b) {}

    void operator()() const
    {
        QThread::msleep(300);
        qDebug() << QThread::currentThreadId()
                 << QString("执行任务")
                 << m_a << "+" << m_b
                 << QString(" = ")
                 << m_a + m_b;
    }

    operator bool() const
    {
        if (m_b == 0)
            return false;
        return true;
    }

private:
    int m_a;
    int m_b;
};
