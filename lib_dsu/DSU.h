#pragma once

#include <stdexcept>
#include <initializer_list>

template <class T> class DSU {
private:
    T* _parent;
    T* _rank;
    size_t _size;
    void checkIndex(T x) const;
public:
    DSU(size_t);
    DSU(const DSU&);
    ~DSU();

    DSU& operator=(const DSU&);

    void unionSets(T, T);
    T find(T);
    T findRec(T);
    bool isConnected(T, T);

    inline size_t size() const { return _size; };
};

template <class T> void DSU<T>::checkIndex(T x) const {
    if (x < 0 || x >= _size) {
        throw std::out_of_range("DSU.checkInndex:: index out of range");
    }
}

template <class T> DSU<T>::DSU(size_t size) :
    _size(size)
{
    if (size == 0) {
        throw std::invalid_argument("DS.size_constructor: size must be > 0");
    }

    _parent = new T[size];
    _rank = new T[size];

    for (size_t i = 0; i < size; i++) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

template <class T> DSU<T>::DSU(const DSU& other) :
    _size(other._size)
{
    _parent = new T[_size];
    _rank = new T[_size];

    for (size_t i = 0; i < _size; ++i) {
        _parent[i] = other._parent[i];
        _rank[i] = other._rank[i];
    }
}

template <class T> DSU<T>::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

template <class T> DSU<T>& DSU<T>::operator=(const DSU& other) {
    if (this != &other) {
        delete[] _parent;
        delete[] _rank;

        _size = other._size;
        _parent = new T[_size];
        _rank = new T[_size];

        for (size_t i = 0; i < _size; ++i) {
            _parent[i] = other._parent[i];
            _rank[i] = other._rank[i];
        }
    }
    return *this;
}

template <class T> void DSU<T>::unionSets(T x, T y) {
    checkIndex(x);
    checkIndex(y);

    T root_x = find(x);
    T root_y = find(y);

    if (root_x == root_y) return;

    if (_rank[root_x] > _rank[root_y]) {
        _parent[root_y] = root_x;
    }
    else if (_rank[root_x] < _rank[root_y]) {
        _parent[root_x] = root_y;
    }
    else {
        _parent[root_y] = root_x;
        _rank[root_x]++;
    }
}

template <class T> T DSU<T>::find(T x) {
    checkIndex(x);

    T root = x;
    while (root != _parent[root]) {
        root = _parent[root];
    }

    while (x != root) {
        T next = _parent[x];
        _parent[x] = root;
        x = next;
    }

    return root;
}

template <class T> T DSU<T>::findRec(T x) {
    checkIndex(x);

    if (_parent[x] != x) {
        _parent[x] = findRec(_parent[x]);
    }
    return _parent[x];
}

template <class T> bool DSU<T>::isConnected(T x, T y) {
    return find(x) == find(y);
}