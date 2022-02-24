//
// Created by pkozusnik on 20.02.22.
//

#ifndef FDBS_CPOINTERTABLE_H
#define FDBS_CPOINTERTABLE_H

#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

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

    std::vector<cRecord<TKey, TData>> mData = std::vector<cRecord<TKey, TData>>();
    cRecord<TKey, TData>** mPointerData;

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
    mData = new cRecord<TKey, TData> [capacity];
    mPointerData = new cRecord<TKey, TData>* [capacity];

    mCapacity = capacity;
    mCount = 0;
}

template<class TKey, class TData>
cPointerTable<TKey, TData>::~cPointerTable()
{
    if (mData != NULL)
    {
        delete mData;
        mData = NULL;
        delete mPointerData;
        mPointerData = NULL;

        mCapacity = 0;
        mCount = 0;
    }
}

template<class TKey, class TData>
bool cPointerTable<TKey, TData>::Get(int rowId, TKey &key, TData &data) const
{
    bool ret = false;
    assert(rowId >= 0 && rowId < mCount);

    //TODO

    return ret;
}

template<class TKey, class TData>
bool cPointerTable<TKey, TData>::Add(const TKey &key, const TData &data)
{
    bool ret = false;
    assert(mCapacity > mCount);

    // insert record to data
    cRecord<TKey, TData> record = new cRecord<TKey, TData>(key,data);
    mData.insert(record);

    // save its pointer (key)
    cRecord<TKey,TData>* cRecordPtr = &mData.back();
    mPointerData[mCount] = cRecordPtr;

    mCount++;

    ret = true;
    return ret;
}

template<class TKey, class TData>
bool cPointerTable<TKey, TData>::Find(const TKey &key, TData &data) const {
    //TODO
    bool ret = false;
    return ret;
}

#endif //FDBS_CPOINTERTABLE_H
