#pragma once

#include "cHashTableNode.h"
#include "cMemory.h"

template<class TKey, class TData>
class cHashTableNode
{
private:
    bool mEmptyNode;
    TKey mKey;
    TData mData;
    cHashTableNode* mNextNode;

public:
    cHashTableNode();
    ~cHashTableNode();

    bool Add(const TKey &key, const TData &data, int &itemCount, int &nodeCount);
    bool Add(const TKey &key, const TData &data, cMemory*& memory, int &itemCount, int &nodeCount);
    bool Find(const TKey &key, TData &data) const;
};

template<class TKey, class TData>
cHashTableNode<TKey, TData>::cHashTableNode()
{
    mNextNode = NULL;
    mEmptyNode = true;
}

template<class TKey, class TData>
cHashTableNode<TKey, TData>::~cHashTableNode()
{
    if (mNextNode != NULL)
    {
        delete mNextNode;
        mNextNode = NULL;
    }
}

template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::Add(const TKey &key, const TData &data, int &itemCount, int &nodeCount)
{
    bool ret = true;

    if (!mEmptyNode) {
        if (mKey == key) {
            ret = false;
        }
        else {
            if (mNextNode == NULL) {
                mNextNode = new cHashTableNode<TKey, TData>();
                nodeCount++;
            }
            ret = mNextNode->Add(key, data, itemCount, nodeCount);
        }
    }
    else {
        mKey = key;
        mData = data;
        mEmptyNode = false;
        itemCount++;

        ret = true;
    }
    return ret;
}

template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::Find(const TKey &key, TData &data) const
{
    if (mEmptyNode) return false;
    if (mKey == key) {
        data = mData;
        return true;
    }
    if (mNextNode != NULL) return mNextNode->Find(key, data);
    return false;
}

template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::Add(const TKey &key, const TData &data, cMemory *&memory, int &itemCount, int &nodeCount) {
    bool ret = true;
    if (!mEmptyNode ) {
        if(mKey == key) {
            ret = false;
        }
        else {
            if (mNextNode == NULL) {
                if (memory == NULL) {
                    mNextNode = new cHashTableNode<TKey , TData> () ;
                }
                else {
                    char* mem = memory->New(sizeof(cHashTableNode<TKey,TData>));
                    mNextNode = new (mem)cHashTableNode<TKey,TData>();
                }
                nodeCount++;
            }
            ret = mNextNode->Add(key,data,memory,itemCount,nodeCount);
        }
    }
    else {
        mKey = key ;
        mData = data ;
        mEmptyNode = false;
        itemCount++;
        ret = true;
    }
    return ret;
}