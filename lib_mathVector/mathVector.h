#include <iostream>
#include "../lib_TVector/TVector.h"
#include <initializer_list>
#include <utility>

#pragma once

template <typename T> class mathVector : public TVector<T> {
public:
    mathVector();
    explicit mathVector(int);
    mathVector(int, const T*);
    explicit mathVector(std::initializer_list<T>);
    mathVector(int, std::initializer_list<T>);
    explicit mathVector(const mathVector<T>&);
    explicit mathVector(const TVector<T>&);
    mathVector(mathVector&&) noexcept;

    ~mathVector();

    mathVector<T>& operator+(const mathVector<T>&) const;
    mathVector<T>& operator-(const mathVector<T>&) const;
    mathVector<T>& operator*(const T) const;
    mathVector<T>& operator+=(const mathVector<T>&);
    mathVector<T>& operator-=(const mathVector<T>&);
    mathVector<T>& operator*=(const T);
    T operator*(const mathVector<T>&) const;
};

template<class T> mathVector<T>::mathVector() {
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    for (int i = 0; i < _capacity; i++) _states[i] = TVectorElemState::empty;
}

template<class T> mathVector<T>::mathVector(int size) {
    if (size < 0) throw std::invalid_argument("mathVector.size_constructor: Invalid argument 'size' - must be >= 0");
    _size = size;
    if (_size == 0) {
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        for (int i = 0; i < _capacity; i++) _states[i] = TVectorElemState::empty;
    }
    else {
        _capacity = size + CAPACITY;
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        for (int i = 0; i < _size; i++) _states[i] = TVectorElemState::busy;
        for (int i = _size; i < _capacity; i++) _states[i] = TVectorElemState::empty;
    }
}

template<class T> mathVector<T>::mathVector(int size, const T* data) {
    if (size < 0) {
        throw std::invalid_argument("mathVector.sizedata_constructor: Invalid argument 'size' - must be >= 0");
    }
    if (data == nullptr && size > 0) {
        throw std::invalid_argument("mathVector.size_constructor: Invalid argument 'data' - is nullptr");
    }
    _size = size;
    _capacity = _size + CAPACITY;
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = data[i];
        _states[i] = TVectorElemState::busy;
    }
    for (int i = _size; i < _capacity; i++) {
        _states[i] = TVectorElemState::empty;
    }
}

template<class T> mathVector<T>::mathVector(std::initializer_list<T> init) {
    if (init.size() > 0) {
        _size = init.size();
        _capacity = _size + CAPACITY;
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        const T* src = init.begin();
        for (int i = 0; i < _size; i++) {
            _data[i] = src[i];
            _states[i] = TVectorElemState::busy;
        }
        for (int i = _size; i < _capacity; i++) {
            _states[i] = TVectorElemState::empty;
        }
    }
}

template<class T> mathVector<T>::mathVector(int size, std::initializer_list<T> init) {
    if (size < 0) {
        throw std::invalid_argument("mathVector.sizeinitlist_constructor: Invalid argument 'size' - must be >= 0");
    }
    if (size > 0) {
        _size = size;
        _capacity = _size + CAPACITY;
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        const T* src = init.begin();
        for (int i = 0; i < _size; i++) {
            _data[i] = src[i];
            _states[i] = TVectorElemState::busy;
        }
        for (int i = _size; i < _capacity; i++) {
            _states[i] = TVectorElemState::empty;
        }
    }
}

template<class T> mathVector<T>::mathVector(const mathVector<T>& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _deleted = other._deleted;
    _states = new TVectorElemState[_capacity];
    for (int i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}

template<class T> mathVector<T>::mathVector(const TVector<T>& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _deleted = other._deleted;
    _states = new TVectorElemState[_capacity];
    for (int i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}

template<class T> mathVector<T>::mathVector(mathVector&& other) noexcept :
    _data(std::exchange(other._data, nullptr)),
    _size(std::exchange(other._size, 0)),
    _capacity(std::exchange(other._capacity, CAPACITY)),
    _deleted(std::exchange(other._deleted, 0)),
    _states(std::exchange(other._states, nullptr))
{

}

template<class T> mathVector<T>::~mathVector() {
    if (_data != nullptr) {
        delete[] _data;
        delete[] _states;
    }
}


template<class T> mathVector<T>& mathVector<T>::operator+(const mathVector<T>& other) const {
    if (size() != other._size) {
        throw std::logic_error("mathVector.operator+: vectors must be the same size");
    }
    mathVector<T> result(size());
    for (int i = 0; i < size(); i++) {
        result[i] = at(i) + other[i];
    }
    return result;
}

template<class T>mathVector<T>& mathVector<T>::operator-(const mathVector<T>&) const {
    if (size() != other._size) {
        throw std::logic_error("mathVector.operator-: vectors must be the same size");
    }
    mathVector<T> result(size());
    for (int i = 0; i < size(); i++) {
        result[i] = at(i) - other[i];
    }
    return result;
}

template<class T>mathVector<T>& mathVector<T>::operator*(const T scalar) const {
    mathVector<T> result(size());
    for (int i = 0; i < size(); i++) {
        result[i] = at(i) * scalar;
    }
    return result;
}

template<class T>mathVector<T>& mathVector<T>::operator+=(const mathVector<T>&) {
    if (size() != other._size) {
        throw std::logic_error("mathVector.operator+=: vectors must be the same size");
    }
    for (int i = 0; i < size(); i++) {
        this->at(i) += other[i];
    }
    return *this;
}

template<class T>mathVector<T>& mathVector<T>::operator-=(const mathVector<T>&) {
    if (size() != other._size) {
        throw std::logic_error("mathVector.operator-=: vectors must be the same size");
    }
    for (int i = 0; i < size(); i++) {
        this->at(i) -= other[i];
    }
    return *this;
}

template<class T> mathVector<T>& mathVector<T>::operator*=(const T scalar) {
    for (int i = 0; i < size(); i++) {
        this->at(i) *= scalar;
    }
    return *this;
}

template<class T> T mathVector<T>::operator*(const mathVector<T>& other) const {
    if (size() != other._size) {
        throw std::logic_error("mathVector.operator* vec: vectors must be the same size");
    }

    T result = T();

    for (int i = 0; i < size(); i++) {
        result += at(i) * other[i];
    }
    return result;
}