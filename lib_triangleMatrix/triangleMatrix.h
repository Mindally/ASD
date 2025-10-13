#pragma once

#include <iostream>
#include "../lib_matrix/matrix.h"

template<class T> class triangleMatrix : public matrix<T> {
private:
    bool _isUpper;

public:
    // Constructors
    triangleMatrix();
    triangleMatrix(int size, bool isUpper = true);
    triangleMatrix(const triangleMatrix<T>& other);
    triangleMatrix(const matrix<T>& other, bool isUpper = true);
    triangleMatrix(std::initializer_list<std::initializer_list<T>> init, bool isUpper = true);

    // Math functions
    triangleMatrix<T> addScalar(const T& scalar) const;
    triangleMatrix<T> subScalar(const T& scalar) const;
    triangleMatrix<T> multScalar(const T& scalar) const;
    triangleMatrix<T> divScalar(const T& scalar) const;

    triangleMatrix<T> add(const triangleMatrix<T>& other) const;
    triangleMatrix<T> sub(const triangleMatrix<T>& other) const;
    triangleMatrix<T> mult(const triangleMatrix<T>& other) const;

    // Other functions
    triangleMatrix<T> transpose() const;
    void print() const;

    // Getters
    int size() const;
    bool isUpper() const;

    // Operators
    triangleMatrix<T> operator+(const T& scalar) const;
    triangleMatrix<T> operator-(const T& scalar) const;
    triangleMatrix<T> operator*(const T& scalar) const;
    triangleMatrix<T> operator/(const T& scalar) const;
    triangleMatrix<T> operator+(const triangleMatrix<T>& other) const;
    triangleMatrix<T> operator-(const triangleMatrix<T>& other) const;
    triangleMatrix<T> operator*(const triangleMatrix<T>& other) const;

    // Other operators
    triangleMatrix<T>& operator=(const triangleMatrix<T>&);
};

// Constructors

template<class T>
triangleMatrix<T>::triangleMatrix() : matrix<T>(), _isUpper(true) {}

template<class T>
triangleMatrix<T>::triangleMatrix(int size, bool isUpper) :
    matrix<T>(size, size), _isUpper(isUpper)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((isUpper && i > j) || (!isUpper && i < j)) {
                (*this)[i][j] = T();
            }
        }
    }
}

template<class T>
triangleMatrix<T>::triangleMatrix(const triangleMatrix<T>& other) :
    matrix<T>(other), _isUpper(other._isUpper)
{}

template<class T>
triangleMatrix<T>::triangleMatrix(const matrix<T>& other, bool isUpper) :
    matrix<T>(other), _isUpper(isUpper)
{
    for (int i = 0; i < this->rows(); i++) {
        for (int j = 0; j < this->cols(); j++) {
            if ((isUpper && i > j && (*this)[i][j] != T()) ||
                (!isUpper && i < j && (*this)[i][j] != T())) {
                throw std::invalid_argument("triangleMatrix: matrix is not triangular");
            }
        }
    }
}

template<class T>
triangleMatrix<T>::triangleMatrix(std::initializer_list<std::initializer_list<T>> init, bool isUpper) :
    _isUpper(isUpper)
{
    int rows = static_cast<int>(init.size());
    if (rows == 0) {
        this->_rows = 0;
        this->_cols = 0;
        return;
    }

    int cols = static_cast<int>(init.begin()->size());
    if (rows != cols) {
        throw std::invalid_argument("triangleMatrix: Triangular matrix must be square");
    }

    this->_rows = rows;
    this->_cols = cols;

    for (auto& row : init) {
        this->push_back(mathVector<T>(row));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((isUpper && i > j) || (!isUpper && i < j)) {
                if ((*this)[i][j] != T()) {
                    throw std::invalid_argument("triangleMatrix: Initializer list does not represent a triangular matrix");
                }
            }
        }
    }
}

// Math functions

