#ifndef LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_

#include "../lib_matrix/matrix.h"

template <typename T>
class triangleMatrix : public matrix<T> {
private:
	size_t _rows;
	size_t _cols;

public:
	triangleMatrix();
	triangleMatrix(size_t rows, size_t cols);
	~triangleMatrix();

	triangleMatrix<T> operator+(triangleMatrix<T>& tr_matrix);
	triangleMatrix<T> operator-(triangleMatrix<T>& tr_matrix);
	triangleMatrix<T> operator*(triangleMatrix<T>& tr_matrix);
};

template <typename T>
triangleMatrix<T>::triangleMatrix() : _rows(0), _cols(0) {
	;
}
template <typename T>
triangleMatrix<T>::triangleMatrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {
	;
}

template <typename T>
triangleMatrix<T>::~triangleMatrix() {
	;
}
template <typename T>
triangleMatrix<T> triangleMatrix<T>::operator+(triangleMatrix<T>& tr_matrix) {
	return triangleMatrix<T>();
}

template <typename T>
triangleMatrix<T> triangleMatrix<T>::operator-(triangleMatrix<T>& tr_matrix) {
	return triangleMatrix<T>();
}

template <typename T>
triangleMatrix<T> triangleMatrix<T>::operator*(triangleMatrix<T>& tr_matrix) {
	return triangleMatrix<T>();
}

#endif  // LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_