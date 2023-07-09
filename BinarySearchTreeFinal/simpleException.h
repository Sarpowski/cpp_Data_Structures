#ifndef SIMPLEEXCEPTION_H
#define SIMPLEEXCEPTION_H
#include<iostream>
#include<exception>

//queue 
class QueueOverflow : public std::exception
{
	public:
    virtual const char* what() const throw()
    {
        return "Queue Overflow!";
    }
};

class QueueUnderflow : public std::exception
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


//stack
class StackOverflow : public std::exception
{
public:
	 virtual const char* what() const throw() {
        return "Stack overflow";
    }

};


class StackUnderflow : public std::exception
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


#endif 