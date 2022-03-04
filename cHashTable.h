#pragma once

#include "cHashTableNode.h"
#include "cMemory.h"

template<class TKey, class TData>
class cHashTable
{
private:
    int mSize;
    cHashTableNode<TKey,TData>** mHashTable;
    int mItemCount;
    int mNodeCount;
    cMemory *mMemory;

private:
    inline int HashValue(const TKey &key) const;

public:
    explicit cHashTable(int size);
    cHashTable(int size, cMemory *memory);
    ~cHashTable();

    bool Add(const TKey &key, const TData &data);
    bool Find(const TKey &key, TData &data) const;
    void PrintStat() const;
};

template<class TKey, class TData>
cHashTable<TKey,TData>::cHashTable(int size)
{
    mSize = size;
    mHashTable = new cHashTableNode<TKey,TData>*[size];
    for (int i = 0; i < mSize; i++)
    {
        mHashTable[i] = NULL;
    }
}

template<class TKey, class TData>
cHashTable<TKey,TData>::cHashTable(int size, cMemory *memory)
{
    mSize = size;
    mHashTable = new cHashTableNode<TKey,TData>*[size];
    for (int i = 0; i < mSize; i++)
    {
        mHashTable[i] = NULL;
    }
    mMemory = memory;
}

template<class TKey, class TData>
cHashTable<TKey, TData>::~cHashTable() {
    if (mMemory == NULL) {
        for (int i = 0; i < mSize; i++) {
            if (mHashTable[i] != NULL) {
                delete mHashTable[i];
            }
        }
    }
    delete mHashTable;
}

template<class TKey, class TData>
bool cHashTable<TKey, TData>::Add(const TKey &key, const TData &data)
{
    int hv = HashValue(key);

    if (mHashTable[hv] == NULL) {
        if (mMemory == NULL) {
            mHashTable[hv] = new cHashTableNode<TKey, TData>();
        }
        else  {
            char* mem = mMemory->New(sizeof (cHashTableNode<TKey, TData>));
            mHashTable[hv] = new (mem)cHashTableNode<TKey, TData>();
        }
        mNodeCount++;
    }

    return mHashTable[hv]->Add(key, data, mMemory, mItemCount, mNodeCount);
}

template<class TKey, class TData>
bool cHashTable<TKey, TData>::Find(const TKey &key, TData &data) const
{
    if (mHashTable[HashValue(key)]->Find(key, data)) return true;
    return false;
}

template<class TKey, class TData>
inline int cHashTable<TKey, TData>::HashValue(const TKey &key) const
{
    return key % mSize;
}

template<class TKey, class TData>
void cHashTable<TKey, TData>::PrintStat() const
{
    printf("HashTable Statistics: Size: %d, ItemCount: %d, NodeCount: %d, Avg. Items/Slot: %.2f.\n",
           mSize, mItemCount, mNodeCount, (float)mItemCount / mSize);
}