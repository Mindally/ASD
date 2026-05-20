#pragma once

#include "../interface_itable/ITable.h"
#include "../lib_TVector/TVector.h"
#include "../lib_list/List.h"

template<class TKey, class TValue> class UnsortedTableOnList : public ITable<TKey, TValue> {
private:
    List<std::pair<TKey, TValue>> _list;
    auto findKeyIter(const TKey& key);
    auto findKeyIter(const TKey& key) const;
public:
    UnsortedTableOnList() = default;

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;

    TValue* find(const TKey& key) noexcept override;

    inline bool isEmpty() const noexcept override { return _list.isEmpty(); };
    bool contains(const TKey& key) const noexcept override;

    void print(std::ostream& out) const noexcept override;
};

template<class TKey, class TValue> auto UnsortedTableOnList<TKey, TValue>::findKeyIter(const TKey& key) {
    for (auto it = _list.begin(); it != _list.end(); ++it) {
        if ((*it).first == key) return it;
    }
    return _list.end();
}

template<class TKey, class TValue> auto UnsortedTableOnList<TKey, TValue>::findKeyIter(const TKey& key) const {
    for (auto it = _list.begin(); it != _list.end(); ++it) {
        if ((*it).first == key) return it;
    }
    return _list.end();
}

template<class TKey, class TValue> void UnsortedTableOnList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    auto it = findKeyIter(key);
    if (it == _list.end()) {
        _list.pushBack({ key, value });
    }
    else {
        (*it).second = value;
    }
}

template<class TKey, class TValue> void UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) {
    size_t pos = 0;
    for (auto searchIt = _list.begin(); searchIt != _list.end() && (*searchIt).first != key; ++searchIt, ++pos) {
    }
    try {
        _list.erase(pos);
    }
    catch (std::exception e) {
        throw std::logic_error("error");
    }
}

template <class TKey, class TValue> bool UnsortedTableOnList<TKey, TValue>::contains(const TKey& key) const noexcept {
    auto it = findKeyIter(key);
    return it != _list.end();
}

template<class TKey, class TValue> TValue* UnsortedTableOnList<TKey, TValue>::find(const TKey& key) noexcept {
    auto it = findKeyIter(key);
    if (it != _list.end()) {
        return &((*it).second);
    }
    return nullptr;
}

template<class TKey, class TValue> void UnsortedTableOnList<TKey, TValue>::print(std::ostream& out) const noexcept {
    out << "UnsortedTableOnList with " << _list.size() << " rows:" << std::endl;
    for (auto it = _list.begin(); it != _list.end(); ++it) {
        out << "   " << (*it).first << " : " << (*it).second << std::endl;
    }
}