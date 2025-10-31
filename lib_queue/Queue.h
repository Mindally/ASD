#pragma once

#include "../lib_TVector/TVector.h"

#include <stdexcept>
#include <initializer_list>

#define QUEUE_DEFAULT_SIZE 10

template<class T> class Queue {
	T* _data;
	size_t _size;
	size_t _count;
	size_t _head;
	size_t _tail;
public:
	// Constructors
	Queue();
	Queue(size_t);
	Queue(const TVector<T>&);
	Queue(std::initializer_list<T>);
	Queue(const Queue&);

	// Destructor
	~Queue();

	// Functions
	Queue& assign(const Queue&);
	Queue& assign(const TVector<T>&);
	TVector<T> toTVector() const;

	void push(T val);
	void pop();
	T& head();
	T& tail();
	const T& head() const;
	const T& tail() const;
	void clear() noexcept;

	// Getters
	inline bool isEmpty() const noexcept { return _count == 0; };
	inline bool isFull() const noexcept { return _count == _size; };
	inline size_t size() const noexcept { return _count; }
	inline size_t capacity() const noexcept { return _size; }

	// Operators overload
	Queue& operator=(const Queue&);
	Queue<T>& operator=(const TVector<T>&);
};

// Constructors

template<class T> Queue<T>::Queue() :
	_data(new T[QUEUE_DEFAULT_SIZE]),
	_size(QUEUE_DEFAULT_SIZE),
	_count(0),
	_head(0),
	_tail(0)
{}

template<class T> Queue<T>::Queue(size_t size) :
	_data(nullptr),
	_size(size),
	_count(0),
	_head(0),
	_tail(0)
{
	if (size <= 0) {
		throw std::invalid_argument("Queue.size_constructor: 'size' must be > 0");
	}
	_data = new T[size];
}

template<class T> Queue<T>::Queue(const TVector<T>& vector) :
	_data(nullptr),
	_size(vector.size()),
	_count(vector.size()),
	_head(0),
	_tail(_count % _size)
{
	if (vector.size() == 0) {
		throw std::invalid_argument("Queue.fromTVector_constructor: 'size' must be > 0");
	}
	_data = new T[vector.size()];
	for (int i = 0; i < _size; i++) {
		_data[i] = vector[i];
	}
}

template<class T> Queue<T>::Queue(std::initializer_list<T> init) :
	_data(nullptr),
	_size(init.size()),
	_count(init.size()),
	_head(0),
	_tail(_count% _size)
{
	if (init.size() == 0) {
		throw std::invalid_argument("Queue.fromInitializeList_constructor: 'size' must be > 0");
	}
	_data = new T[init.size()];
	size_t i = 0;
	for (const auto& elem : init) {
		_data[i++] = elem;
	}
}

template<class T> Queue<T>::Queue(const Queue& other) :
	_data(nullptr),
	_size(other._size),
	_count(other._count),
	_head(other._head),
	_tail(other._tail)
{
	_data = new T[other._size];
	for (int i = 0; i < other._size; i++) {
		_data[i] = other._data[i];
	}
}

// Destructor

template<class T> Queue<T>::~Queue() {
	delete[] _data;
}

// Functions

template<class T> Queue<T>& Queue<T>::assign(const Queue& other) {
	if (this != &other) {
		delete[] _data;
		_size = other._size;
		_count = other._count;
		_head = other._head;
		_tail = other._tail;
		_data = new T[_size];
		for (int i = 0; i < _size; i++) {
			_data[i] = other._data[i];
		}
	}
	return *this;
}

template<class T> Queue<T>& Queue<T>::assign(const TVector<T>& vector) {
	if (vector.size() == 0) {
		throw std::logic_error("Queue.assign_TVector: 'vector.size' must be > 0");
	}
	delete[] _data;
	_size = vector.size();
	_count = vector.size();
	_head = 0;
	_tail = _count % _size;
	_data = new T[_size];
	for (int i = 0; i < _size; i++) {
		_data[i] = vector[i];
	}
	return *this;
}

template<class T> TVector<T> Queue<T>::toTVector() const {
	TVector<T> result(_count);
	for (int i = 0; i < _count; i++) {
		result[i] = _data[(_head + i) % _size];
	}
	return result;
}

template<class T> void Queue<T>::push(T val) {
	if (isFull()) {
		throw std::logic_error("Queue.push: Unable to push - queue is full");
	}
	_count++;
	_data[_tail] = val;
	_tail = (_tail + 1) % _size;
}

template<class T> void Queue<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("Queue.pop: Unable to pop - Queue is empty");
	}
	_count--;
	_head = (_head + 1) % _size;
}

template<class T> T& Queue<T>::head() {
	if (isEmpty()) {
		throw std::logic_error("Queue.head: Unable to get head element - Queue is empty");
	}
	return _data[_head];
}

template<class T> T& Queue<T>::tail() {
	if (isEmpty()) {
		throw std::logic_error("stack.top: Unable to get top element - stack is empty");
	}
	return _data[(_tail - 1 + _size) % _size];
}

template<class T> const T& Queue<T>::head() const {
	if (isEmpty()) {
		throw std::logic_error("Queue.head: Unable to get head element - Queue is empty");
	}
	return _data[_head];
}

template<class T> const T& Queue<T>::tail() const {
	if (isEmpty()) {
		throw std::logic_error("stack.top: Unable to get top element - stack is empty");
	}
	return _data[(_tail - 1 + _size) % _size];
}

template<class T> void Queue<T>::clear() noexcept {
	_count = 0;
	_head = 0;
	_tail = 0;
}

// Operators overload

template<class T> Queue<T>& Queue<T>::operator=(const Queue& other) {
	return this->assign(other);
}

template<class T> Queue<T>& Queue<T>::operator=(const TVector<T>& vector) {
	return this->assign(vector);
}
