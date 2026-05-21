#pragma once

#include <iostream>

#include "../interface_itable/ITable.h"
#include "../lib_tvector/TVector.h"
#include "../lib_list/List.h"

#define DEFAULT_CHAINED_TABLE_SIZE 100

template <class TValue> class ChainedHashTable : public ITable<std::string, TValue> {
    TVector<List<std::pair<std::string, TValue>>> _rows;
    size_t _size;
    size_t _counter;

    void initializeRows(const size_t&);
    size_t hashFunction(const std::string& key) const noexcept;
public:
    ChainedHashTable();
    ChainedHashTable(size_t);
    ChainedHashTable(const ChainedHashTable&);

    void insert(const std::string&, const TValue&) override;
    void erase(const std::string&) override;

    TValue* find(const std::string&) noexcept override;

    inline bool isEmpty() const noexcept override { return _counter == 0; }
    inline bool isFull() const noexcept { return false; }
    inline size_t size() const noexcept { return _counter; }
    inline size_t capacity() const noexcept { return _size; }
    bool contains(const std::string&) const noexcept override;

    void print(std::ostream& out) const override;
};

template <class TValue> void ChainedHashTable<TValue>::initializeRows(const size_t& size) {
    if (size == 0) {
        throw std::invalid_argument("ChainedHashTable.initializeRows: Size can't be 0!");
    }
    for (size_t i = 0; i < size; i++) {
        _rows.push_back(List<std::pair<std::string, TValue>>());
    }
}

template <class TValue> size_t ChainedHashTable<TValue>::hashFunction(const std::string& key) const noexcept {
    size_t hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash = hash * 31 + key[i];
    }
    return hash % _size;
}

template <class TValue> ChainedHashTable<TValue>::ChainedHashTable() :
    _size(DEFAULT_CHAINED_TABLE_SIZE),
    _counter(0)
{
    initializeRows(_size);
}

template <class TValue>
ChainedHashTable<TValue>::ChainedHashTable(size_t size) :
    _size(size),
    _counter(0)
{
    initializeRows(_size);
}

template <class TValue> ChainedHashTable<TValue>::ChainedHashTable(const ChainedHashTable& other) :
    _rows(other._rows),
    _size(other._size),
    _counter(other._counter)
{

}

template <class TValue> void ChainedHashTable<TValue>::insert(const std::string& key, const TValue& value) {
    size_t hash = hashFunction(key);
    std::pair<std::string, TValue>* found = nullptr;
    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        if (it.getNode()->value.first == key) {
            found = &(it.getNode()->value);
            break;
        }
    }
    if (found) {
        throw std::logic_error("ChainedHashTable.insert: Unable to insert. Key already exists!");
    }
    _rows[hash].pushBack({key, value});
    _counter++;
}

template <class TValue> void ChainedHashTable<TValue>::erase(const std::string& key) {
    size_t hash = hashFunction(key);

    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        if (it.getNode()->value.first == key) {
            _rows[hash].eraseNode(it.getNode());
            _counter--;
            return;
        }
    }
    throw std::logic_error("ChainedHashTable.erase: Unable to erase. Key doesn't exists!");
}

template <class TValue> TValue* ChainedHashTable<TValue>::find(const std::string& key) noexcept {
    size_t hash = hashFunction(key);

    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        if (it.getNode()->value.first == key) {
            return &(it.getNode()->value.second);
        }
    }
    return nullptr;
}

template <class TValue> bool ChainedHashTable<TValue>::contains(const std::string& key) const noexcept {
    size_t hash = hashFunction(key);

    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        if (it.getNode()->value.first == key) {
            return true;
        }
    }
    return false;
}
template <class TValue> void ChainedHashTable<TValue>::print(std::ostream& out) const {
    for (size_t i = 0; i < _rows.size(); i++) {
        for (auto it = _rows[i].begin(); it != _rows[i].end(); ++it) {
            out << it.getNode()->value.first << " : " << it.getNode()->value.second << "\n";
        }
    }
    out << std::endl;
}