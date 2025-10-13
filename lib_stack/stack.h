#pragma once

#include "../lib_TVector/TVector.h"

template<class T> class stack {
	TVector<T> _data;
public:
	// Constructors
	stack();
	stack(int);
	stack(TVector<T>&);
	stack(std::initializer_list<T>);
	stack(const stack&);

	// Functions
	void push(T val);
	void pop();
	T& top() const;
	inline bool isEmpty() const noexcept { return _data.is_empty(); };
	inline bool isFull() const noexcept { return _data.is_full(); };
	void clear() noexcept;
};

// Constructors

template<class T> stack<T>::stack() {
	_data.shrink_to_fit();
}
template<class T> stack<T>::stack(int size) {
	_data.reserve(size);
}

template<class T> stack<T>::stack(TVector<T>& other) {
	_data = TVector<T>(other);
	_data.shrink_to_fit();
}

template<class T> stack<T>::stack(std::initializer_list<T> init) {
	_data = TVector<T>(init);
	_data.shrink_to_fit();
}

template<class T> stack<T>::stack(const stack& other) {
	_data = other._data;
	_data.shrink_to_fit();
}

// Functions

template<class T> void stack<T>::push(T val) {
	if (isFull()) {
		throw std::logic_error("stack.push: Unable to push - stack is full");
	}
	_data.push_back(val);
}

template<class T> void stack<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("stack.pop: Unable to pop - stack is empty");
	}
	_data.pop_back();
}

template<class T> T& stack<T>::top() const {
	if (isEmpty()) {
		throw std::logic_error("stack.top: Unable to get top element - stack is empty");
	}
	return _data.back();
}

template<class T> void stack<T>::clear() noexcept {
	if (isEmpty()) return;
	_data.clear();
}

