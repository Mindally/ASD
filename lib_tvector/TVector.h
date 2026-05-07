// "Copyright 2025 Artem Denisov 3824B1PR2"
#pragma once

#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <initializer_list>

#define CAPACITY 15
#define DELETED_LIMIT 0.15

enum class TVectorElemState { Empty, Busy, Deleted };

template<class T> class TVector {
    T* _data;
    TVectorElemState* _states;
    size_t _size;
    size_t _capacity;
    size_t _deleted;
    bool _is_clean;

public:
    // Constructors
    TVector();
    explicit TVector(size_t);
    TVector(size_t, const T*);
    explicit TVector(std::initializer_list<T>);
    TVector(size_t, std::initializer_list<T>);
    explicit TVector(const TVector<T>&);
    TVector(TVector&&) noexcept;

    // Destructor
    ~TVector();

    // Getters
    bool is_empty() const noexcept { return size() == 0; };
    bool is_full() const noexcept { return size() >= _capacity; };
    inline size_t size() const noexcept { return _size - _deleted; };
    inline size_t capacity() const noexcept { return _capacity; };
    inline T& front() const { return at(0); };
    inline T& back() const { return at(size() - 1); };

    // Functions
    T* to_array() const;

    T& at(size_t) const;
    void emplace(size_t, const T&);
    void assign(const TVector<T>&);

    // Insertion functions
    void push_front(const T&);
    void push_back(const T&);
    void insert(size_t, const T&);

    // Deletion functions
    void pop_front();
    void pop_back();
    void erase(size_t);

    // Memory management functions
    void clear() noexcept;
    void shrink_to_fit();
    void reserve(size_t);
    void resize(size_t);

    // Operators overload
    void operator=(const TVector<T>&);
    TVector& operator=(TVector&&) noexcept;
    bool operator==(const TVector<T>&) const;
    bool operator!=(const TVector<T>&) const;
    T& operator[](size_t) const;

    class Iterator {
        TVector<T>* _vector;
        size_t _current_index;

        void move_to_next_busy() {
            while (_current_index < _vector->_size &&
                _vector->_states[_current_index] != TVectorElemState::Busy) {
                ++_current_index;
            }
        }

        void move_to_prev_busy() {
            while (_current_index > 0 &&
                _current_index != static_cast<size_t>(-1) &&
                _vector->_states[_current_index] != TVectorElemState::Busy) {
                --_current_index;
            }
        }

    public:
        Iterator() : _vector(nullptr), _current_index(0) {}
        Iterator(TVector<T>* vec, size_t index) : _vector(vec), _current_index(index) {
            if (_vector && _current_index < _vector->_size &&
                _vector->_states[_current_index] != TVectorElemState::Busy) {
                move_to_next_busy();
            }
        }

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                _vector = other._vector;
                _current_index = other._current_index;
            }
            return *this;
        }

        Iterator& operator++() {
            ++_current_index;
            move_to_next_busy();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            if (_current_index > 0) {
                --_current_index;
            }
            move_to_prev_busy();
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        Iterator& operator+=(size_t n) {
            for (size_t i = 0; i < n && _current_index < _vector->_size; ++i) {
                ++(*this);
            }
            return *this;
        }

        Iterator& operator-=(size_t n) {
            for (size_t i = 0; i < n && _current_index > 0; ++i) {
                --(*this);
            }
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return _vector == other._vector && _current_index == other._current_index;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        T& operator*() {
            if (_current_index >= _vector->_size ||
                _vector->_states[_current_index] != TVectorElemState::Busy) {
                throw std::out_of_range("TVector.Iterator: dereferencing invalid iterator");
            }
            return _vector->_data[_current_index];
        }

        T* operator->() {
            return &(operator*());
        }
    };

    // Iterator getters
    Iterator begin() {
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this, _size);
    }

    Iterator rbegin() {
        return Iterator(this, _size);
    }

    Iterator rend() {
        return Iterator(this, 0);
    }


private:
    void cleanup();
    size_t translate_index(size_t) const;
    void swap_elements(size_t, size_t);
};

// Realization

// Constructors
template<class T> TVector<T>::TVector() :
    _data(nullptr),
    _states(nullptr),
    _size(0),
    _capacity(CAPACITY),
    _deleted(0),
    _is_clean(true)
{
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    for (size_t i = 0; i < _capacity; i++) _states[i] = TVectorElemState::Empty;
}

