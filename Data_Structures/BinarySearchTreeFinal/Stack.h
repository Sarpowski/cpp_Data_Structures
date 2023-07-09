#ifndef STACK_H
#define STACK_H
#include <exception>
#include"simpleException.h"


template <class T>
class Stack
{
public:
	virtual ~Stack() = default;
	virtual void push(const T& e) = 0;
	virtual T pop() = 0;
	virtual bool isEmpty() = 0;
};

template <class T>
class StackArray : public Stack<T>
{
public:
	StackArray(size_t size = 256);
	StackArray(const StackArray<T>& src) = delete;
	StackArray(StackArray<T>&& src) = delete;
	StackArray& operator=(const StackArray<T>& src) = delete;
	StackArray& operator=(StackArray<T>&& src) = delete;
	~StackArray();
	void push(const T& e);
	T pop();
	bool isEmpty();
private:
	T* array_;
	size_t top_;
	size_t size_;
	void swap(StackArray<T>& src);
};

template <class T>
void StackArray<T>::swap(StackArray<T>& src)
{
	std::swap(array_, src.array_);
	std::swap(top_, src.top_);
	std::swap(size_, src.size_);
}

template <class T>
StackArray<T>::StackArray(size_t size) :
	size_(size),
	top_(0)
{
	try {
		array_ = new T[size + 1];
	}
	catch (...) {
		throw WrongStackSize();
	}
}

template <class T>
StackArray<T>::~StackArray() {
	delete[] array_;
}

template <class T>
void StackArray<T>::push(const T& e)
{
	if (top_ == size_) {
		throw StackOverflow();
	}
	array_[++top_] = e;
}

template <class T>
T StackArray<T>::pop()
{
	if (isEmpty()) {
		throw StackUnderflow();
	}
	return array_[top_--];
}

template <class T>
bool StackArray<T>::isEmpty(){ 
	return top_ == 0;
}


#endif