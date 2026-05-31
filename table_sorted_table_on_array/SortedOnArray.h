#pragma once

#include "../interface_itable/ITable.h"
#include "../lib_TVector/TVector.h"

template<class TKey, class TValue> class SortedTableOnArray : public ITable<TKey, TValue> {
    TVector<std::pair<TKey, TValue>> _rows;
    int binarySearch(const TKey& key) const noexcept;
    bool tryGetPos(const TKey& key, int& pos) const;
public:
    SortedTableOnArray() = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;

    TValue* find(const TKey&) noexcept override;

    inline const TVector<std::pair<TKey, TValue>>& getRows() const { return _rows; }
    inline bool isEmpty() const noexcept override { return _rows.is_empty(); };
    bool contains(const TKey&) const noexcept override;

    void print(std::ostream&) const override;
};

template <class TKey, class TValue> int SortedTableOnArray<TKey, TValue>::binarySearch(const TKey& key) const noexcept {
    int left = 0;
    int right = static_cast<int>(_rows.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (_rows[mid].first == key) return mid;
        if (_rows[mid].first < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -(left + 1);
}

template <class TKey, class TValue> bool SortedTableOnArray<TKey, TValue>::tryGetPos(const TKey& key, int& pos) const {
    pos = binarySearch(key);
    return pos >= 0;
}

template<class TKey, class TValue> void SortedTableOnArray<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    int pos;
    if (tryGetPos(key, pos)) {
        _rows[pos].second = value;
        return;
    }
    size_t insert_pos = -(pos + 1);
    _rows.insert(insert_pos, { key, value });
}

template<class TKey, class TValue> void SortedTableOnArray<TKey, TValue>::erase(const TKey& key) {
    int pos;
    if (tryGetPos(key, pos)) {
        _rows.erase(pos);
    }
}

template<class TKey, class TValue> bool SortedTableOnArray<TKey, TValue>::contains(const TKey& key) const noexcept {
    return binarySearch(key) >= 0;
}

template<class TKey, class TValue> TValue* SortedTableOnArray<TKey, TValue>::find(const TKey& key) noexcept {
    int pos;
    if (tryGetPos(key, pos)) {
        return &_rows[pos].second;
    }
    return nullptr;
}

template<class TKey, class TValue> void SortedTableOnArray<TKey, TValue>::print(std::ostream& out) const {
    out << "SortedTableOnArray with " << _rows.size() << " rows:" << std::endl;
    for (size_t i = 0; i < _rows.size(); i++) {
        out << " " << i << " " << _rows[i].first << " : " << _rows[i].second << std::endl;
    }
}