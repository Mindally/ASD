#pragma once

#include <iostream>

template <class TKey, class TValue> class ITable {
public:
    virtual ~ITable() = default;

    virtual void insert(const TKey&, const TValue&) = 0;
    virtual void erase(const TKey&) = 0;

    virtual TValue* find(const TKey&) noexcept = 0;

    virtual bool isEmpty() const noexcept = 0;
    virtual bool contains(const TKey&) const noexcept = 0;

    virtual void print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const ITable& table) {
        table.print(out);
        return out;
    }
};