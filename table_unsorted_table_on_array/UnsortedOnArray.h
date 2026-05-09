#pragma once

#include "../interface_itable/ITable.h"
#include "../lib_TVector/TVector.h"

template <class TKey, class TValue> class UnsortedTableOnArray : public ITable<TKey, TValue> {
    TVector<std::pair<TKey, TVal>> _rows;
public:

};