#pragma once
#include "queue.h"

template <class T>
class QueueArray : public Queue<T>
{
public:
    QueueArray(int max_Size)
    {
        if (max_Size < 1)
        {
            throw WrongQueueSize();
        }

        array = new T[max_Size];
        QueueFront = 0;
        QueueBack = -1;
        QueueMax = max_Size;
        count = 0;
    }
    ~QueueArray()
    {
        delete[] array;
    }
    void enQueue(const T &e)
    {
        if (count == QueueMax)
            throw QueueOverFlow();
        QueueBack = (QueueBack + 1) % QueueMax;
        array[QueueBack] = e;
        count++;
    }
    T deQueue()
    {
        if (count == 0)
            throw QueueUnderFlow();
        T data = array[QueueFront];
        QueueFront = (QueueFront + 1) % QueueMax;
        count--;
        return data;
    }
    bool isEmpty()
    {
        return count == 0;
    }

private:
    T *array;
    int QueueFront; // size_t???
    int QueueBack;
    int QueueMax;
    int count;
};
