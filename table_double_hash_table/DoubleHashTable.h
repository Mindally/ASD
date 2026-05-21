#pragma once

#include <iostream>

#include "../interface_itable/ITable.h"
#include "../lib_tvector/TVector.h"

#define DEFAULT_TABLE_SIZE 100
#define STEP_DENOMINATOR 15

namespace support_functions {
    size_t gcd(size_t a, size_t b) {
        while (b != 0) {
            size_t t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    bool isMutuallyPrime(size_t a, size_t b) {
        return gcd(a, b) == 1;
    }
}

template <class TValue> class DoubleHashTable : public ITable<std::string, TValue> {
    enum class EntryStatus { Empty, Busy, Deleted };

    TVector<std::tuple<EntryStatus, std::string, TValue>> _rows;
    size_t _size;
    size_t _step;
    size_t _counter;

    void determineStepLength(const size_t&, const size_t&);
    size_t firstHashFunction(const std::string&) const noexcept;
    inline size_t secondHashFunction(const size_t& hash) const noexcept { return (hash + _step) % _size; }
public:
    DoubleHashTable();
    DoubleHashTable(size_t);
    DoubleHashTable(const DoubleHashTable&);

    void insert(const std::string&, const TValue&) override;
    void erase(const std::string&) override;

    TValue* find(const std::string&) noexcept override;

    inline bool isEmpty() const noexcept override { return _counter == 0; }
    inline bool isFull() const noexcept { return _counter == _size; }
    inline size_t size() const noexcept { return _counter; }
    inline size_t capacity() const noexcept { return _size; }
    bool contains(const std::string&) const noexcept override;

    void print(std::ostream&) const override;
};

template <class TValue> void DoubleHashTable<TValue>::determineStepLength(const size_t& size, const size_t& stepDenom) {
    if (stepDenom < 3) {
        throw std::invalid_argument("DoubleHashTable.determineStepLength: Please make table at least 3 elements long!");
    }
    int upperLimit = static_cast<int>(size / stepDenom);
    for (size_t i = std::max(2, upperLimit); i < size; i++) {
        if (support_functions::isMutuallyPrime(i, size)) {
            _step = i;
            return;
        }
    }
    throw std::logic_error("DoubleHashTable.determineStepLength: Step hasn't been determined!");
}

template <class TValue> size_t DoubleHashTable<TValue>::firstHashFunction(const std::string& key) const noexcept {
    size_t hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash = hash * 31 + key[i];
    }
    return hash % _size;
}

template <class TValue> DoubleHashTable<TValue>::DoubleHashTable() :
    _size(DEFAULT_TABLE_SIZE),
    _counter(0) 
{
    determineStepLength(_size, STEP_DENOMINATOR);
    _rows.resize(_size);
}

template <class TValue> DoubleHashTable<TValue>::DoubleHashTable(size_t size) :
    _size(size),
    _counter(0)
{
    determineStepLength(_size, STEP_DENOMINATOR);
    _rows.resize(_size);
}

template <class TValue> DoubleHashTable<TValue>::DoubleHashTable(const DoubleHashTable& other) :
    _rows(other._rows),
    _size(other._size),
    _step(other._step),
    _counter(other._counter)
{

}

template <class TValue> void DoubleHashTable<TValue>::insert(const std::string& key, const TValue& value) {
    size_t hash = firstHashFunction(key);
    
    for (size_t i = 0; i < _size; i++) {
        if (std::get<0>(_rows[hash]) != EntryStatus::Busy) {
            _rows[hash] = std::make_tuple(EntryStatus::Busy, key, value);
            _counter++;
            return;
        }
        if (std::get<0>(_rows[hash]) == EntryStatus::Busy && std::get<1>(_rows[hash]) == key) {
            throw std::logic_error("DoubleHashTable.insert: key already exists!");
        }
        hash = secondHashFunction(hash);
    }
    throw std::logic_error("DoubleHashTable.insert: table is full (no free slots)!");
}

template <class TValue> void DoubleHashTable<TValue>::erase(const std::string& key) {
    size_t hash = firstHashFunction(key);

    if (std::get<0>(_rows[hash]) == EntryStatus::Empty) {
        throw std::logic_error("DoubleHashTable.erase: Unable to erase. This key doesn't exists!");
    }

    for (size_t i = 0; i < _size; i++) {
        if (std::get<0>(_rows[hash]) == EntryStatus::Busy && std::get<1>(_rows[hash]) == key) {
            std::get<0>(_rows[hash]) = EntryStatus::Deleted;
            _counter--;
            return;
        }
        hash = secondHashFunction(hash);
    }
    throw std::logic_error("DoubleHashTable.erase: Unable to erase!");
}

template <class TValue> TValue* DoubleHashTable<TValue>::find(const std::string& key) noexcept {
    size_t hash = firstHashFunction(key);

    for (size_t i = 0; i < _size; i++) {
        if (std::get<0>(_rows[hash]) == EntryStatus::Empty) {
            return nullptr;
        }

        if (std::get<0>(_rows[hash]) == EntryStatus::Busy && std::get<1>(_rows[hash]) == key) {
            return &(std::get<2>(_rows[hash]));
        }
        hash = secondHashFunction(hash);
    }
    return nullptr;
}

template <class TValue> bool DoubleHashTable<TValue>::contains(const std::string& key) const noexcept {
    size_t hash = firstHashFunction(key);

    for (size_t i = 0; i < _size; i++) {
        if (std::get<0>(_rows[hash]) == EntryStatus::Empty) {
            return false;
        }

        if (std::get<0>(_rows[hash]) == EntryStatus::Busy && std::get<1>(_rows[hash]) == key) {
            return true;
        }
        hash = secondHashFunction(hash);
    }
    return false;
}

template <class TValue> void DoubleHashTable<TValue>::print(std::ostream& out) const {
    for (size_t i = 0; i < _size; i++) {
        if (std::get<0>(_rows[i]) == EntryStatus::Busy) {
            out << std::get<1>(_rows[i]) << " : " << std::get<2>(_rows[i]) << "\n";
        }
    }
    std::cout << std::endl;
}