template<class T> TVector<T>::TVector(size_t size) :
    _data(nullptr),
    _states(nullptr),
    _size(size),
    _capacity(CAPACITY),
    _deleted(0),
    _is_clean(true)
{
    if (size < 0) throw std::invalid_argument("TVector.size_constructor: Invalid argument 'size' - must be >= 0");
    if (_size == 0) {
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        for (size_t i = 0; i < _capacity; i++) _states[i] = TVectorElemState::Empty;
    }
    else {
        _capacity = _size + CAPACITY;
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        for (size_t i = 0; i < _size; i++) {
            _states[i] = TVectorElemState::Busy;
        }
        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = TVectorElemState::Empty;
        }
    }
}

template<class T> TVector<T>::TVector(size_t size, const T* data) :
    _data(nullptr),
    _states(nullptr),
    _size(size),
    _capacity(size + CAPACITY),
    _deleted(0),
    _is_clean(true)
{
    if (size < 0) {
        throw std::invalid_argument("TVector.sizedata_constructor: Invalid argument 'size' - must be >= 0");
    }
    if (data == nullptr && size > 0) {
        throw std::invalid_argument("TVector.size_constructor: Invalid argument 'data' - is nullptr");
    }
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = data[i];
        _states[i] = TVectorElemState::Busy;
    }
    for (size_t i = _size; i < _capacity; i++) {
        _states[i] = TVectorElemState::Empty;
    }
}

template<class T> TVector<T>::TVector(std::initializer_list<T> init) :
    _data(nullptr),
    _states(nullptr),
    _size(init.size()),
    _capacity(init.size() + CAPACITY),
    _deleted(0),
    _is_clean(true)
{
    if (init.size() > 0) {
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        const T* src = init.begin();
        for (size_t i = 0; i < _size; i++) {
            _data[i] = src[i];
            _states[i] = TVectorElemState::Busy;
        }
        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = TVectorElemState::Empty;
        }
    }
}

template<class T> TVector<T>::TVector(size_t size, std::initializer_list<T> init) :
    _data(nullptr),
    _states(nullptr),
    _size(size),
    _capacity(size + CAPACITY),
    _deleted(0),
    _is_clean(true)
{
    if (size <= 0) {
        throw std::invalid_argument("TVector.sizeinitlist_constructor: Invalid argument 'size' - must be > 0");
    }
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    const T* src = init.begin();
    for (size_t i = 0; i < _size; i++) {
        _data[i] = src[i];
        _states[i] = TVectorElemState::Busy;
    }
    for (size_t i = _size; i < _capacity; i++) {
        _states[i] = TVectorElemState::Empty;
    }
}

template<class T> TVector<T>::TVector(const TVector<T>& other) :
    _data(nullptr),
    _states(nullptr),
    _size(other._size),
    _capacity(other._capacity),
    _deleted(other._deleted),
    _is_clean(other._is_clean)
{
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}

template<class T> TVector<T>::TVector(TVector&& other) noexcept :
    _data(std::exchange(other._data, nullptr)),
    _size(std::exchange(other._size, 0)),
    _capacity(std::exchange(other._capacity, CAPACITY)),
    _deleted(std::exchange(other._deleted, 0)),
    _states(std::exchange(other._states, nullptr)),
    _is_clean(std::exchange(other._is_clean, true))
{

}

// Destructor

template<class T> TVector<T>::~TVector() {
    if (_data != nullptr) {
        delete[] _data;
        delete[] _states;
    }
}

// Functions

template<class T> T* TVector<T>::to_array() const {
    if (size() == 0) {
        return nullptr;
    }
    T* array = new T[size()];
    for (size_t i = 0; i < size(); i++) {
        array[i] = at(i);
    }
    return array;
}

template<class T> T& TVector<T>::at(size_t index) const {
    if (index >= size() || index < 0) {
        throw std::out_of_range("TVector.at: 'index' out of range or vector is empty");
    }
    if (_is_clean) return _data[index];
    else return _data[translate_index(index)];
}

template<class T> void TVector<T>::emplace(size_t index, const T& value) {
    if (index >= size() || index < 0) {
        throw std::out_of_range("TVector.emplace: 'index' out of range or vector is empty");
    }
    at(index) = value;
}