template<class T>
triangleMatrix<T> triangleMatrix<T>::addScalar(const T& scalar) const {
    triangleMatrix<T> result(this->size(), _isUpper);

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            if ((_isUpper && i <= j) || (!_isUpper && i >= j)) {
                result[i][j] = (*this)[i][j] + scalar;
            }
        }
    }
    return result;
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::subScalar(const T& scalar) const {
    triangleMatrix<T> result(this->size(), _isUpper);

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            if ((_isUpper && i <= j) || (!_isUpper && i >= j)) {
                result[i][j] = (*this)[i][j] - scalar;
            }
        }
    }
    return result;
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::multScalar(const T& scalar) const {
    triangleMatrix<T> result(this->size(), _isUpper);

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            if ((_isUpper && i <= j) || (!_isUpper && i >= j)) {
                result[i][j] = (*this)[i][j] * scalar;
            }
        }
    }
    return result;
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::divScalar(const T& scalar) const {
    if (scalar == T()) {
        throw std::logic_error("triangleMatrix.divScalar: Division by zero");
    }

    triangleMatrix<T> result(this->size(), _isUpper);
    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            if ((_isUpper && i <= j) || (!_isUpper && i >= j)) {
                result[i][j] = (*this)[i][j] / scalar;
            }
        }
    }
    return result;
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::add(const triangleMatrix<T>& other) const {
    if (this->size() != other.size() || _isUpper != other._isUpper) {
        throw std::logic_error("triangleMatrix.add: Matrices must have same dimensions and type");
    }

    triangleMatrix<T> result(this->size(), _isUpper);
    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            if ((_isUpper && i <= j) || (!_isUpper && i >= j)) {
                result[i][j] = (*this)[i][j] + other[i][j];
            }
        }
    }
    return result;
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::sub(const triangleMatrix<T>& other) const {
    if (this->size() != other.size() || _isUpper != other._isUpper) {
        throw std::logic_error("triangleMatrix.sub: Matrices must have same dimensions and type");
    }

    triangleMatrix<T> result(this->size(), _isUpper);
    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            if ((_isUpper && i <= j) || (!_isUpper && i >= j)) {
                result[i][j] = (*this)[i][j] - other[i][j];
            }
        }
    }
    return result;
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::mult(const triangleMatrix<T>& other) const {
    if (this->size() != other.size()) {
        throw std::logic_error("triangleMatrix.mult: Matrices must have same dimensions");
    }

    if (_isUpper != other._isUpper) {
        throw std::logic_error("triangleMatrix.mult: Matrices must be of the same type (both upper or both lower)");
    }

    triangleMatrix<T> result(this->size(), _isUpper);

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            if ((_isUpper && i <= j) || (!_isUpper && i >= j)) {
                T sum = T();
                for (int k = 0; k < this->size(); k++) {
                    sum += (*this)[i][k] * other[k][j];
                }
                result[i][j] = sum;
            }
        }
    }
    return result;
}

// Other functions

template<class T>
triangleMatrix<T> triangleMatrix<T>::transpose() const {
    triangleMatrix<T> result(this->size(), !_isUpper);
    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            result[j][i] = (*this)[i][j];
        }
    }
    return result;
}

template<class T>
int triangleMatrix<T>::size() const {
    return this->rows();
}

template<class T>
bool triangleMatrix<T>::isUpper() const {
    return _isUpper;
}

// Operators

template<class T>
triangleMatrix<T> triangleMatrix<T>::operator+(const T& scalar) const {
    return this->addScalar(scalar);
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::operator-(const T& scalar) const {
    return this->subScalar(scalar);
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::operator*(const T& scalar) const {
    return this->multScalar(scalar);
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::operator/(const T& scalar) const {
    return this->divScalar(scalar);
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::operator+(const triangleMatrix<T>& other) const {
    return this->add(other);
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::operator-(const triangleMatrix<T>& other) const {
    return this->sub(other);
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::operator*(const triangleMatrix<T>& other) const {
    return this->mult(other);
}

// Other operators
template<class T>
triangleMatrix<T>& triangleMatrix<T>::operator=(const triangleMatrix<T>& other) {
    if (this != &other) {
        matrix<T>::operator=(other);
        _isUpper = other._isUpper;
    }
    return *this;
}