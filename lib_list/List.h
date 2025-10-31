#pragma once

#include "../lib_TVector/TVector.h"

#include <stdexcept>
#include <initializer_list>

namespace singly_linked {
	template<class T> struct Node {
		T value;
		Node* next;

		Node(T _value, Node* _next) : value(_value), next(_next) {};
	};
}

template<class T> class List {
	singly_linked::Node<T>* _head;
	singly_linked::Node<T>* _tail;
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
	bool isEqual(const List&) const;
	TVector<T> toTVector() const;

	void pushFront(const T&);
	void pushBack(const T&);
	void insert(size_t, const T&);
	void insertAtNode(singly_linked::Node<T>*, const T&);
	void popFront();
	void popBack();
	void erase(size_t);
	void eraseNode(singly_linked::Node<T>*);
	void clear();

	// Getters
	inline bool isEmpty() const { return _head == nullptr; };
	inline size_t size() const { return _size; };
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

	// Operators overload
	List& operator=(const List&);
	List& operator=(const TVector<T>&);
	bool operator==(const List&) const;
	bool operator!=(const List&) const;

	// Class Iterator
	class Iterator {
		singly_linked::Node<T>* _current;
	public:
		Iterator() : _current(nullptr) {};
		Iterator(singly_linked::Node<T>* node) : _current(node) {};

		Iterator& operator=(const Iterator& other) {
			if (this != &other) {
				_current = other._current;
			}
			return *this;
		}

		Iterator& operator++() {
			if (_current != nullptr) {
				_current = _current->next;
			}
			return *this;
		}
		Iterator operator++(int) {
			Iterator iter = *this;
			++(*this);
			return iter;
		}

		bool operator==(const Iterator& other) const {
			return _current == other._current;
		}

		bool operator!=(const Iterator& other) const {
			return _current != other._current;
		}

		T& operator*() {
			if (_current == nullptr) {
				throw std::logic_error("List::Iterator.operator*: Current node is nullptr");
			}
			return _current->value;
		}

		Iterator& operator+=(size_t gap) {
			for (size_t i = 0; i < gap; i++) {
				if (_current == nullptr) break;
				_current = _current->next;
			}
			return *this;
		}
	};

	// Class ConstIterator
	class ConstIterator {
		const singly_linked::Node<T>* _current;
	public:
		ConstIterator() : _current(nullptr) {};
		ConstIterator(const singly_linked::Node<T>* node) : _current(node) {};

		ConstIterator& operator=(const ConstIterator& other) {
			if (this != &other) {
				_current = other._current;
			}
			return *this;
		}

		ConstIterator& operator++() {
			if (_current != nullptr) {
				_current = _current->next;
			}
			return *this;
		}

		ConstIterator operator++(int) {
			ConstIterator iter = *this;
			++(*this);
			return iter;
		}

		bool operator==(const ConstIterator& other) const {
			return _current == other._current;
		}

		bool operator!=(const ConstIterator& other) const {
			return _current != other._current;
		}

		const T& operator*() const {
			if (_current == nullptr) {
				throw std::logic_error("List::ConstIterator.operator*: Current node is nullptr");
			}
			return _current->value;
		}

		ConstIterator& operator+=(size_t gap) {
			for (size_t i = 0; i < gap; i++) {
				if (_current == nullptr) break;
				_current = _current->next;
			}
			return *this;
		}
	};

	// Getters associated with the Iterator class
	inline Iterator begin() { return Iterator(_head); };
	inline Iterator end() { return Iterator(nullptr); };
	inline ConstIterator begin() const { return ConstIterator(_head); };
	inline ConstIterator end() const { return ConstIterator(nullptr); };
};

// Constructors

template<class T> List<T>::List() :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{}

template<class T> List<T>::List(size_t size) : // Can be optimized
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	for (int i = 0; i < size; i++) {
		pushBack(T());
	}
}

template<class T> List<T>::List(size_t size, const T& value) : // Can be optimized
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
	singly_linked::Node<T>* current = other._head;
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
		singly_linked::Node<T>* current = other._head;
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

template<class T> bool List<T>::isEqual(const List& other) const {
	if (_size != other._size) return false;

	const singly_linked::Node<T>* current1 = _head;
	const singly_linked::Node<T>* current2 = other._head;

	while (current1 != nullptr && current2 != nullptr) {
		if (current1->value != current2->value) return false;
		current1 = current1->next;
		current2 = current2->next;
	}
	return true;
}

template<class T> TVector<T> List<T>::toTVector() const {
	TVector<T> result;
	singly_linked::Node<T>* current = _head;
	while (current != nullptr) {
		result.push_back(current->value);
		current = current->next;
	}

	return result;
}