template<class T> void TVector<T>::assign(const TVector<T>& other) {
    delete[] _states;
    delete[] _data;
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _states = new TVectorElemState[_capacity];
    _deleted = other._deleted;
    _is_clean = other._is_clean;
    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}

// Insertion functions
template<class T> void TVector<T>::push_front(const T& value) {
    if (_size == 0) _size++;
    if (_states[0] == TVectorElemState::Busy) {
        _size++;
        if (is_full()) reserve(_size + CAPACITY);
        swap_elements(_size - 1, 0);
    }
    if (_states[0] == TVectorElemState::Deleted) _deleted--;
    if (_size == size()) _is_clean = true;
    _data[0] = value;
    _states[0] = TVectorElemState::Busy;
}

template<class T> void TVector<T>::push_back(const T& value) {
    if (_size == 0) _size++;
    if (_states[_size - 1] == TVectorElemState::Busy) {
        _size++;
        if (is_full()) reserve(_size + CAPACITY);
    }
    if (_states[_size - 1] == TVectorElemState::Deleted) _deleted--;
    if (_size == size()) _is_clean = true;
    _data[_size - 1] = value;
    _states[_size - 1] = TVectorElemState::Busy;
}

template<class T> void TVector<T>::insert(size_t index, const T& value) {
    _size++;
    size_t real_index = translate_index(index);
    if (is_full()) reserve(_size + CAPACITY);
    swap_elements(_size - 1, real_index);
    _data[real_index] = value;
    _states[real_index] = TVectorElemState::Busy;
}

// Deletion functions
template<class T> void TVector<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("TVector.pop_front: Impossible to delete - there are no elements in the vector");
    }
    _states[translate_index(0)] = TVectorElemState::Deleted;
    _deleted++;
    _is_clean = false;
    if (_deleted >= static_cast<size_t>(_size * DELETED_LIMIT)) {
        cleanup();
    }
}

template<class T> void TVector<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("TVector.pop_back: Impossible to delete - there are no elements in the vector");
    }
    size_t index = 0;
    for (int i = _size - 1; i >= 0; i--) {
        if (_states[i] == TVectorElemState::Busy) {
            index = i;
            break;
        }
    }
    _states[index] = TVectorElemState::Empty;
    _size--;
}

template<class T> void TVector<T>::erase(size_t index) {
    if (is_empty()) {
        throw std::logic_error("TVector.erase: Impossible to delete - there are no elements in the vector");
    }
    size_t real_index = translate_index(index);
    if (real_index == size() - 1) {
        pop_back();
        return;
    }
    _states[real_index] = TVectorElemState::Deleted;
    _deleted++;
    _is_clean = false;
    if (_deleted >= static_cast<size_t>(_size * DELETED_LIMIT)) {
        cleanup();
    }
}

// Memory management functions
template<class T> void TVector<T>::clear() noexcept {
    _size = 0;
    _deleted = 0;
    _is_clean = true;
    for (size_t i = 0; i < _capacity; i++) _states[i] = TVectorElemState::Empty;
}

