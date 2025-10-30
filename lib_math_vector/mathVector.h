#pragma once

#include <iostream>
#include "../lib_TVector/TVector.h"
#include <initializer_list>
#include <utility>

template<class T> class mathVector : public TVector<T> {
public:
    // Constructors
    mathVector();
    mathVector(int);
    mathVector(int, const T*);
    mathVector(std::initializer_list<T>);
    mathVector(int, std::initializer_list<T>);
    mathVector(const mathVector<T>&);
    mathVector(const TVector<T>&);
    mathVector(mathVector&&) noexcept;

    // Math functions
    mathVector<T> add(const mathVector<T>&) const;
    mathVector<T> sub(const mathVector<T>&) const;
    mathVector<T> mult(const T&) const;
    mathVector<T> div(const T&) const;
    T scalarMult(const mathVector<T>&) const;

    // Operators that don't change the current object
    mathVector<T> operator+(const mathVector<T>&) const;
    mathVector<T> operator-(const mathVector<T>&) const;
    mathVector<T> operator*(const T&) const;
    mathVector<T> operator/(const T&) const;
    T operator*(const mathVector<T>&) const;

    // Operators that change the current object
    mathVector<T>& operator+=(const mathVector<T>&);
    mathVector<T>& operator-=(const mathVector<T>&);
    mathVector<T>& operator*=(const T&);
    mathVector<T>& operator/=(const T&);

    // Other operator
    mathVector<T>& operator=(const mathVector<T>&);
};

// Constructors

template<class T> mathVector<T>::mathVector() : TVector<T>() {}

template<class T> mathVector<T>::mathVector(int size) : TVector<T>(size) {}

template<class T> mathVector<T>::mathVector(int size, const T* data) : TVector<T>(size, data) {}

template<class T> mathVector<T>::mathVector(std::initializer_list<T> init) : TVector<T>(init) {}

template<class T> mathVector<T>::mathVector(int size, std::initializer_list<T> init) : TVector<T>(size, init) {}

template<class T> mathVector<T>::mathVector(const mathVector<T>& other) : TVector<T>(other) {}

template<class T> mathVector<T>::mathVector(const TVector<T>& other) : TVector<T>(other) {}

template<class T> mathVector<T>::mathVector(mathVector&& other) noexcept : TVector<T>(other) {}

// Math functions

template<class T> mathVector<T> mathVector<T>::add(const mathVector<T>& other) const {
    if (this->size() != other.size()) {
        throw std::logic_error("mathVector.add: vectors must be the same size");
    }
    mathVector<T> result(this->size());
    for (int i = 0; i < this->size(); i++) {
        result[i] = this->at(i) + other[i];
    }

    return result;
}

template<class T> mathVector<T> mathVector<T>::sub(const mathVector<T>& other) const {
    if (this->size() != other.size()) {
        throw std::logic_error("mathVector.sub: vectors must be the same size");
    }
    mathVector<T> result(this->size());
    for (int i = 0; i < this->size(); i++) {
        result[i] = this->at(i) - other[i];
    }
    return result;
}

template<class T> mathVector<T> mathVector<T>::mult(const T& scalar) const {
    mathVector<T> result(this->size());
    for (int i = 0; i < this->size(); i++) {
        result[i] = this->at(i) * scalar;
    }
    return result;
}

template<class T> mathVector<T> mathVector<T>::div(const T& scalar) const {
    if (scalar == T()) {
        throw std::logic_error("mathVector.div: division by zero");
    }
    mathVector<T> result(this->size());
    for (int i = 0; i < this->size(); i++) {
        result[i] = this->at(i) / scalar;
    }
    return result;
}

template<class T> T mathVector<T>::scalarMult(const mathVector<T>& other) const {
    if (this->size() != other.size()) {
        throw std::logic_error("mathVector.scalarMult: vectors must be the same size");
    }

    T result = T();
    for (int i = 0; i < this->size(); i++) {
        result += this->at(i) * other[i];
    }
    return result;
}

// Operators that don't change the current object

template<class T> mathVector<T> mathVector<T>::operator+(const mathVector<T>& other) const {
    return this->add(other);
}

template<class T> mathVector<T> mathVector<T>::operator-(const mathVector<T>& other) const {
    return this->sub(other);
}

template<class T> mathVector<T> mathVector<T>::operator*(const T& scalar) const {
    return this->mult(scalar);
}

template<class T> mathVector<T> mathVector<T>::operator/(const T& scalar) const {
    return this->div(scalar);
}

template<class T> T mathVector<T>::operator*(const mathVector<T>& other) const {
    return this->scalarMult(other);
}

// Operators that change the current object

template<class T> mathVector<T>& mathVector<T>::operator+=(const mathVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::logic_error("mathVector.+=: Vectors must be the same size");
    }
    for (int i = 0; i < this->size(); i++) {
        this->at(i) += other[i];
    }
    return *this;
}

template<class T> mathVector<T>& mathVector<T>::operator-=(const mathVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::logic_error("mathVector.-=: Vectors must be the same size");
    }
    for (int i = 0; i < this->size(); i++) {
        this->at(i) -= other[i];
    }
    return *this;
}

template<class T> mathVector<T>& mathVector<T>::operator*=(const T& scalar) {
    for (int i = 0; i < this->size(); i++) {
        this->at(i) *= scalar;
    }
    return *this;
}

template<class T> mathVector<T>& mathVector<T>::operator/=(const T& scalar) {
    if (scalar == T()) {
        throw std::logic_error("mathVector./=: Division by zero");
    }
    for (int i = 0; i < this->size(); i++) {
        this->at(i) /= scalar;
    }
    return *this;
}

// Other operator

template<class T> mathVector<T>& mathVector<T>::operator=(const mathVector<T>& other) {
    if (this != &other) {
        TVector<T>::operator=(other);
    }
    return *this;
}