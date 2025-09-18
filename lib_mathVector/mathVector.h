#ifndef LIB_MATHVECTOR_MATHVECTORX_H_
#define LIB_MATHVECTOR_MATHVECTORX_H_

#include <iostream>
#include "../lib_TVector/TVector.h"

template <typename T>
class mathVector : private TVector<T> {
private:
    size_t _size;
    TVector<T> data;

public:
    mathVector();
    mathVector(size_t size);
    ~mathVector();

    mathVector<T> operator*(T& val);
    T operator*(mathVector<T>& vec);

    friend std::ostream& operator<<(std::ostream& os, const mathVector<T>& data) {
        return os;
    }
    friend std::istream& operator>>(std::istream& is, const mathVector<T>& data) {
        return is;
    }

private:
};

template <typename T>
mathVector<T>::mathVector() : TVector<T>() { }

template <typename T>
mathVector<T>::~mathVector() { }
template <typename T>
mathVector<T>::mathVector(size_t size) : _size(size) { }

template <typename T>
mathVector<T> mathVector<T>::operator*(T& val) {
    mathVector<T> result(size);
    return *this;
}
template <typename T>
T mathVector<T>::operator*(mathVector<T>& vec) {
    return T();
}

#endif  // LIB_MATHVECTOR_MATHVECTORX_H_