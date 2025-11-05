#pragma once

#include "../lib_TVector/TVector.h"

#include <stdexcept>
#include <initializer_list>

namespace doubly_linked {
	template<class T> struct Node {
		T value;
		Node* prev;
		Node* next;

		Node(T _value, Node* _prev, Node* _next) : value(_value), prev(_prev), next(_next) {};
	};
}

template<class T> class DoublyLinkedList {
	doubly_linked::Node<T>* _head;
	doubly_linked::Node<T>* _tail;
	size_t _size;
public:
	// Constructors
	DoublyLinkedList();
	DoublyLinkedList(size_t);
	DoublyLinkedList(size_t, const T&);
	DoublyLinkedList(const TVector<T>&);
	DoublyLinkedList(std::initializer_list<T>);
	DoublyLinkedList(const DoublyLinkedList&);

	// Destructor
	~DoublyLinkedList();

	// Functions
	DoublyLinkedList& assign(const DoublyLinkedList&);
	DoublyLinkedList& assign(const TVector<T>&);
	bool isEqual(const DoublyLinkedList&) const;
	TVector<T> toTVector() const;

	void pushFront(const T&);
	void pushBack(const T&);
	void insert(size_t, const T&);
	void insertAtNode(doubly_linked::Node<T>*, const T&);
	void popFront();
	void popBack();
	void erase(size_t);
	void eraseNode(doubly_linked::Node<T>*);
	void clear();

	// Getters
	inline bool isEmpty() const { return _head == nullptr; };
	inline size_t size() const { return _size; };
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

	// Operators overload
	DoublyLinkedList& operator=(const DoublyLinkedList&);
	DoublyLinkedList& operator=(const TVector<T>&);
	bool operator==(const DoublyLinkedList&) const;
	bool operator!=(const DoublyLinkedList&) const;

	// Class Iterator
	class Iterator {
		doubly_linked::Node<T>* _current;
	public:
		Iterator() : _current(nullptr) {};
		Iterator(doubly_linked::Node<T>* node) : _current(node) {};

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

		Iterator& operator--() {
			if (_current != nullptr) {
				_current = _current->prev;
			}
			return *this;
		}
		Iterator operator--(int) {
			Iterator iter = *this;
			--(*this);
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
				throw std::logic_error("DoublyLinkedList::Iterator.operator*: Current node is nullptr");
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

		Iterator& operator-=(size_t gap) {
			for (size_t i = 0; i < gap; i++) {
				if (_current == nullptr) break;
				_current = _current->prev;
			}
			return *this;
		}
	};

	// Class ConstIterator
	class ConstIterator {
		const doubly_linked::Node<T>* _current;
	public:
		ConstIterator() : _current(nullptr) {};
		ConstIterator(const doubly_linked::Node<T>* node) : _current(node) {};

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

		ConstIterator& operator--() {
			if (_current != nullptr) {
				_current = _current->prev;
			}
			return *this;
		}

		ConstIterator operator--(int) {
			ConstIterator iter = *this;
			--(*this);
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

		ConstIterator& operator-=(size_t gap) {
			for (size_t i = 0; i < gap; i++) {
				if (_current == nullptr) break;
				_current = _current->prev;
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

template<class T> DoublyLinkedList<T>::DoublyLinkedList() :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{}

template<class T> DoublyLinkedList<T>::DoublyLinkedList(size_t size) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	for (size_t i = 0; i < size; i++) {
		pushBack(T());
	}
}

template<class T> DoublyLinkedList<T>::DoublyLinkedList(size_t size, const T& value) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	for (size_t i = 0; i < size; i++) {
		pushBack(value);
	}
}

template<class T> DoublyLinkedList<T>::DoublyLinkedList(const TVector<T>& vector) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	if (!vector.is_empty()) {
		for (size_t i = 0; i < vector.size(); i++) {
			pushBack(vector[i]);
		}
	}
}

template<class T> DoublyLinkedList<T>::DoublyLinkedList(const std::initializer_list<T> init) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	for (const T& elem : init) {
		pushBack(elem);
	}
}

template<class T> DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) :
	_head(nullptr),
	_tail(nullptr),
	_size(0)
{
	doubly_linked::Node<T>* current = other._head;
	while (current != nullptr) {
		pushBack(current->value);
		current = current->next;
	}
}

// Destructor

template<class T> DoublyLinkedList<T>::~DoublyLinkedList() {
	clear();
}

// Functions

template<class T> DoublyLinkedList<T>& DoublyLinkedList<T>::assign(const DoublyLinkedList& other) {
	if (this != &other) {
		clear();
		_size = 0;
		doubly_linked::Node<T>* current = other._head;
		while (current != nullptr) {
			pushBack(current->value);
			current = current->next;
		}
	}
	return *this;
}

template<class T> DoublyLinkedList<T>& DoublyLinkedList<T>::assign(const TVector<T>& vector) {
	if (vector.size() == 0) {
		throw std::logic_error("DoublyLinkedList.assign_TVector: 'vector.size' must be > 0");
	}

	clear();
	for (size_t i = 0; i < vector.size(); i++) {
		pushBack(vector[i]);
	}

	return *this;
}

template<class T> bool DoublyLinkedList<T>::isEqual(const DoublyLinkedList& other) const {
	if (_size != other._size) return false;

	const doubly_linked::Node<T>* current1 = _head;
	const doubly_linked::Node<T>* current2 = other._head;

	while (current1 != nullptr && current2 != nullptr) {
		if (current1->value != current2->value) return false;
		current1 = current1->next;
		current2 = current2->next;
	}
	return true;
}

template<class T> TVector<T> DoublyLinkedList<T>::toTVector() const {
	TVector<T> result;
	doubly_linked::Node<T>* current = _head;
	while (current != nullptr) {
		result.push_back(current->value);
		current = current->next;
	}

	return result;
}

template<class T> void DoublyLinkedList<T>::pushFront(const T& value) {
	doubly_linked::Node<T>* node = new doubly_linked::Node<T>(value, nullptr, _head);

	if (_head != nullptr) {
		_head->prev = node;
	}

	if (isEmpty()) {
		_tail = node;
	}
	_head = node;
	_size++;
}

template<class T> void DoublyLinkedList<T>::pushBack(const T& value) {
	doubly_linked::Node<T>* node = new doubly_linked::Node<T>(value, _tail, nullptr);

	if (isEmpty()) {
		_head = node;
		_tail = node;
	}
	else {
		_tail->next = node;
		_tail = node;
	}
	_size++;
}

template<class T> void DoublyLinkedList<T>::insert(size_t pos, const T& value) {
	if (pos > _size) {
		throw std::out_of_range("DoublyLinkedList.insert: 'pos' out of range");
	}

	if (pos == 0) {
		pushFront(value);
	}
	else if (pos == _size) {
		pushBack(value);
	}
	else {
		doubly_linked::Node<T>* current = _head;
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
}

template<class T> void DoublyLinkedList<T>::insertAtNode(doubly_linked::Node<T>* pos, const T& value) {
	if (pos == nullptr) {
		throw std::logic_error("DoublyLinkedList.insert: Node pointer is null");
	}

	if (isEmpty()) {
		throw std::logic_error("DoublyLinkedList.insert: List is empty");
	}

	doubly_linked::Node<T>* node = new doubly_linked::Node<T>(value, pos, pos->next);
	if (node->next != nullptr) {
		node->next->prev = node;
	}
	pos->next = node;
	if (pos == _tail) {
		_tail = node;
	}
	_size++;
}

template<class T> void DoublyLinkedList<T>::popFront() {
	if (isEmpty()) {
		throw std::logic_error("DoublyLinkedList.popFront: List is empty");
	}

	doubly_linked::Node<T>* node = _head;
	_head = _head->next;

	if (_head != nullptr) {
		_head->prev = nullptr;
	}
	else {
		_tail = nullptr;
	}

	delete node;
	_size--;
}

template<class T> void DoublyLinkedList<T>::popBack() {
	if (isEmpty()) {
		throw std::logic_error("DoublyLinkedList.popBack: List is empty");
	}

	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		doubly_linked::Node<T>* newTail = _tail->prev;
		newTail->next = nullptr;
		delete _tail;
		_tail = newTail;
	}
	_size--;
}

template<class T> void DoublyLinkedList<T>::erase(size_t pos) {
	if (pos >= _size) {
		throw std::out_of_range("DoublyLinkedList.insert: 'pos' out of range");
	}

	if (isEmpty()) {
		throw std::logic_error("DoublyLinkedList.erase: List is empty");
	}

	if (pos == 0) {
		popFront();
	}
	else if (pos == _size - 1) {
		popBack();
	}
	else {
		doubly_linked::Node<T>* current = _head;
		size_t currentPos = 0;
		while (current != nullptr && currentPos < pos) {
			currentPos++;
			current = current->next;
		}

		current->prev->next = current->next;
		if (current->next != nullptr) {
			current->next->prev = current->prev;
		}
		delete current;
		_size--;
	}
}

template<class T> void DoublyLinkedList<T>::eraseNode(doubly_linked::Node<T>* pos) {
	if (pos == nullptr) {
		throw std::logic_error("DoublyLinkedList.erase: Node pointer is null");
	}

	if (isEmpty()) {
		throw std::logic_error("DoublyLinkedList.erase: List is empty");
	}

	if (pos == _head) {
		popFront();
	}
	else if (pos == _tail) {
		popBack();
	}
	else {
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		delete pos;
		_size--;
	}
}

template<class T> void DoublyLinkedList<T>::clear() {
	while (_head != nullptr) {
		doubly_linked::Node<T>* current = _head;
		_head = _head->next;
		delete current;
	}
	_tail = nullptr;
	_size = 0;
}

// Getters

template<class T> T& DoublyLinkedList<T>::front() {
	if (isEmpty()) {
		throw std::logic_error("DoublyLinkedList.front: Unable to access front element - list is empty");
	}
	return _head->value;
}
template<class T> const T& DoublyLinkedList<T>::front() const {
	if (isEmpty()) {
		throw std::logic_error("DoublyLinkedList.front: Unable to access front element - list is empty");
	}
	return _head->value;
}
template<class T> T& DoublyLinkedList<T>::back() {
	if (isEmpty()) {
		throw std::logic_error("DoublyLinkedList.back: Unable to access back element - list is empty");
	}
	return _tail->value;
}

template<class T> const T& DoublyLinkedList<T>::back() const {
	if (isEmpty()) {
		throw std::logic_error("DoublyLinkedList.back: Unable to access back element - list is empty");
	}
	return _tail->value;
}

// Operators overload

template<class T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
	return this->assign(other);
}

template<class T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const TVector<T>& vector) {
	return this->assign(vector);
}

template<class T> bool DoublyLinkedList<T>::operator==(const DoublyLinkedList& other) const {
	return this->isEqual(other);
}

template<class T> bool DoublyLinkedList<T>::operator!=(const DoublyLinkedList& other) const {
	return !(*this == other);
}