#pragma once

#include <iostream>
#include <initializer_list>
#include <cmath>
#include "../lib_mathVector/mathVector.h"

template<class T> class matrix : public mathVector<mathVector<T>> {
protected:
    int _rows, _cols;
public:
    // Constructors
    matrix();
    matrix(int, int);
    matrix(const mathVector<mathVector<T>>&);
    matrix(std::initializer_list<std::initializer_list<T>>);
    matrix(const matrix<T>&);

    // Math functions

    // Scalar
    matrix<T> addScalar(const T&) const;
    matrix<T> subScalar(const T&) const;
    matrix<T> multScalar(const T&) const;
    matrix<T> divScalar(const T&) const;

    // Vector
    mathVector<T> vectorMult(const mathVector<T>&) const;

    // Matrix
    matrix<T> add(const matrix<T>&) const;
    matrix<T> sub(const matrix<T>&) const;
    matrix<T> matrixMult(const matrix<T>&) const;

    // Other functions
    matrix<T> transpose() const;
    bool isEqual(const matrix<T>&) const;
    void print() const;


    // Getters
    int rows() const;
    int cols() const;
    T& atMatrix(int, int);
    mathVector<T>& operator[](int);
    mathVector<T>& operator[](int) const;

    // Operators that don't change the current object

    // Scalar
    matrix<T> operator+(const T&) const;
    matrix<T> operator-(const T&) const;
    matrix<T> operator*(const T&) const;
    matrix<T> operator/(const T&) const;

    // Vector
    mathVector<T> operator*(const mathVector<T>&) const;

    // Matrix
    matrix<T> operator+(const matrix<T>&) const;
    matrix<T> operator-(const matrix<T>&) const;
    matrix<T> operator*(const matrix<T>& other) const;

    // Operators that change the current object

    // Scalar
    matrix<T>& operator+=(const T&);
    matrix<T>& operator-=(const T&);
    matrix<T>& operator*=(const T&);
    matrix<T>& operator/=(const T&);

    // Matrix
    matrix<T>& operator+=(const matrix<T>&);
    matrix<T>& operator-=(const matrix<T>&);
    matrix<T>& operator*=(const matrix<T>&);

    // Other operators
    matrix<T>& operator=(const matrix<T>&);
    bool operator==(const matrix<T>&);
    bool operator!=(const matrix<T>&);
};

// Constructors

template<class T> matrix<T>::matrix() :
    mathVector<mathVector<T>>(),
    _rows(0),
    _cols(0)
{}

template<class T> matrix<T>::matrix(int rows, int cols) :
    mathVector<mathVector<T>>(),
    _rows(rows),
    _cols(cols)
{
    if (rows < 0 || cols < 0) {
        throw std::invalid_argument("matrix: Invalid argument 'rows' or 'col' - must be >= 0");
    }
    for (int i = 0; i < rows; i++) {
        mathVector<T> row;
        for (int j = 0; j < cols; j++) {
            row.push_back(T());
        }
        this->push_back(row);
    }
}

template<class T> matrix<T>::matrix(const mathVector<mathVector<T>>& other) :
    mathVector<mathVector<T>>(other),
    _rows(other.size()),
    _cols(other.size() ? other[0].size() : 0) {}

template<class T> matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> init) :
    mathVector<mathVector<T>>(),
    _rows(static_cast<int>(init.size())),
    _cols(0)
{

    if (_rows == 0) return;

    _cols = static_cast<int>(init.begin()->size());
    for (auto& row : init) {
        if (row.size() != _cols) {
            throw std::invalid_argument("matrix: All rows must have same size");
        }
        this->push_back(mathVector<T>(row));
    }
}

template<class T> matrix<T>::matrix(const matrix<T>& other) : 
    mathVector<mathVector<T>>(other),
    _rows(other._rows),
    _cols(other._cols)
{}

// Math functions

// Scalar

template<class T> matrix<T> matrix<T>::addScalar(const T& scalar) const {
    matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result[i][j] = (*this)[i][j] + scalar;
        }
    }
    return result;
}
template<class T> matrix<T> matrix<T>::subScalar(const T& scalar) const {
    matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result[i][j] = (*this)[i][j] - scalar;
        }
    }
    return result;
}

template<class T> matrix<T> matrix<T>::multScalar(const T& scalar) const {
    matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result[i][j] = (*this)[i][j] * scalar;
        }
    }
    return result;
}

template<class T> matrix<T> matrix<T>::divScalar(const T& scalar) const {
    if (scalar == T()) {
        throw std::logic_error("matrix.divScalar: division by zero");
    }

    matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result[i][j] = (*this)[i][j] / scalar;
        }
    }
    return result;
}

// Vector

template<class T> mathVector<T> matrix<T>::vectorMult(const mathVector<T>& vector) const {
    if (vector.is_empty()) {
        throw std::logic_error("matrix.vectorMult: Vector is empty");
    }
    if (_cols != vector.size()) {
        throw std::logic_error("matrix.vectorMult: Matrix and vector must have same dimensions");
    }
    mathVector<T> result(_rows);
    for (int i = 0; i < _rows; i++) {
        result[i] = (*this)[i] * vector;
    }
    return result;
}

// Matrix

