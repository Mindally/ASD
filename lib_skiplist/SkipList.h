#pragma once

#include <iostream>
#include "../lib_tvector/TVector.h"

#define MAX_LVLS 16

namespace skiplist {
    template <class TKey, class TValue> struct Node {
        std::pair<TKey, TValue> data;
        Node** next;

        Node(const TKey& key, const TValue& value, size_t lvl) :
            data({ key, value })
        {
            next = new Node * [lvl + 1];
            for (size_t i = 0; i <= lvl; i++) {
                next[i] = nullptr;
            }
        }

        ~Node() { delete[] next; }
    };
}

template <class TKey, class TValue> class SkipList {
    size_t _maxLevels;
    size_t _curLevel;
    TVector<skiplist::Node<TKey, TValue>*> _heads;

    size_t generateRandomLevel() const;
    skiplist::Node<TKey, TValue>* findNearestNode(const TKey&, TVector<skiplist::Node<TKey, TValue>*>&) const;
public:
    SkipList();
    SkipList(size_t);

    ~SkipList();

    void insert(const TKey&, const TValue&);
    bool remove(const TKey&);
    bool find(const TKey&, TValue&) const;

    void print() const;
};

template <class TKey, class TValue> size_t SkipList<TKey, TValue>::generateRandomLevel() const {
    size_t lvl = 0;
    while (lvl < _maxLevels - 1 && (rand() & 1)) {
        ++lvl;
    }
    return lvl;
}

template <class TKey, class TValue> skiplist::Node<TKey, TValue>* SkipList<TKey, TValue>::findNearestNode(const TKey& key, TVector<skiplist::Node<TKey, TValue>*>& update) const {
    skiplist::Node<TKey, TValue>* current = nullptr;
    for (int lvl = static_cast<int>(_curLevel); lvl >= 0; --lvl) {
        if (current == nullptr) {
            current = _heads[lvl];
        }
        while (current != nullptr && current->next[lvl] != nullptr &&
            current->next[lvl]->data.first < key) {
            current = current->next[lvl];
        }
        if (lvl < static_cast<int>(update.size())) {
            update[lvl] = current;
        }
    }
    return current;
}

template <class TKey, class TValue> SkipList<TKey, TValue>::SkipList() :
    _maxLevels(MAX_LVLS),
    _curLevel(0)
{
    srand(time(nullptr));
    for (int i = 0; i < _maxLevels; i++) {
        _heads.push_back(nullptr);
    }
}

template <class TKey, class TValue> SkipList<TKey, TValue>::SkipList(size_t maxLvls) :
    _maxLevels(maxLvls),
    _curLevel(0)
{
    srand(time(nullptr));
    for (int i = 0; i < _maxLevels; i++) {
        _heads.push_back(nullptr);
    }
}

template <class TKey, class TValue> SkipList<TKey, TValue>::~SkipList() {
    if (_heads.size() > 0 && _heads[0] != nullptr) {
        skiplist::Node<TKey, TValue>* current = _heads[0];
        while (current != nullptr) {
            skiplist::Node<TKey, TValue>* next = current->next[0];
            delete current;
            current = next;
        }
    }
}

template <class TKey, class TValue> void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TVector<skiplist::Node<TKey, TValue>*> update;
    for (size_t i = 0; i <= _maxLevels; i++) {
        update.push_back(nullptr);
    }

    skiplist::Node<TKey, TValue>* current = findNearestNode(key, update);

    if (current != nullptr && current->data.first == key) {
        throw std::logic_error("SkipList.insert: that key already exists");
    }

    size_t newLevel = generateRandomLevel();
    if (newLevel > _curLevel) {
        _curLevel = newLevel;
    }

    skiplist::Node<TKey, TValue>* newNode = new skiplist::Node<TKey, TValue>(key, value, newLevel);

    for (size_t i = 0; i <= newLevel; i++) {
        if (update[i] != nullptr) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
        else {
            newNode->next[i] = _heads[i];
            _heads[i] = newNode;
        }
    }
}

template <class TKey, class TValue> bool SkipList<TKey, TValue>::remove(const TKey& key) {
    TVector<skiplist::Node<TKey, TValue>*> update;
    for (size_t i = 0; i <= _maxLevels; i++) {
        update.push_back(nullptr);
    }

    skiplist::Node<TKey, TValue>* current = findNearestNode(key, update);

    if (current == nullptr || current->data.first != key) {
        return false;
    }

    for (size_t i = 0; i <= _curLevel; i++) {
        if (update[i] != nullptr && update[i]->next[i] == current) {
            update[i]->next[i] = current->next[i];
        }
    }
    delete current;
    while (_curLevel > 0 && _heads[_curLevel] == nullptr) {
        _curLevel--;
    }
    return true;
}

template <class TKey, class TValue> bool SkipList<TKey, TValue>::find(const TKey& key, TValue& value) const {
    TVector<skiplist::Node<TKey, TValue>*> update;
    for (size_t i = 0; i <= _maxLevels; i++) {
        update.push_back(nullptr);
    }
    skiplist::Node<TKey, TValue>* node = findNearestNode(key, update);
    if (node != nullptr && node->data.first == key) {
        value = node->data.second;
        return true;
    }
    return false;
}

template <class TKey, class TValue> void SkipList<TKey, TValue>::print() const {
    TVector<skiplist::Node<TKey, TValue>*> nodes;
    skiplist::Node<TKey, TValue>* current = _heads[0];
    while (current != nullptr) {
        nodes.push_back(current);
        current = current->next[0];
    }

    std::cout << "Index: ";
    for (size_t i = 0; i < nodes.size(); ++i) {
        printf("%5zu ", i);
    }
    std::cout << "\nKey:   ";
    for (auto* node : nodes) {
        printf("%5d ", node->data.first);
    }
    std::cout << "\n";

    for (int lvl = static_cast<int>(_curLevel); lvl >= 0; --lvl) {
        std::cout << "Level " << lvl << ": ";
        for (auto* node : nodes) {
            if (static_cast<size_t>(lvl) <= node->level) {
                std::cout << "  X   ";
            }
            else {
                std::cout << "  .   ";
            }
        }
        std::cout << "\n";
    }
}