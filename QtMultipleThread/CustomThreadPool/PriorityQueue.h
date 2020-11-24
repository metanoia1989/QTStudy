#pragma once

#include <QVector>
#include <algorithm>

template <
        typename T,
        typename Array = QVector<T>,
        typename compare_T=std::less<T>
>
class PriorityQueue
{
public:
    PriorityQueue();
    bool empty();
    T front();
    void push(const T& val);
    void pop();
    int size();

private:
    void up_adjust(); // 向上调整
    void down_adjust(); // 向下调整

    Array elements;
    compare_T compare;
};

template<typename T, typename Array, typename compare_T>
PriorityQueue<T, Array, compare_T>::PriorityQueue()
{
    elements.clear();
}

template<typename T, typename Array, typename compare_T>
bool PriorityQueue<T, Array, compare_T>::empty()
{
    return elements.size() == 0;
}

template<typename T, typename Array, typename compare_T>
T PriorityQueue<T, Array, compare_T>::front()
{
    return elements[0];
}

template<typename T, typename Array, typename compare_T>
void PriorityQueue<T, Array, compare_T>::push(const T &val)
{
    elements.push_back(val);
    up_adjust();
}

template<typename T, typename Array, typename compare_T>
void PriorityQueue<T, Array, compare_T>::pop()
{
    if (empty()) return;
    int count = elements.size();
    qSwap(elements[count - 1], elements[0]);
    elements.pop_back();
    down_adjust();
}

template<typename T, typename Array, typename compare_T>
int PriorityQueue<T, Array, compare_T>::size()
{
    return elements.size();
}

template<typename T, typename Array, typename compare_T>
void PriorityQueue<T, Array, compare_T>::up_adjust()
{
    int ind = elements.size();
    while (ind > 1 && compare(elements[ind/2-1], elements[ind-1])) {
        qSwap(elements[ind/2-1], elements[ind-1]);
        ind /= 2;
    }
}

template<typename T, typename Array, typename compare_T>
void PriorityQueue<T, Array, compare_T>::down_adjust()
{
    int ind = 0;
    int count = elements.size();
    while (ind * 2 + 1 < count) {
        int tind = ind;
        if (compare(elements[tind], elements[ind*2+1]))
            tind = ind * 2 + 1;

        if (ind*2+2<count && compare(elements[tind], elements[ind*2+1]))
            tind = ind * 2 + 2;

        if (ind == tind)
            break;

        qSwap(elements[ind], elements[tind]);
        ind = tind;
    }
}