template<class T> void List<T>::pushFront(const T& value) {
	_size++;
	singly_linked::Node<T>* node = new singly_linked::Node<T>(value, _head);
	if (isEmpty()) {
		_tail = node;
	}
	_head = node;
}

template<class T> void List<T>::pushBack(const T& value) { // O(n)
	_size++;
	singly_linked::Node<T>* node = new singly_linked::Node<T>(value, nullptr);

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

	singly_linked::Node<T>* current = _head;
	size_t currentPos = 0;
	while (current != nullptr) {
		if (currentPos == pos - 1) {
			break;
		}
		currentPos++;
		current = current->next;
	}
	insertAtNode(current, value);
}

template<class T> void List<T>::insertAtNode(singly_linked::Node<T>* pos, const T& value) {
	if (pos == nullptr) {
		throw std::logic_error("List.insert: Node pointer is null");
	}

	if (isEmpty()) {
		throw std::logic_error("List.insert: List is empty");
	}

	singly_linked::Node<T>* node = new singly_linked::Node<T>(value, pos->next);
	pos->next = node;
	if (pos == _tail) {
		_tail = node;
	}
	_size++;
}

template<class T> void List<T>::popFront() {
	if (isEmpty()) {
		throw std::logic_error("List.popFront: List is empty");
	}

	singly_linked::Node<T>* node = _head;
	_head = _head->next;
	delete node;
	if (_head == nullptr) {
		_tail = nullptr;
	}
	_size--;
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
		singly_linked::Node<T>* current = _head;
		while (current->next != _tail) {
			current = current->next;
		}
		delete _tail;
		_tail = current;
		_tail->next = nullptr;
	}
	_size--;
}

template<class T> void List<T>::erase(size_t pos) {
	if (pos >= _size) {
		throw std::out_of_range("List.insert: 'pos' out of range");
	}

	if (pos == 0) {
		popFront();
		return;
	}

	if (pos == _size - 1) {
		popBack();
		return;
	}

	singly_linked::Node<T>* current = _head;
	size_t currentPos = 0;
	while (current != nullptr && currentPos < pos - 1) {
		currentPos++;
		current = current->next;
	}

	singly_linked::Node<T>* toDelete = current->next;
	current->next = toDelete->next;
	if (toDelete == _tail) {
		_tail = current;
	}
	delete toDelete;
	_size--;
}

template<class T> void List<T>::eraseNode(singly_linked::Node<T>* pos) { // O(n)
	if (pos == nullptr) {
		throw std::logic_error("List.erase: Node pointer is null");
	}

	if (isEmpty()) {
		throw std::logic_error("List.erase: List is empty");
	}

	if (pos == _head) {
		popFront();
		return;
	}

	if (pos == _tail) {
		popBack();
		return;
	}

	singly_linked::Node<T>* current = _head;
	while (current->next != pos) {
		if (current->next == nullptr) {
			throw std::invalid_argument("List.erase: Node not found in list");
		}
		current = current->next;
	}

	current->next = pos->next;
	if (pos == _tail) {
		_tail = current;
	}
	delete pos;
	_size--;
}

template<class T> void List<T>::clear() {
	while (_head != nullptr) {
		singly_linked::Node<T>* current = _head;
		_head = _head->next;
		delete current;
	}
	_tail = nullptr;
	_size = 0;
}

// Getters

template<class T> T& List<T>::front() {
	if (isEmpty()) {
		throw std::logic_error("List.front: Unable to access front element - list is empty");
	}
	return _head->value;
}
template<class T> const T& List<T>::front() const {
	if (isEmpty()) {
		throw std::logic_error("List.front: Unable to access front element - list is empty");
	}
	return _head->value;
}
template<class T> T& List<T>::back() {
	if (isEmpty()) {
		throw std::logic_error("List.back: Unable to access back element - list is empty");
	}
	return _tail->value;
}

template<class T> const T& List<T>::back() const {
	if (isEmpty()) {
		throw std::logic_error("List.back: Unable to access back element - list is empty");
	}
	return _tail->value;
}

// Operators overload

template<class T> List<T>& List<T>::operator=(const List& other) {
	return this->assign(other);
}

template<class T> List<T>& List<T>::operator=(const TVector<T>& vector) {
	return this->assign(vector);
}

template<class T> bool List<T>::operator==(const List& other) const {
	return this->isEqual(other);
}

template<class T> bool List<T>::operator!=(const List& other) const {
	return !(*this == other);
}