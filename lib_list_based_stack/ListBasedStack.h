#pragma once

#include "../lib_TVector/TVector.h"
#include "../lib_List/List.h"
#include "../lib_stack/stack.h"

#include <stdexcept>
#include <initializer_list>

#define STACK_DEFAULT_SIZE 10

template<class T> class ListBasedStack {
	List<T> _data;
	size_t _size;
public:
	// Constructors
	ListBasedStack();
	ListBasedStack(size_t);
	ListBasedStack(size_t, const T&);
	ListBasedStack(const TVector<T>&);
	ListBasedStack(const std::initializer_list<T>);
	ListBasedStack(const ListBasedStack&);

	// Functions
	ListBasedStack& assign(const ListBasedStack&);
	ListBasedStack& assign(const TVector<T>&);
	TVector<T> toTVector() const;
	Stack<T> toStack() const;

	void push(const T& val);
	void pop();
	T& top();
	const T& top() const;
	void clear() noexcept;

	void reserve(size_t) noexcept;
	void shrinkToFit();

	// Getters
	inline bool isEmpty() const noexcept { return _data.isEmpty(); }
	inline bool isFull() const noexcept { return _data.size() == _size; }
	inline size_t size() const noexcept { return _data.size(); }
	inline size_t capacity() const noexcept { return _size; }

	// Operators overload
	ListBasedStack& operator=(const ListBasedStack&);
	ListBasedStack& operator=(const TVector<T>&);
};

// Constructors

template<class T> ListBasedStack<T>::ListBasedStack() :
	_size(STACK_DEFAULT_SIZE)
{}

template<class T> ListBasedStack<T>::ListBasedStack(size_t size) :
	_size(size)
{
	if (size == 0) {
		throw std::logic_error("ListBasedStack.size_constructor: 'size' must be > 0");
	}
}

template<class T> ListBasedStack<T>::ListBasedStack(size_t size, const T& value) :
	_size(size)
{
	if (size == 0) {
		throw std::logic_error("Stack.sizevalue_constructor: 'size' must be > 0");
	}
	for (size_t i = 0; i < _size; i++) {
		_data.pushBack(value);
	}
}

template<class T> ListBasedStack<T>::ListBasedStack(const TVector<T>& vector) :
	_size(vector.size())
{
	if (vector.size() == 0) {
		throw std::logic_error("Stack.fromTVector_constructor: 'size' must be > 0");
	}
	for (size_t i = 0; i < _size; i++) {
		_data.pushBack(vector[i]);
	}
}

template<class T> ListBasedStack<T>::ListBasedStack(const std::initializer_list<T> init) :
	_size(init.size())
{
	if (init.size() == 0) {
		throw std::logic_error("Stack.fromInitializeList_constructor: 'size' must be > 0");
	}
	size_t i = 0;
	for (const auto& elem : init) {
		_data.pushBack(elem);
	}
}

template<class T> ListBasedStack<T>::ListBasedStack(const ListBasedStack& other) :
	_size(other._size)
{
	_data = other._data;
}

// Functions

template<class T> ListBasedStack<T>& ListBasedStack<T>::assign(const ListBasedStack& other) {
	if (this != &other) {
		_data.assign(other._data);
		_size = other.size();
	}
	return *this;
}

template<class T> ListBasedStack<T>& ListBasedStack<T>::assign(const TVector<T>& vector) {
	_data.assign(vector);
	_size = vector.size();
	return *this;
}

template<class T> TVector<T> ListBasedStack<T>::toTVector() const {
	return _data.toTVector();
}

template<class T> Stack<T> ListBasedStack<T>::toStack() const {
	Stack<T> result(_data.size());
	for (auto it = _data.begin(); it != _data.end(); ++it) {
		result.push(*it);
	}
	return result;
}

template<class T> void ListBasedStack<T>::push(const T& val) {
	if (isFull()) {
		throw std::logic_error("ListBasedStack.push: Unable to push - stack is full");
	}
	_data.pushBack(val);
}

template<class T> void ListBasedStack<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("ListBasedStack.pop: Unable to pop - stack is empty");
	}
	_data.popBack();
}

template<class T> T& ListBasedStack<T>::top() {
	if (isEmpty()) {
		throw std::logic_error("ListBasedStack.top: Unable to get top element - stack is empty");
	}
	return _data.back();
}

template<class T> const T& ListBasedStack<T>::top() const {
	if (isEmpty()) {
		throw std::logic_error("ListBasedStack.top: Unable to get top element - stack is empty");
	}
	return _data.back();
}

template<class T> void ListBasedStack<T>::clear() noexcept {
	_data.clear();
}

template<class T> void ListBasedStack<T>::reserve(size_t newCapacity) noexcept {
	if (newCapacity <= _size) return;
	_size = newCapacity;
}

template<class T> void ListBasedStack<T>::shrinkToFit() {
	if (isEmpty()) {
		throw std::logic_error("ListBasedStack.shrinkToFit: Undable to shrink - stack is empty");
	}
	if (isFull()) return;
	_size = _data.size();
}


// Operators overload

template<class T> ListBasedStack<T>& ListBasedStack<T>::operator=(const ListBasedStack& other) {
	return this->assign(other);
}

template<class T> ListBasedStack<T>& ListBasedStack<T>::operator=(const TVector<T>& vector) {
	return this->assign(vector);
}