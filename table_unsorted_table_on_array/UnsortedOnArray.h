#pragma once

#include "../interface_itable/ITable.h"
#include "../lib_TVector/TVector.h"

template<class TKey, class TValue> class UnsortedTableOnArray : public ITable<TKey, TValue> {
    TVector<std::pair<TKey, TValue>> _rows;
public:
    UnsortedTableOnArray() = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;

    TValue* find(const TKey&) noexcept override;

    inline bool isEmpty() const noexcept override { return _rows.is_empty(); };
    bool contains(const TKey&) const noexcept override;

    void print(std::ostream&) const override;
private:
    int keyExistsPos(const TKey&) const noexcept;
};

template<class TKey, class TValue> void UnsortedTableOnArray<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    int pos = keyExistsPos(key);
    if (pos == -1) {
        _rows.push_back({ key, value });
    }
    else {
        _rows[pos].second = value;
    }
}

template<class TKey, class TValue> void UnsortedTableOnArray<TKey, TValue>::erase(const TKey& key) {
    int pos = keyExistsPos(key);
    if (pos != -1) {
        _rows.erase(pos);
    }
}

template<class TKey, class TValue> bool UnsortedTableOnArray<TKey, TValue>::contains(const TKey& key) const noexcept {
    int pos = keyExistsPos(key);
    if (pos != -1) {
        return true;
    }
    else {
        return false;
    }
}

template<class TKey, class TValue> TValue* UnsortedTableOnArray<TKey, TValue>::find(const TKey& key) noexcept {
    int pos = keyExistsPos(key);
    if (pos != -1) {
        return &_rows[pos].second;
    }
    else {
        return nullptr;
    }
}

template<class TKey, class TValue> void UnsortedTableOnArray<TKey, TValue>::print(std::ostream& out) const {
    out << "UnsortedTableOnArray with " << _rows.size() << " rows:" << std::endl;
    for (size_t i = 0; i < _rows.size(); i++) {
        out << " " << i << " " << _rows[i].first << " : " << _rows[i].second << std::endl;
    }
}

template<class TKey, class TValue> int UnsortedTableOnArray<TKey, TValue>::keyExistsPos(const TKey& key) const noexcept {
    for (size_t i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            return i;
        }
    }
    return -1;
}