#include <iostream>
#include <initializer_list>
#include "../lib_mathVector/mathVector.h"

#pragma once

template<class T> class matrix : public mathVector<mathVector<T>> {
    int _rows, _cols;
public:
    matrix();
    matrix(int, int);
    matrix(std::initializer_list<std::initializer_list<T>>);
    matrix(const matrix<T>&);

    ~matrix() = default;

    int rows() const;
    int cols() const;

    T& at(int, int);
    mathVector<T>& operator[](int);

    matrix<T> operator+(const matrix<T>&) const;
    matrix<T> operator-(const matrix<T>&) const;
    matrix<T> operator*(const matrix<T>& other) const;
    matrix<T> operator*(const T) const;
    mathVector<T> operator*(const mathVector<T>& vec) const;

    matrix<T> transpose();
    matrix<T>& operator=(const matrix<T>& other);
};

template<class T> matrix<T>::matrix() : mathVector<mathVector<T>>(), _rows(0), _cols(0)
{

}

template<class T> matrix<T>::matrix(int rows, int cols) :
    mathVector<mathVector<T>>(rows), _rows(rows), _cols(cols) {
    for (int i = 0; i < rows; i++) {
        at(i) = mathVector<T>(cols);
    }
}

template<class T> matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> init) {
    _rows = init.size();
    if (_rows == 0) {
        _cols = 0;
        return;
    }

    _cols = init.begin()->size();

    for (const auto& row : init) {
        if (row.size() != _cols) {
            throw std::invalid_argument("matrix init_list: All rows must have same size");
        }
    }

    this->_size = _rows;
    this->_capacity = _rows + CAPACITY;
    this->_data = new mathVector<T>[this->_capacity];
    this->_states = new TVectorElemState[this->_capacity];

    const std::initializer_list<T>* src = init.begin();
    for (int i = 0; i < _rows; i++) {
        this->_data[i] = mathVector<T>(src[i]);
        this->_states[i] = TVectorElemState::busy;
    }

    for (int i = _rows; i < this->_capacity; i++) {
        this->_states[i] = TVectorElemState::empty;
    }
}

template<class T> matrix<T>::matrix(const matrix<T>& other) : 
    MathVector<MathVector<T>>(other), _rows(other._rows), _cols(other._cols)
{

}

template<class T> int matrix<T>::rows() const {
    return _rows;
}

template<class T> int matrix<T>::cols() const {
    return _cols;
}

template<class T> T& matrix<T>::at(int row, int col) {
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) {
        throw std::out_of_range("matrix.at: Index out of range");
    }
    return this->mathVector<mathVector<T>>::at(row).at(col);
}

template<class T> mathVector<T>& matrix<T>::operator[](int row) {
    return this->mathVector<mathVector<T>>::at(row);
}

template<class T> matrix<T> matrix<T>::operator+(const matrix<T>& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::logic_error("matrix.operator+: Matrices must have same dimensions");
    }

    matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        result[i] = this->at(i) + other[i];
    }
    return result;
}

template<class T> matrix<T> matrix<T>::operator-(const matrix<T>& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::logic_error("matrix.operator-: Matrices must have same dimensions");
    }

    matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        result[i] = this->at(i) - other[i];
    }
    return result;
}

template<class T> matrix<T> matrix<T>::operator*(const matrix<T>& other) const {
    if (_cols != other._rows) {
        throw std::logic_error("matrix::operator*: Incompatible dimensions for multiplication");
    }

    matrix<T> result(_rows, other._cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._cols; j++) {
            T sum = T();
            for (int k = 0; k < _cols; k++) {
                sum += this->at(i, k) * other.at(k, j);
            }
            result[i][j] = sum;
        }
    }
    return result;
}

template<class T> matrix<T> matrix<T>::operator*(const T scalar) const {
    matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        result[i] = this->at(i) * scalar;
    }
    return result;
}

template<class T> mathVector<T> matrix<T>::operator*(const mathVector<T>& vec) const {
    if (_cols != vec.size()) {
        throw std::logic_error("matrix.operator*: Incompatible dimensions for matrix-vector multiplication");
    }

    mathVector<T> result(_rows);
    for (int i = 0; i < _rows; i++) {
        T sum = T();
        for (int j = 0; j < _cols; j++) {
            sum += this->at(i, j) * vec[j];
        }
        result[i] = sum;
    }
    return result;
}



template<class T> matrix<T> matrix<T>::transpose() {
    matrix<T> result(_cols, _rows);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result[j][i] = this->at(i, j);
        }
    }
    return result;
}

template<class T> matrix<T>& matrix<T>::operator=(const matrix<T>& other) {
    if (this != &other) {
        mathVector<mathVector<T>>::operator=(other);
        _rows = other._rows;
        _cols = other._cols;
    }
    return *this;
}