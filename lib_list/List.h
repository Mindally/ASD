#pragma once

#include "../lib_TVector/TVector.h"

#include <stdexcept>
#include <initializer_list>

template<class T> class List {
private:
	struct Node {
		T value;
		Node* next;

		Node(T _value, Node* _next) : value(_value), next(_next) {};
	};

	Node* _head;
	Node* _tail;
	size_t _size;
public:
	// Constructors
	List();
	List(size_t);
	List(size_t, const T&);
	List(const TVector<T>&);
	List(std::initializer_list<T>);
	List(const List&);

	// Destructor
	~List();

	// Functions
	List& assign(const List&);
	List& assign(const TVector<T>&);
	TVector<T> toTVector() const;

	void pushFront(const T&);
	void pushBack(const T&);
	void insert(size_t, const T&);
	void insert(Node*, const T&);
	void popBack();
	void clear();

	// Getters
	inline bool isEmpty() const { return _head == nullptr; };
	inline size_t size() const { return _size; };

	// Operators overload
	List& operator=(const List&);
	List& operator=(const TVector<T>&);
};

// Constructors

template<class T> List<T>::List() :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{}

template<class T> List<T>::List(size_t size) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	for (int i = 0; i < size; i++) {
		pushBack(T());
	}
}

template<class T> List<T>::List(size_t size, const T& value) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	for (int i = 0; i < size; i++) {
		pushBack(value);
	}
}

template<class T> List<T>::List(const TVector<T>& vector) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	for (int i = 0; i < vector.size(); i++) {
		pushBack(vector[i]);
	}
}

template<class T> List<T>::List(const std::initializer_list<T> init) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	for (const T& elem : init) {
		pushBack(elem);
	}
}

template<class T> List<T>::List(const List& other) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	Node* current = other._head;
	while (current != nullptr) {
		pushBack(current->value);
		current = current->next;
	}
}

// Destructor

template<class T> List<T>::~List() {
	clear();
}

// Functions

template<class T> List<T>& List<T>::assign(const List& other) {
	if (this != &other) {
		clear();
		_size = 0;
		Node* current = other._head;
		while (current != nullptr) {
			pushBack(current->value);
			current = current->next;
		}
	}
	return *this;
}

template<class T> List<T>& List<T>::assign(const TVector<T>& vector) {
	if (vector.size() == 0) {
		throw std::logic_error("List.assign_TVector: 'vector.size' must be > 0");
	}

	clear();
	for (int i = 0; i < vector.size(); i++) {
		pushBack(vector[i]);
	}

	return *this;
}

template<class T> TVector<T> List<T>::toTVector() const {
	TVector<T> result;
	Node* current = _head;
	while (current != nullptr) {
		result.push_back(current->value);
		current = current->next;
	}

	return result;
}

template<class T> void List<T>::pushFront(const T& value) {
	_size++;
	Node* node = new Node(value, _head);
	if (isEmpty()) {
		_tail = node;
	}
	_head = node;
}

template<class T> void List<T>::pushBack(const T& value) {
	_size++;
	Node* node = new Node(value, nullptr);

	if (isEmpty()) {
		_head = node;
		_tail = node;
		return;
	}
	_tail->next = node;
	_tail = node;
}

template<class T> void List<T>::insert(size_t pos, const T& value) {
	if (pos > _size) {
		throw std::out_of_range("List.insert: 'pos' out of range");
	}

	if (pos == 0) {
		pushFront(value);
		return;
	}

	if (pos == _size) {
		pushBack(value);
		return;
	}

	Node* current = _head;
	for (int i = 0; i < pos - 1; i++) {
		current = current->next;
	}

	Node* node = new Node(value, current->next);
	current->next = node;
	_size++;
}

template<class T> void List<T>::insert(Node* pos, const T& value) {
	if (pos == nullptr) {
		throw std::logic_error("List.insert: Node pointer is null");
	}

	if (isEmpty) {
		throw std::logic_error("List.insert: List is empty");
	}

	Node* node = new Node(value, pos->next);
	pos->next = node;
	_size++;
	if (pos == _tail) {
		_tail = node;
	}
}

template<class T> void List<T>::popBack() {
	if (isEmpty()) {
		throw std::logic_error("List.popBack: List is empty");
	}

	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		Node* current = _head;
		while (current->next != _tail) {
			current = current->next;
		}
		delete _tail;
		_tail = current;
		_tail->next = nullptr;
	}
	_size--;
}

template<class T> void List<T>::clear() {
	while (_head != nullptr) {
		Node* current = _head;
		_head = _head->next;
		delete current;
	}
	_tail = nullptr;
}

// Operators overload

template<class T> List<T>& List<T>::operator=(const List& other) {
	return this->assign(other);
}

template<class T> List<T>& List<T>::operator=(const TVector<T>& vector) {
	return this->assign(vector);
}