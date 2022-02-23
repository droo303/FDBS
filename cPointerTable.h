//
// Created by pkozusnik on 20.02.22.
//

#ifndef FDBS_CPOINTERTABLE_H
#define FDBS_CPOINTERTABLE_H

#pragma once

#include <assert.h>
#include <stdlib.h>
#include <iostream>

template<class TKey, class TData>
class cRecord
{
    TKey tkey;
    TData data;

    cRecord(TKey tKey, TData tData){
        this->tkey = tKey;
        this->data = tData;
    }
    ~cRecord() {
        this->data = nullptr;
        this->tkey = nullptr;
    }
};


template<class TKey, class TData>
class cPointerTable
{
private:
    int mCapacity;
    int mCount;

    cRecord<TKey, TData>** mData = new cRecord<TKey, TData>* [100000];
private:
    inline char* GetRowPointer(int rowId) const;

public:
    cPointerTable(int capacity);
    ~cPointerTable();

    bool Add(const TKey &key, const TData &data);
    bool Get(int rowId, TKey &key, TData &data) const;
    bool Find ( const TKey &key , TData &data ) const;

};

template<class TKey, class TData>
cPointerTable<TKey, TData>::cPointerTable(int capacity)
{
    mCapacity = capacity;
    mCount = 0;
    mData = new char[mRowSize * capacity];
}

template<class TKey, class TData>
cPointerTable<TKey, TData>::~cPointerTable()
{
    if (mData != NULL)
    {
        delete mData;
        mData = NULL;
        mCapacity = 0;
        mCount = 0;
    }
}

template<class TKey, class TData>
inline char* cPointerTable<TKey, TData>::GetRowPointer(int rowId) const
{
    return mData + rowId * mRowSize;
}

template<class TKey, class TData>
bool cPointerTable<TKey, TData>::Get(int rowId, TKey &key, TData &data) const
{

    bool ret = false;
    assert(rowId >= 0 && rowId < mCount);
    ret = true;

    char* p = GetRowPointer(rowId);
    key = *((TKey*)p);
    data = *((TData*)(p + sizeof(TKey)));

    return ret;
}

template<class TKey, class TData>
bool cPointerTable<TKey, TData>::Add(const TKey &key, const TData &data)
{
    bool ret = false;
    assert(mCapacity > mCount);

    // get pointer to empty place according to count already in
    char* p = mData + mRowSize * mCount;
    // insert key
    *(TKey*)p = key;
    // move pointer by the size of key
    p += sizeof (TKey);
    // insert data
    *(TData*)p = data;
    // increment count
    mCount++;

    ret = true;
    return ret;
}

template<class TKey, class TData>
bool cPointerTable<TKey, TData>::Find(const TKey &key, TData &data) const {
    bool ret = false;

    TKey found_key = 0;
    TData found_data = 0;
    int row_id = 0;
    char* p = GetRowPointer(row_id);

    do {
        found_key = *(TKey*)p;
        std::cout << found_key << "first\n";
        p += sizeof (TKey);
        found_data = *(TData*)p;
        std::cout << found_data << "after move\n";
        p += sizeof (TData);
    } while (found_key != key && row_id < mCount);

    return ret;
}

#endif //FDBS_CPOINTERTABLE_H
