#pragma once

#include "../lib_TVector/TVector.h"

#include <stdexcept>
#include <initializer_list>

#define STACK_DEFAULT_SIZE 10

template<class T> class Stack {
	T* _data;
	int _top;
	size_t _size;
public:
	// Constructors
	Stack();
	Stack(size_t);
	Stack(const TVector<T>&);
	Stack(std::initializer_list<T>);
	Stack(const Stack&);

	// Desturctor
	~Stack();

	// Functions
	Stack& assign(const Stack&);
	Stack& assign(const TVector<T>&);
	TVector<T> toTVector() const;

	void push(const T& val);
	void pop();
	T& top();
	const T& top() const;
	void clear() noexcept;

	// Getters
	inline bool isEmpty() const noexcept { return _top == -1; }
	inline bool isFull() const noexcept { return _top == static_cast<int>(_size - 1); }
	inline size_t size() const noexcept { return static_cast<size_t>(_top + 1); }
	inline size_t capacity() const noexcept { return _size; }

	// Operators overload
	Stack& operator=(const Stack&);
	Stack& operator=(const TVector<T>&);
};

// Constructors

template<class T> Stack<T>::Stack() :
	_data(new T[STACK_DEFAULT_SIZE]),
	_size(STACK_DEFAULT_SIZE),
	_top(-1)
{}

template<class T> Stack<T>::Stack(size_t size) :
	_data(nullptr),
	_size(size),
	_top(-1)
{
	if (size == 0) {
		throw std::logic_error("Stack.size_constructor: 'size' must be > 0");
	}
	_data = new T[_size];
}

template<class T> Stack<T>::Stack(const TVector<T>& vector) :
	_data(nullptr),
	_size(vector.size()),
	_top(static_cast<int>(vector.size()) - 1)
{
	if (vector.size() == 0) {
		throw std::logic_error("Stack.fromTVector_constructor: 'size' must be > 0");
	}
	_data = new T[vector.size()];
	for (int i = 0; i < _size; i++) {
		_data[i] = vector[i];
	}
}

template<class T> Stack<T>::Stack(std::initializer_list<T> init) : 
	_data(nullptr),
	_size(init.size()),
	_top(static_cast<int>(init.size()) - 1)
{
	if (init.size() == 0) {
		throw std::logic_error("Stack.fromInitializeList_constructor: 'size' must be > 0");
	}
	_data = new T[init.size()];
	size_t i = 0;
	for (const auto& elem : init) {
		_data[i++] = elem;
	}
}

template<class T> Stack<T>::Stack(const Stack& other) :
	_data(nullptr),
	_size(other._size),
	_top(other._top) 
{
	_data = new T[_size];
	for (int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
}

// Destructor

template<class T> Stack<T>::~Stack() {
	delete[] _data;
}

// Functions

template<class T> Stack<T>& Stack<T>::assign(const Stack& other) {
	if (this != &other) {
		delete[] _data;
		_size = other._size;
		_top = other._top;
		_data = new T[_size];
		for (int i = 0; i < _size; i++) {
			_data[i] = other._data[i];
		}
	}
	return *this;
}

template<class T> Stack<T>& Stack<T>::assign(const TVector<T>& vector) {
	if (vector.size() == 0) {
		throw std::logic_error("Stack.assign_TVector: 'vector.size' must be > 0");
	}
	delete[] _data;
	_size = vector.size();
	_top = vector.size() - 1;
	_data = new T[_size];
	for (int i = 0; i < _size; i++) {
		_data[i] = vector[i];
	}
	return *this;
}

template<class T> TVector<T> Stack<T>::toTVector() const {
	TVector<T> result(_top + 1);
	for (int i = 0; i < _size; i++) {
		result[i] = _data[i];
	}
	return result;
}

template<class T> void Stack<T>::push(const T& val) {
	if (isFull()) {
		throw std::logic_error("Stack.push: Unable to push - stack is full");
	}
	_top++;
	_data[_top] = val;
}

template<class T> void Stack<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("Stack.pop: Unable to pop - stack is empty");
	}
	_top--;
}

template<class T> T& Stack<T>::top() {
	if (isEmpty()) {
		throw std::logic_error("Stack.top: Unable to get top element - stack is empty");
	}
	return _data[_top];
}

template<class T> const T& Stack<T>::top() const {
	if (isEmpty()) {
		throw std::logic_error("Stack.top: Unable to get top element - stack is empty");
	}
	return _data[_top];
}

template<class T> void Stack<T>::clear() noexcept {
	_top = -1;
}

// Operators overload

template<class T> Stack<T>& Stack<T>::operator=(const Stack& other) {
	return this->assign(other);
}

template<class T> Stack<T>& Stack<T>::operator=(const TVector<T>& vector) {
	return this->assign(vector);
}