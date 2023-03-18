#pragma once
#include"stack.h"
#include"myexceptions.h"

//  stack  array
template <class T>
class StackArray : public Stack<T> {
public:
    StackArray(int size) 
    {
        if (size <= 0) 
        {
            throw WrongStackSize();
        }
        maxSize = size;
        top = -1;
        stack = new T[maxSize];
    }

    ~StackArray() 
    {
        delete[] stack;
    }

   
    void push(const T& e) {
        if (top >= maxSize - 1) {
            throw StackOverFlow();
        }
        stack[++top] = e;
    }

    T pop() 
    {
        if (top < 0) 
        {
            throw StackUnderFlow();
        }
        return stack[top--];
    }

    bool isEmpty() 
    {
        return top == -1;
    }

private:
    int maxSize;
    int top;//size_t??
    T* stack;
};

