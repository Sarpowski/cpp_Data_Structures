#pragma once
#include <exception>

// Stack exceptions
class StackOverFlow : public std::exception
{
public:
    virtual const char* what() const throw() {
        return "Stack overflow";
    }
};

class StackUnderFlow : public std::exception
{
public:
    virtual const char* what() const throw() {
        return "Stack underflow";
    }
};
class WrongStackSize : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Invalid stack size!";
    }
};

//queue exceptions !!!

class QueueOverFlow : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Queue Overflow!";
    }
};

class QueueUnderFlow : public  std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Queue Under Flow!";
    }
};

class WrongQueueSize : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Wrong Queue Size ";
    }
};