template<class T> matrix<T> matrix<T>::add(const matrix<T>& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::logic_error("matrix.add: Matrices must have same dimensions");
    }

    matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        result[i] = (*this)[i] + other[i];
    }
    return result;
}

template<class T> matrix<T> matrix<T>::sub(const matrix<T>& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::logic_error("matrix.sub: Matrices must have same dimensions");
    }

    matrix<T> result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        result[i] = (*this)[i] - other[i];
    }
    return result;
}


template<class T> matrix<T> matrix<T>::matrixMult(const matrix<T>& other) const {
    if (_cols != other._rows) {
        throw std::logic_error("matrix.matrixMult: Incompatible dimensions for multiplication");
    }

    matrix<T> result(_rows, other._cols);

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._cols; j++) {
            T sum = T();
            for (int k = 0; k < _cols; k++) {
                sum += (*this)[i][k] * other[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

// Other functions

template<class T> matrix<T> matrix<T>::transpose() const {
    if (_rows == 0 || _cols == 0) {
        return matrix<T>();
    }

    matrix<T> result(_cols, _rows);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result[j][i] = (*this)[i][j];
        }
    }
    return result;
}

template<class T> bool matrix<T>::isEqual(const matrix<T>& other) const {
    if (_rows != other._rows || _cols != other._cols) return false;
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            if ((*this)[i][j] != other[i][j]) return false;
        }
    }
    return true;
}

template<class T> void matrix<T>::print() const {
    // TODO
}

// Getters

template<class T> int matrix<T>::rows() const {
    return _rows;
}

template<class T> int matrix<T>::cols() const {
    return _cols;
}

template<class T> T& matrix<T>::atMatrix(int row, int col) {
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) {
        throw std::out_of_range("matrix.at: Index out of range");
    }
    return (*this)[row][col];
}

template<class T> mathVector<T>& matrix<T>::operator[](int row) {
    return mathVector<mathVector<T>>::operator[](row);
}

template<class T> mathVector<T>& matrix<T>::operator[](int row) const {
    return mathVector<mathVector<T>>::operator[](row);
}

// Operators that don't change the current object

// Scalar

template<class T> matrix<T> matrix<T>::operator+(const T& scalar) const {
    return this->addScalar(scalar);
}

template<class T> matrix<T> matrix<T>::operator-(const T& scalar) const {
    return this->subScalar(scalar);
}

template<class T> matrix<T> matrix<T>::operator*(const T& scalar) const {
    return this->multScalar(scalar);
}

template<class T> matrix<T> matrix<T>::operator/(const T& scalar) const {
    return this->divScalar(scalar);
}

// Vector

template<class T> mathVector<T> matrix<T>::operator*(const mathVector<T>& vector) const {
    return this->vectorMult(vector);
}

// Matrix

template<class T> matrix<T> matrix<T>::operator+(const matrix<T>& other) const {
    return this->add(other);
}

template<class T> matrix<T> matrix<T>::operator-(const matrix<T>& other) const {
    return this->sub(other);
}

template<class T> matrix<T> matrix<T>::operator*(const matrix<T>& other) const {
    return this->matrixMult(other);
}

// Operators that change the current object

// Scalar

template<class T> matrix<T>& matrix<T>::operator+=(const T& scalar) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            (*this)[i][j] += scalar;
        }
    }
    return *this;
}

template<class T> matrix<T>& matrix<T>::operator-=(const T& scalar) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            (*this)[i][j] -= scalar;
        }
    }
    return *this;
}

template<class T> matrix<T>& matrix<T>::operator*=(const T& scalar) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            (*this)[i][j] *= scalar;
        }
    }
    return *this;
}

template<class T> matrix<T>& matrix<T>::operator/=(const T& scalar) {
    if (scalar == T()) {
        throw std::logic_error("matrix.divScalar: division by zero");
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            (*this)[i][j] /= scalar;
        }
    }
    return *this;
}

// Matrix

template<class T> matrix<T>& matrix<T>::operator+=(const matrix<T>& other) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            (*this)[i][j] += other[i][j];
        }
    }
    return *this;
}

template<class T> matrix<T>& matrix<T>::operator-=(const matrix<T>& other) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            (*this)[i][j] -= other[i][j];
        }
    }
    return *this;
}

template<class T> matrix<T>& matrix<T>::operator*=(const matrix<T>& other) {
    if (_cols != other._rows) {
        throw std::logic_error("matrix.operator*=: Incompatible dimensions for multiplication");
    }

    matrix<T> result = this->matrixMult(other);
    this->clear();
    for (int i = 0; i < result.rows(); i++) {
        this->push_back(result[i]);
    }
    _rows = result.rows();
    _cols = result.cols();
    return *this;
}

// Other operators

template<class T> matrix<T>& matrix<T>::operator=(const matrix<T>& other) {
    if (this != &other) {
        mathVector<mathVector<T>>::operator=(other);
        _rows = other._rows;
        _cols = other._cols;
    }
    return *this;
}

template<class T> bool matrix<T>::operator==(const matrix<T>& other) {
    return this->isEqual(other);
}

template<class T> bool matrix<T>::operator!=(const matrix<T>& other) {
    return !(this->isEqual(other));
}