template<class T> void TVector<T>::shrink_to_fit() {
    cleanup();
    if (_size < _capacity) {
        T* new_data = new T[_size];
        TVectorElemState* new_states = new TVectorElemState[_size];
        for (size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = _size;
    }
}

template<class T> void TVector<T>::reserve(size_t new_capacity) {
    cleanup();
    if (new_capacity > _capacity) {
        T* new_data = new T[new_capacity];
        TVectorElemState* new_states = new TVectorElemState[new_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }
        for (size_t i = _capacity; i < new_capacity; i++) new_states[i] = TVectorElemState::Empty;
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = new_capacity;
    }
}

template<class T> void TVector<T>::resize(size_t new_size) {
    if (new_size < 0) {
        throw std::invalid_argument("TVector.resize: Invalid argument 'new_size' - must be >= 0");
    }
    cleanup();
    if (new_size == size()) return;
    if (new_size < size()) {
        for (size_t i = new_size; i < _size; i++) _states[i] = TVectorElemState::Empty;
    }
    else {
        if (new_size >= _capacity) reserve(new_size + CAPACITY);
        for (size_t i = _size; i < new_size; i++) _states[i] = TVectorElemState::Empty;
    }
    _size = new_size;
}


// Operators overload
template <class T> void TVector<T>::operator=(const TVector<T>& other) {
    assign(other);
}

template <class T> TVector<T>& TVector<T>::operator=(TVector&& other) noexcept {
    if (this != &other) {
        delete[] _data;
        delete[] _states;

        _data = std::exchange(other._data, nullptr);
        _size = std::exchange(other._size, 0);
        _capacity = std::exchange(other._capacity, CAPACITY);
        _deleted = std::exchange(other._deleted, 0);
        _states = std::exchange(other._states, nullptr);
        _is_clean = std::exchange(other._is_clean, true);
    }
    return *this;
}

template <class T> bool TVector<T>::operator==(const TVector<T>& other) const {
    if (size() != other.size()) return false;
    if (is_empty()) return true;
    for (int i = 0; i < size(); i++) {
        if (at(i) != other.at(i)) return false;
    }
    return true;
}

template <class T> bool TVector<T>::operator!=(const TVector<T>& other) const {
    return !(*this == other);
}

template <class T> T& TVector<T>::operator[](size_t index) const {
    return at(index);
}

// Private functions
template<class T> void TVector<T>::cleanup() {
    if (_deleted == 0) return;
    _is_clean = true;
    size_t new_size = size();
    size_t index = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == TVectorElemState::Busy) {
            _data[index] = _data[i];
            _states[index] = TVectorElemState::Busy;
            index++;
        }
    }
    for (size_t i = new_size; i < _capacity; i++) _states[i] = TVectorElemState::Empty;
    _size = new_size;
    _deleted = 0;
}

template<class T> size_t TVector<T>::translate_index(size_t index) const {
    if (index < 0 || index >= size()) {
        throw std::out_of_range("TVector: logical index out of range");
    }

    if (_is_clean) {
        return index;
    }

    size_t busy_found = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == TVectorElemState::Busy) {
            if (busy_found == index) {
                return i;
            }
            busy_found++;
        }
    }
    throw std::logic_error("TVector: internal consistency error");
}

template<class T> void TVector<T>::swap_elements(size_t begin, size_t end) {
    for (size_t i = begin; i > end; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];

    }
}

// Friend functions

// Search functions
template <class T> int find_first(const TVector<T>& vector, const T& value) {
    vector.cleanup();
    if (vector.is_empty()) {
        throw std::logic_error("find_first: Impossible to find an element - vector is empty");
    }
    for (int i = 0; i < vector.size(); i++) {
        if (vector.at(i) == value) return i;
    }
    return -1;
}

template <class T> int find_last(const TVector<T>& vector, const T& value) {
    vector.cleanup();
    if (vector.is_empty()) {
        throw std::logic_error("find_last: Impossible to find an element - vector is empty");
    }
    for (int i = vector.size() - 1; i >= 0; i--) {
        if (vector.at(i) == value) return i;
    }
    return -1;
}

template <class T> int* find_all(const TVector<T>& vector, const T& value) {
    vector.cleanup();
    if (vector.is_empty()) {
        throw std::logic_error("find_all: Impossible to find elements - vector is empty");
    }
    int* result = nullptr, size_res = 0;
    for (int i = 0; i < vector.size(); i++) {
        if (vector.at(i) == value) size_res++;
    }

    if (size_res == 0) {
        result = new int[1];
        result[0] = -1;
    }
    else {
        result = new int[size_res];
        for (int i = 0, j = 0; j < size_res; i++) {
            if (vector.at(i) == value) {
                result[j] = i;
                j++;
            }
        }
    }
    return result;
}

// Shuffling

template <class T> void vectorShuffle(TVector<T>& vec) {
    if (vec.size() <= 1) return;
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = vec.size() - 1; i > 0; i--) {
        std::uniform_int_distribution<> distr(0, i);
        int j = distr(gen);
        std::swap(vec[i], vec[j]);
    }
}

template <class T> void vectorShuffle(TVector<T>& vec, std::mt19937& gen) {
    if (vec.size() <= 1) return;
    for (int i = vec.size() - 1; i > 0; i--) {
        std::uniform_int_distribution<> distr(0, i);
        int j = distr(gen);
        std::swap(vec[i], vec[j]);
    }
}
