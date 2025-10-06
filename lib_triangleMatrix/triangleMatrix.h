#include "../lib_matrix/matrix.h"
#include <iostream>

#pragma once

template<class T> class triangleMatrix : public matrix<T> {
private:
    int _size;

public:
    triangleMatrix();
    explicit triangleMatrix(int);
    triangleMatrix(std::initializer_list<std::initializer_list<T>>);
    triangleMatrix(const triangleMatrix<T>&);

    ~triangleMatrix() = default;

    int getSize() const;

    T& at(int, int);
    mathVector<T>& operator[](int);

    triangleMatrix<T> operator+(const triangleMatrix<T>&) const;
    triangleMatrix<T> operator-(const triangleMatrix<T>&) const;
    triangleMatrix<T> operator*(const triangleMatrix<T>&) const;
    triangleMatrix<T> operator*(const T&) const;
    mathVector<T> operator*(const mathVector<T>&) const;

    triangleMatrix<T>& operator=(const triangleMatrix<T>&);

    template<class U> friend matrix<U> operator+(const matrix<U>&, const triangleMatrix<U>&);

    template<class U> friend matrix<U> operator+(const triangleMatrix<U>&, const matrix<U>&);

    template<class U> friend matrix<U> operator*(const matrix<U>&, const triangleMatrix<U>&);

    template<class U> friend matrix<U> operator*(const triangleMatrix<U>&, const matrix<U>&);

private:
    void initializeUpperTriangular();
    bool isValidTriangleIndex(int, int) const;
};

template<class T> std::ostream& operator<<(std::ostream& os, const triangleMatrix<T>& matrix);

template<class T> matrix<T> operator+(const matrix<T>& mat, const triangleMatrix<T>& triMat);

template<class T> matrix<T> operator+(const triangleMatrix<T>& triMat, const matrix<T>& mat);

template<class T> matrix<T> operator-(const matrix<T>& mat, const triangleMatrix<T>& triMat);

template<class T> matrix<T> operator-(const triangleMatrix<T>& triMat, const matrix<T>& mat);

template<class T> matrix<T> operator*(const matrix<T>& mat, const triangleMatrix<T>& triMat);

template<class T> matrix<T> operator*(const triangleMatrix<T>& triMat, const matrix<T>& mat);



template<class T> triangleMatrix<T>::triangleMatrix() :
    matrix<T>(),
    _size(0)
{

}

template<class T> triangleMatrix<T>::triangleMatrix(int size) :
    matrix<T>(size, size),
    _size(size) 
{
    initializeUpperTriangular();
}

template<class T> triangleMatrix<T>::triangleMatrix(std::initializer_list<std::initializer_list<T>> init) :
    matrix<T>(init),
    _size(init.size())
{
    if (this->rows() != this->cols()) {
        throw std::invalid_argument("triangleMatrix: Must be square matrix");
    }
    initializeUpperTriangular();
}

template<class T> triangleMatrix<T>::triangleMatrix(const triangleMatrix<T>& other) :
    matrix<T>(other),
    _size(other._size)
{

}

template<class T> int triangleMatrix<T>::getSize() const {
    return _size;
}

template<class T>
void triangleMatrix<T>::initializeUpperTriangular() {
    for (int i = 1; i < _size; i++) {
        for (int j = 0; j < i; j++) {
            this->matrix<T>::at(i, j) = T();
        }
    }
}

template<class T>
bool triangleMatrix<T>::isValidTriangleIndex(int row, int col) const {
    return row >= 0 && row < _size && col >= 0 && col < _size && row <= col;
}

template<class T> T& triangleMatrix<T>::at(int row, int col) {
    if (row < 0 || row >= _size || col < 0 || col >= _size) {
        throw std::out_of_range("triangleMatrix.at: Index out of range");
    }

    if (row > col) {
        throw std::invalid_argument("triangleMatrix.at: Cannot modify lower triangular elements");
    }
    return this->matrix<T>::at(row, col);
}

template<class T> mathVector<T>& triangleMatrix<T>::operator[](int row) {
    return this->matrix<T>::operator[](row);
}



template<class T> triangleMatrix<T> triangleMatrix<T>::operator+(const triangleMatrix<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("triangleMatrix.operator+: Matrices must have same size");
    }

    triangleMatrix<T> result(_size);
    for (int i = 0; i < _size; i++) {
        for (int j = i; j < _size; j++) {
            result.at(i, j) = this->at(i, j) + other.at(i, j);
        }
    }
    return result;
}

template<class T> triangleMatrix<T> triangleMatrix<T>::operator-(const triangleMatrix<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("triangleMatrix::operator-: Matrices must have same size");
    }

    triangleMatrix<T> result(_size);
    for (int i = 0; i < _size; i++) {
        for (int j = i; j < _size; j++) {
            result.at(i, j) = this->at(i, j) - other.at(i, j);
        }
    }
    return result;
}

