#pragma once

#include "../lib_TVector/TVector.h"

#include <stdexcept>
#include <initializer_list>

namespace doubly_linked {
	template<class T> struct Node {
		T value;
		Node* next;
		Node* previous;

		Node(T _value, Node* _next, Node* _previous) : value(_value), next(_next), previous(_previous) {};
	};
}

template<class T> class DoublyLinkedList {
/*
	doubly_linked::Node<T>* _head;
	doubly_linked::Node<T>* _tail;
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
	*/
};