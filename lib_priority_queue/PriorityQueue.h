#pragma once

#include "../lib_heap/Heap.h"

template <class TKey, class TValue> class PriorityQueue {
    Heap<TKey, TValue> _heap;
public:
    PriorityQueue() = default;
    ~PriorityQueue() = default;

    void add(const TKey&, const TValue&);
    void print() const;

    inline size_t size() const { return _heap.size(); }
    std::pair<TKey, TValue> peek();
    inline std::pair<TKey, TValue> extract() { return _heap.extract(); }
    inline bool isEmpty() const { return _heap.isEmpty(); }

};

template <class TKey, class TValue> void PriorityQueue<TKey, TValue>::add(const TKey& key, const TValue& value) {
    _heap.insert(key, value);
}

template <class TKey, class TValue> void PriorityQueue<TKey, TValue>::print() const {
    _heap.print();
}

template <class TKey, class TValue> std::pair<TKey, TValue> PriorityQueue<TKey, TValue>::peek() {
    if (isEmpty()) {
        throw std::logic_error("PriorityQueue.peek: Queue is empty!");
    }
    return _heap.top();
};