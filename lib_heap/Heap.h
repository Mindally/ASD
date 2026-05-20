#pragma once

#include <iostream>

#include "../lib_tvector/TVector.h"

template <class TKey, class TValue> class Heap {
    TVector<std::tuple<TKey, size_t, TValue>> _data;
    size_t _counter;
    bool isMostProfitableElement(size_t, size_t) noexcept;
public:
    Heap();

    void insert(const TKey& key, const TValue& value) noexcept;
    void ascend() noexcept;
    void descend() noexcept;
    std::pair<TKey, TValue> extract();

    void print() const noexcept;

    inline size_t size() const { return _data.size(); }
    std::pair<TKey, TValue> top() const;
    inline bool isEmpty() const { return _data.is_empty(); }
};

template <class TKey, class TValue>Heap<TKey, TValue>::Heap() :
    _counter(0)
{

}

template <class TKey, class TValue> void Heap<TKey, TValue>::insert(const TKey& key, const TValue& value) noexcept {
    _counter++;
    _data.push_back({ key, _counter, value });
    ascend();
}

template <class TKey, class TValue> void Heap<TKey, TValue>::ascend() noexcept {
    size_t index = _data.size() - 1;
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (std::get<0>(_data[parent]) > std::get<0>(_data[index]) ||
            (std::get<0>(_data[parent]) == std::get<0>(_data[index]) &&
                std::get<1>(_data[parent]) > std::get<1>(_data[index]))) {
            std::swap(_data[parent], _data[index]);
            index = parent;
        }
        else {
            break;
        }
    }
}

template <class TKey, class TValue> void Heap<TKey, TValue>::descend() noexcept {
    if (isEmpty()) return;

    size_t index = 0;
    size_t size = _data.size();

    while (true) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t smallest = index;

        if (left < size && isMostProfitableElement(left, smallest)) {
            smallest = left;
        }
        if (right < size && isMostProfitableElement(right, smallest)) {
            smallest = right;
        }
        if (smallest != index) {
            std::swap(_data[index], _data[smallest]);
            index = smallest;
        }
        else {
            break;
        }
    }
}

template <class TKey, class TValue> std::pair<TKey, TValue> Heap<TKey, TValue>::extract() {
    if (_data.is_empty()) {
        throw std::logic_error("Heap.extract: Unable to extract. Heap is empty!");
    }

    std::pair<TKey, TValue> result = { std::get<0>(_data[0]), std::get<2>(_data[0]) };

    _data[0] = _data.back();
    _data.pop_back();

    if (!isEmpty()) descend();

    return result;
}

template <class TKey, class TValue> void Heap<TKey, TValue>::print() const noexcept {
    if (isEmpty()) {
        return;
    }
    for (size_t i = 0; i < _data.size(); i++) {
        std::cout << std::get<0>(_data[i]) << ":" << std::get<2>(_data[i]);
        if (i != _data.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
}

template <class TKey, class TValue> std::pair<TKey, TValue> Heap<TKey, TValue>::top() const {
    if (isEmpty()) {
        throw std::logic_error("Heap.top: Unable to get top element. Heap is empty!");
    }
    return { std::get<0>(_data[0]), std::get<2>(_data[0]) };
}

template <class TKey, class TValue> bool Heap<TKey, TValue>::isMostProfitableElement(size_t first, size_t second) noexcept {
    TKey firstKey = std::get<0>(_data[first]);
    TKey secondKey = std::get<0>(_data[second]);
    if (firstKey != secondKey) return firstKey < secondKey;
    return std::get<1>(_data[first]) < std::get<1>(_data[second]);
}