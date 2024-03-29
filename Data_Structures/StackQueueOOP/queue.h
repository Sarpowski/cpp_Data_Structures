#pragma once


template <class T>
class Queue
{
public:
    virtual ~Queue() {}
    virtual void enQueue(const T& e) = 0;// Adding an item to the queue
    virtual T deQueue() = 0;// Deleting an item from the queue
    virtual bool isEmpty() = 0; // Checking the queue for emptiness
    
};