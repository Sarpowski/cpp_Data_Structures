#ifndef QUEUE_H
#define QUEUE_H
#include <exception>
#include <iostream>
#include"simpleException.h"
template <class T>
class Queue
{
public:
	virtual ~Queue() {}
	virtual void enQueue(const T& element) = 0;
	virtual T deQueue() = 0;
	virtual bool isEmpty() const = 0;
};

template <class T>
class QueueArray : public Queue<T>
{
private:
	T* array_;
	int end_;
	int begin_;
	size_t size_;
	void swap(QueueArray<T>& source);
public:
	QueueArray(size_t size = 100);
	QueueArray(const QueueArray<T>& source);
	QueueArray(QueueArray<T>&& source) noexcept;
	QueueArray& operator=(const QueueArray<T>& source) = delete;
	QueueArray& operator=(QueueArray<T>&& source) noexcept;
	~QueueArray();
	void enQueue(const T& element);
	T deQueue();
	bool isEmpty() const;
	
	
	
	
	void print()
	{
		for (size_t i = 0; i < size_; i++)
		{
			std::cout << array_[i] << " ";
		}
		std::cout << "\t";
		if (!isEmpty() )
			std::cout << "begin " << array_[begin_] << " end " << array_[end_] << "\n";
	}
};


template <class T>
void QueueArray<T>::swap(QueueArray<T>& source)
{
	std::swap(array_, source.array_);
	std::swap(begin_, source.begin_);
	std::swap(end_, source.end_);
	std::swap(size_, source.size_);
}

template <class T>
QueueArray<T>::QueueArray(size_t size) :
	size_(size),
	begin_(-1),
	end_(-1)
{
	try {
		array_ = new T[size];
	}
	catch (...) {
		throw WrongQueueSize();
	}
}

template <class T>
QueueArray<T>::QueueArray(const QueueArray<T>& source) :
	size_(source.size_),
	begin_(source.begin_),
	end_(source.end_)
{
	try {
		array_ = new T[source.size_];
	}
	catch (...) {
		throw WrongQueueSize();
	}
	for (size_t i = 1; i < source.size_; i++) {
		array_[i] = source.array_[i];
	}
}

template <class T>
QueueArray<T>::QueueArray(QueueArray<T>&& source) noexcept :
	size_(source.size_),
	begin_(source.begin_),
	end_(source.end_),
	array_(source.array_)
{
	source.size_ = 0;
	source.begin_ = -1;
	source.end_ = -1;
	source.array_ = nullptr;
}

template <class T>
QueueArray<T>& QueueArray<T>::operator=(QueueArray<T>&& source) noexcept
{
	if (this != &source)
	{
		swap(source);
	}
	return *this;
}

template<class T>
QueueArray<T>::~QueueArray()
{
	delete[] array_;
}

template <class T>
void QueueArray<T>::enQueue(const T& element)
{
	if ((end_ + 1) % size_ == begin_)
		throw QueueOverflow();
	else if (begin_ == -1 && end_ == -1)
	{
		begin_ = 0;
		end_ = 0;
		array_[end_] = element;
	}
	else
	{
		end_ = (end_ + 1) % size_;
		array_[end_] = element;
	}
}

template <class T>
T QueueArray<T>::deQueue()
{
	if (isEmpty())
		throw QueueUnderflow();
	size_t temp = begin_;
	if (end_ == begin_)
		begin_ = end_ = -1;
	else
		begin_ = (begin_ + 1) % size_;
	return array_[temp];
}

template <class T>
bool QueueArray<T>::isEmpty() const
{
	return end_ == -1 && begin_ == -1;
}

#endif