template<class T> triangleMatrix<T> triangleMatrix<T>::operator*(const triangleMatrix<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("triangleMatrix.operator*: Matrices must have same size");
    }

    triangleMatrix<T> result(_size);
    for (int i = 0; i < _size; i++) {
        for (int j = i; j < _size; j++) {
            T sum = T();
            for (int k = i; k <= j; k++) {
                sum += this->at(i, k) * other.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

template<class T>
triangleMatrix<T> triangleMatrix<T>::operator*(const T& scalar) const {
    triangleMatrix<T> result(_size);
    for (int i = 0; i < _size; i++) {
        for (int j = i; j < _size; j++) {
            result.at(i, j) = this->at(i, j) * scalar;
        }
    }
    return result;
}

template<class T> mathVector<T> triangleMatrix<T>::operator*(const mathVector<T>& vec) const {
    if (_size != vec.size()) {
        throw std::invalid_argument("triangleMatrix.operator*: Vector size must match matrix size");
    }
    mathVector<T> result(_size);
    for (int i = 0; i < _size; i++) {
        T sum = T();
        for (int j = i; j < _size; j++) {
            sum += this->at(i, j) * vec[j];
        }
        result[i] = sum;
    }
    return result;
}

template<class T>
triangleMatrix<T>& triangleMatrix<T>::operator=(const triangleMatrix<T>& other) {
    if (this != &other) {
        matrix<T>::operator=(other);
        _size = other._size;
    }
    return *this;
}

template<class T> std::ostream& operator<<(std::ostream& os, const triangleMatrix<T>& matrix) {
    for (int i = 0; i < matrix.getSize(); i++) {
        os << "[ ";
        for (int j = 0; j < matrix.getSize(); j++) {
            os << matrix.at(i, j);
            if (j < matrix.getSize() - 1) os << " ";
        }
        os << " ]" << std::endl;
    }
    return os;
}

template<class T>
matrix<T> operator+(const matrix<T>& mat, const triangleMatrix<T>& triMat) {
    if (mat.rows() != triMat.getSize() || mat.cols() != triMat.getSize()) {
        throw std::invalid_argument("operator+: Matrix dimensions must match");
    }

    matrix<T> result(mat.rows(), mat.cols());
    for (int i = 0; i < mat.rows(); i++) {
        for (int j = 0; j < mat.cols(); j++) {
            result.at(i, j) = mat.at(i, j) + triMat.at(i, j);
        }
    }
    return result;
}

template<class T> matrix<T> operator+(const triangleMatrix<T>& triMat, const matrix<T>& mat) {
    return mat + triMat;
}

template<class T> matrix<T> operator-(const matrix<T>& mat, const triangleMatrix<T>& triMat) {
    if (mat.rows() != triMat.getSize() || mat.cols() != triMat.getSize()) {
        throw std::invalid_argument("operator-: Matrix dimensions must match");
    }

    matrix<T> result(mat.rows(), mat.cols());
    for (int i = 0; i < mat.rows(); i++) {
        for (int j = 0; j < mat.cols(); j++) {
            result.at(i, j) = mat.at(i, j) - triMat.at(i, j);
        }
    }
    return result;
}

template<class T> matrix<T> operator-(const triangleMatrix<T>& triMat, const matrix<T>& mat) {
    if (triMat.getSize() != mat.rows() || triMat.getSize() != mat.cols()) {
        throw std::invalid_argument("operator-: Matrix dimensions must match");
    }

    matrix<T> result(triMat.getSize(), triMat.getSize());
    for (int i = 0; i < triMat.getSize(); i++) {
        for (int j = 0; j < triMat.getSize(); j++) {
            result.at(i, j) = triMat.at(i, j) - mat.at(i, j);
        }
    }
    return result;
}

template<class T> matrix<T> operator*(const matrix<T>& mat, const triangleMatrix<T>& triMat) {
    if (mat.cols() != triMat.getSize()) {
        throw std::invalid_argument("operator*: Incompatible dimensions for multiplication");
    }

    matrix<T> result(mat.rows(), triMat.getSize());
    for (int i = 0; i < mat.rows(); i++) {
        for (int j = 0; j < triMat.getSize(); j++) {
            T sum = T();
            for (int k = 0; k < mat.cols(); k++) {
                sum += mat.at(i, k) * triMat.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

template<class T> matrix<T> operator*(const triangleMatrix<T>& triMat, const matrix<T>& mat) {
    if (triMat.getSize() != mat.rows()) {
        throw std::invalid_argument("operator*: Incompatible dimensions for multiplication");
    }

    matrix<T> result(triMat.getSize(), mat.cols());
    for (int i = 0; i < triMat.getSize(); i++) {
        for (int j = 0; j < mat.cols(); j++) {
            T sum = T();
            for (int k = i; k < triMat.getSize(); k++) {
                sum += triMat.at(i, k) * mat.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}