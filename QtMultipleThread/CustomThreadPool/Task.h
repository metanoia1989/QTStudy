#pragma once

#include <functional>

class Task
{
public:
    Task(){};

    template<typename Func, typename ...Args>
    Task(Func f, Args&& ...args)
    {
        func = std::bind(f, std::forward<Args>(args)...);
    }

    virtual void run()
    {
        func();
    }

    void setPriority(int priority)
    {
        m_priority = priority;
    }

    friend bool operator<(const Task& t1, const Task& t2);

private:
    std::function<void()> func;
    int m_priority = 100;
};

inline bool operator<(const Task& t1, const Task& t2)
{
    return t1.m_priority < t2.m_priority;
}
