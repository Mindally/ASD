#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include <iostream>

#include "../lib_mathVector/mathVector.h"

template <typename T>
class matrix : public mathVector<mathVector<T>> {
private:
    size_t _rows;
    size_t _cols;

public:
    matrix();
    matrix(size_t rows, size_t cols);
    ~matrix();
    matrix(const mathVector<mathVector<T>>&);
    matrix(const matrix&);

    matrix<T> operator+(const matrix& other);
    matrix<T> operator-(const matrix& other);

    matrix<T> operator*(const T val);
    mathVector<T> operator*(const mathVector<T>& vec);

    friend mathVector<T> operator*(const mathVector<T>& vec,
        const matrix<T>& matrix) {
        return mathVector<T>();
    }

    matrix<T> operator*(const matrix<T>& matr);

    friend std::ostream& operator<<(std::ostream& os, const matrix<T>& data) {
        return os;
    }
    friend std::istream& operator>>(std::istream& is, matrix<T>& data) {
        return is;
    }
};

template <typename T>
matrix<T>::matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {}

template <typename T>
matrix<T>::matrix() : _rows(0), _cols(0) {
    ;
}

template <typename T>
matrix<T>::~matrix() {
    ;
}

template <typename T>
matrix<T>::matrix(const mathVector<mathVector<T>>&) {
    ;
}

template <typename T>
matrix<T>::matrix(const matrix&) {
    ;
}

template <typename T>
matrix<T> matrix<T>::operator+(const matrix& other) {
    return matrix<T>();
}

template <typename T>
matrix<T> matrix<T>::operator-(const matrix& other) {
    return matrix<T>();
}

template <typename T>
matrix<T> matrix<T>::operator*(const T val) {
    return matrix<T>();
}

template <typename T>
mathVector<T> matrix<T>::operator*(const mathVector<T>& vec) {
    return mathVector<T>();
}

template <typename T>
matrix<T> matrix<T>::operator*(const matrix<T>& matr) {
    return matrix();
}
#endif  // LIB_MATRIX_MATRIX_H_