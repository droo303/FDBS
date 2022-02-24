#pragma once

#include <assert.h>
#include <stdlib.h>

template<class TKey, class TData>
class cHeapTable
{
private:
	int mCapacity;
	int mCount;
	char* mData;
	int const mRowSize = sizeof(TKey) + sizeof(TData);

private:
	inline char* GetRowPointer(int rowId) const;

public:
	cHeapTable(int capacity);
	~cHeapTable();

	bool Add(const TKey &key, const TData &data);
	bool Get(int rowId, TKey &key, TData &data) const;
    bool Find ( const TKey &key , TData &data ) const;

};

template<class TKey, class TData>
cHeapTable<TKey, TData>::cHeapTable(int capacity)
{
	mCapacity = capacity;
	mCount = 0;
	mData = new char[mRowSize * capacity];
}

template<class TKey, class TData>
cHeapTable<TKey, TData>::~cHeapTable()
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
inline char* cHeapTable<TKey, TData>::GetRowPointer(int rowId) const
{
	return mData + rowId * mRowSize;
}

template<class TKey, class TData>
bool cHeapTable<TKey, TData>::Get(int rowId, TKey &key, TData &data) const
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
bool cHeapTable<TKey, TData>::Add(const TKey &key, const TData &data)
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
bool cHeapTable<TKey, TData>::Find(const TKey &key, TData &data) const {
    bool ret = false;

    if (key > mCapacity) return ret;

    TKey found_key = 0;
    TKey found_data = 0;

    char* p = mData;

    do {
        found_key = *(TKey*)p;
        p += sizeof (TKey);
        found_data = *(TData*)p;
        p += sizeof (TData);

        if (found_key == key) {
            data = found_data;
            ret = true;
            break;
        }
    } while (found_key < mCount);

    return ret;
}