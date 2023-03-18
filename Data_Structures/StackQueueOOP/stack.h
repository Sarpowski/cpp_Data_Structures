#pragma once

// Stack abstract base class
template <class T>
class Stack {
public:
    virtual ~Stack() {}
    virtual void push(const T& e) = 0; // Add element to stack
    virtual T pop() = 0; // Remove top element
    virtual bool isEmpty() = 0; // Check if stack is empty
};
